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
#include "diffs.h"


/* make the preparatory calculations */
void precalculate(const SimSetup setup, SimValues& values, SimPrecalculated& precalculated){
	//calculating adimensional spacing factors
	values.eta_a = 1/(setup.N*setup.T_bar);
	values.eta_b = setup.t / setup.M;
	//precalculating important factors
	precalculated = new FACTOR_T[PRECALC_LEN];
	precalculate(setup.lambda, values.eta_a, values.eta_b, setup.alpha, setup.N, setup.M, precalculated);
	//setting up dinamic calculated values with null indicator
	values.accepted = std::numeric_limits<STATS_T>::quiet_NaN();
	values.accepted_E = std::numeric_limits<STATS_T>::quiet_NaN();
	values.calc_time =  std::numeric_limits<unsigned int>::max();
}

/* generate a random initial path */
MetroPath generate_initial(const SimSetup setup){
	Path path = new CELL_T[(setup.N + 2*setup.M) * setup.samples]; // allocating memory
	for(int i=0;i<setup.N;i++)
		path[i] = setup.euclid_path; //the values are renormalized. so 1 is the center of the rigth hole
	FACTOR_T slope = (setup.outher_vertex - setup.euclid_path) / setup.M;
	for(int i=0;i<setup.M;i++)
		path[setup.N + i] = setup.euclid_path + slope * i;
	for(int i=0;i<setup.M;i++)
		path[setup.N + setup.M + i] = setup.outher_vertex - slope * i;
	return path;
}


/* make a local metropolis step, return if accepted
	y_n is the value in this cell
	y_before is the value in the cell before
	y_after is the value in the cell after
	y_out is where to store the result */
template <FACTOR_T (*get_delta_exp)(double, double, double*, double*), bool keep_positive>
inline bool local_step(Cell cell, FACTOR_T* cache, const SimPrecalculated precalculated, const FACTOR_T delta){
	// local vars 
	CELL_T d;
	FACTOR_T norm_delta_exp;
	//start the cicle
	d = ran2::simmetric_ran2(delta); // extracting a uniform number between -delta and delta
	if(keep_positive){ // se cell deve restare positiva
		CELL_T res = *cell + d;
		if(res < 0)
			d = - (*cell) - res; // so d + cell is positive. this is simmetric, as needed by metropolis
	}
	norm_delta_exp = get_delta_exp(d, *cell, precalculated, cache);
	if(
		norm_delta_exp >= 0 // we have moved to a more probable state, is automatically accepted
		|| ran2::ran2() < exp(norm_delta_exp) // we accept with a probability p_new/p_old = e^(-1/h deltaS) = e^norm_delta_s
	){
		*cell += d; // we save the modified value
		return true;
	}
	// the new state is refused, *cell stay the same
	return false;
}

