#include "CONST.h"


#include <math.h>
#ifdef PROGRESS
#include <iostream>
#endif
#include <chrono>
#include <limits> 
#include <cstring>

#include "Metropolis.h"
#include "Ran2.h"


/* make the preparatory calculations */
void precalculate(const SimSetup setup, SimValues& values, SimPrecalculated& precalculated){
	//calculating adimensional spacing factors
	values.eta_0 = 1/(setup.N*setup.T_bar);
	values.eta_d = values.eta_0 / setup.lambda;
	//precalculating important factors
	precalculated.quartic_factor = -values.eta_0;
	precalculated.square_factor = 2*values.eta_0 - 8*setup.lambda/values.eta_d;
	precalculated.near_factor = 8*setup.lambda/values.eta_d;
	//setting up dinamic calculated values with null indicator
	values.accepted = std::numeric_limits<STATS_T>::quiet_NaN();
	values.calc_time =  std::numeric_limits<unsigned int>::max();
}

/* generate a random initial path */
MetroPath generate_initial(const SimSetup setup){
	Path path = new CELL_T[setup.N * setup.samples]; // allocating memory
	for(int i=0;i<setup.N;i++) {
		path[i] = setup.start_path; //the values are renormalized. so 1 is the center of the rigth hole
	}
	return path;
}

/* evaluate the change in the action(negated and divided by h_bar) if the value y_n is changed to y_n + d. neighbour_sum is [y_(n-1) + y_(n+1)] */
inline CELL_T norm_deltaS(CELL_T y_n, CELL_T d, CELL_T neighbour_sum, const SimPrecalculated& precalculated){
	static CELL_T y_n2, sqr_y_n, sqr_y_n2;
	y_n2 = y_n + d; // calcolo in nuovo valore
	sqr_y_n = y_n * y_n; sqr_y_n2 = y_n2 * y_n2; //calcolo i quadrati
	
	return  precalculated.quartic_factor * (sqr_y_n2*sqr_y_n2 - sqr_y_n*sqr_y_n) +
			precalculated.square_factor  * (sqr_y_n2 - sqr_y_n) +
			precalculated.near_factor    * neighbour_sum * d;
}

/* make a local metropolis step, return if accepted
	y_n is the value in this cell
	y_before is the value in the cell before
	y_after is the value in the cell after
	y_out is where to store the result */
unsigned int local_step(Cell y_n, const CELL_T y_before, const CELL_T y_after, const SimSetup& setup, const SimPrecalculated& precalculated){
	// first i'll extract how much to change the state
	static CELL_T d, norm_delta_s, neighbour_sum;
	static unsigned int accepted;
	static unsigned int repeats = setup.repeats;
	accepted = 0;
	neighbour_sum = y_before+y_after;
	for(int i=0; i<repeats; i++){ // repeating the passage repeats time
		d = ran2::simmetric_ran2(setup.delta); // extracting a uniform number between -delta and delta
		norm_delta_s = norm_deltaS(*y_n, d, neighbour_sum, precalculated);
		if(
			norm_delta_s >= 0 // we have moved to a more probable state, is automatically accepted
			|| ran2::ran2() < exp(norm_delta_s) // we accept with a probability p_new/p_old = e^(-1/h deltaS) = e^norm_delta_s
		)	{
			*y_n += d; // we save the modified value
			accepted ++;
		}
		// the new state is refused, *y_n stay the same
	}
	return accepted;
}

/* make an entire pass on a state, save on state n+1, return accepted percentage */
STATS_T step(const Path state, const SimSetup& setup, const SimPrecalculated& precalculated){
	static unsigned int accepted;
	accepted=0; // it's zeroed every time
	static unsigned int N = setup.N; static unsigned int repeats = setup.repeats; // dereferencing for faster code, initialized only once
	static Cell pos;
	pos = (Cell) state; // the cell we are using, the same in the next state
	accepted += local_step(pos, *(pos + N - 1), *(pos + 1), setup, precalculated); // use periodic condition
	pos++; // next cell
	for(int i=0;i<(N-2);i++){ // for every site except the first and last
		accepted += local_step(pos, *(pos - 1), *(pos + 1), setup, precalculated);
		pos++; // next cell
	}
	accepted += local_step(pos, *(pos - 1), *(pos - N + 1), setup, precalculated); // use periodic condition
	return ((STATS_T)accepted)/(N * repeats);
}

void metropolis(const MetroPath state, const SimSetup setup, SimValues& values, const SimPrecalculated precalculated){
	STATS_T accepted = 0;
	auto start = std::chrono::high_resolution_clock::now(); // taking the start time
	unsigned int rowdim = setup.N * sizeof(CELL_T); // dimension of a row
	Cell end = state + setup.N * (setup.samples - 1); // calculating the array end
#ifdef PROGRESS
	unsigned int i = 0;
	unsigned int print_spacing = (setup.samples > 100) ? setup.samples / 100 : 1;  // calculating how much states are 1%
#endif	
	for(Path stat = state; stat < end; stat += setup.N){ // on every row of the array
#ifdef PROGRESS
		if((i % print_spacing) == 0)
			std::cout << "Progress " << 100 * float(stat - state) / float(end - state) << "%" << std::endl; // keeping progress status
		i++;
#endif
		for(int i=0; i<setup.samples_spacing;i++) // repeat spacing time a full pass
			accepted += step(stat, setup, precalculated); //
		memcpy((void*) (stat + setup.N), (void*)stat, rowdim);  // copy a row to the next
	}
	unsigned int duration = std::chrono::duration_cast<std::chrono::TIMING_UNITS>(std::chrono::high_resolution_clock::now() - start).count(); 
	values.accepted = accepted / ((setup.samples-1)*setup.samples_spacing);  //calculating the mean accepted probability
	values.calc_time = duration;
}