/* make an entire pass on a state, save on state n+1, return accepted percentage */
void step(const Path state, const SimSetup& setup, const SimPrecalculated precalculated, SimValues& values){
	// dereferencing for faster code
	unsigned int N = setup.N; unsigned int M = setup.M;
	unsigned int repeats = setup.repeats;
	FACTOR_T delta_E = setup.delta_E;
	FACTOR_T delta = setup.delta;
	// cache space
	FACTOR_T cache[CACHE_LEN];
	// statistical space
	unsigned int accepted;
	Cell pos; // the cell we are using
	int j; //loop variable
	//getting the parts of the path
	Cell y = (Cell)state;
	Cell x1 = y + N;
	Cell x2 = y + N + M;
	
	// EUCLID PART
	
	accepted = 0;
	
	// first euclid step
	cache_diff_y_0(x2[M-1], x2[M-2], y[1], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_y_0, true>(y+0, cache, precalculated, delta_E);
	for(pos = y+1;pos<y+N-1;pos++){ // for every site except the first and last
		// main euclid steps
		cache_diff_y_j(*(pos - 1), *(pos + 1), precalculated, cache);
		for(int i = 0;i<repeats;i++)
			accepted += local_step<diff_y_j, true>(pos, cache, precalculated, delta_E);
	}
	// last euclid step
	cache_diff_y_N_1(x1[0], y[N-2], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_y_N_1, true>(y+N-1, cache, precalculated, delta_E);
	
	values.accepted_E += ((STATS_T)accepted)/(N * repeats);
	
	// MINKOVSKIAN PART
	
	accepted = 0;
	
	// first minkovskian step
	cache_diff_x1_0(x1[1],x1[2],y[N-1], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x1_0, false>(x1+0, cache, precalculated, delta);
	// second minkovskian step
	cache_diff_x1_1(x1[0],x1[2],x1[3], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x1_1, false>(x1+1, cache, precalculated, delta);
	for(pos = x1+2;pos<x1+M-2;pos++){ // for every site except the first and last
		// main minkovskian steps
		cache_diff_x1_j(*(pos - 1),*(pos - 2),*(pos + 1),*(pos + 2), precalculated, cache);
		for(int i = 0;i<repeats;i++)
			accepted += local_step<diff_x1_j, false>(pos, cache, precalculated, delta);
	}
	// first-to-last minkovskian step
	cache_diff_x1_M_2(x1[M-1], x1[M-3], x1[M-4], x2[0], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x1_M_2, false>(x1+M-2, cache, precalculated, delta);
	// last minkovskian step
	cache_diff_x1_M_1(x1[M-2], x1[M-3], x2[0], x2[1], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x1_M_1, false>(x1+M-1, cache, precalculated, delta);
	
	values.accepted += ((STATS_T)accepted)/(M * repeats);
	
	// REVERSE MINKOVSKIAN PART
	
	accepted = 0;
	
	// first reverse minkovskian step
	cache_diff_x2_0(x1[M-1],x1[M-2],x2[1], x2[2], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x2_0, false>(x2+0, cache, precalculated, delta);
	// second reverse minkovskian step
	cache_diff_x2_1(*(pos - 1),*(pos - 2),*(pos + 1),*(pos + 2), precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x2_1, false>(x2+1, cache, precalculated, delta);

	for(pos = x2+2;pos<x2+M-2;pos++){ // for every site except the first and last
		// main reverse minkovskian steps
		cache_diff_x2_j(x2[M-4],x2[M-3], x2[M-1], y[0], precalculated, cache);
		for(int i = 0;i<repeats;i++)
			accepted += local_step<diff_x2_j, false>(pos, cache, precalculated, delta);
	}
	// first-to-last reverse minkovskian step
	cache_diff_x2_M_2(x2[M-4],x2[M-3], x2[M-1], y[0], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x2_M_2, false>(x2+M-2, cache, precalculated, delta);
	// last reverse minkovskian step
	cache_diff_x2_M_1(x2[M-2],x2[M-3], y[0], precalculated, cache);
	for(int i = 0;i<repeats;i++)
		accepted += local_step<diff_x2_M_1, false>(x2+M-1, cache, precalculated, delta);
		
	values.accepted += ((STATS_T)accepted)/(M * repeats);
}

void metropolis(const MetroPath state, const SimSetup setup, SimValues& values, const SimPrecalculated precalculated){
	auto start = std::chrono::high_resolution_clock::now(); // taking the start time
	values.accepted = 0; //so we sum from there
	values.accepted_E = 0; //so we sum from there
	
	unsigned int cell_num = setup.N + 2*setup.M; // len of a row
	unsigned int rowdim = cell_num * sizeof(CELL_T); // dimension of a row
	Cell end = state + cell_num * (setup.samples - 1); // calculating the array end

#ifdef PROGRESS
	unsigned int i = 0;
	unsigned int print_spacing = (setup.samples > 100) ? setup.samples / 100 : 1;  // calculating how much states are 1%
#endif	
	for(Path stat = state; stat < end; stat += cell_num){ // on every row of the array
#ifdef PROGRESS
		if((i % print_spacing) == 0)
			std::cout << "Progress " << 100 * float(stat - state) / float(end - state) << "%" << std::endl; // keeping progress status
		i++;
#endif
		for(int j=0; j<setup.samples_spacing;j++) // repeat samples_spacing time a full pass
			step(stat, setup, precalculated, values); // make a step
		memcpy((void*) (stat + cell_num), (void*)stat, rowdim);  // copy a row to the next
	}
	unsigned int duration = std::chrono::duration_cast<std::chrono::TIMING_UNITS>(std::chrono::high_resolution_clock::now() - start).count(); 
	values.accepted /= 2 * ((setup.samples-1)*setup.samples_spacing);  //calculating the mean accepted probability
	values.accepted_E /= ((setup.samples-1)*setup.samples_spacing);  //calculating the mean accepted probability
	values.calc_time = duration;
}
