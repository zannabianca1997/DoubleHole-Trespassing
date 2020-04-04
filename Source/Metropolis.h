#pragma once

#include "CONST.h"
#include "LoadSetup.h"


/* represent the values for the simulation*/
struct SimValues {
	FACTOR_T eta_0;
	FACTOR_T eta_d;
	STATS_T accepted;
	unsigned int calc_time;
};

/* precalculated values for the simulation */
struct SimPrecalculated{
	FACTOR_T quartic_factor;
	FACTOR_T square_factor;
	FACTOR_T near_factor;
};

/* represent the system */
typedef CELL_T* MetroPath;  // a metropolis walks, aka a list of path of len setup.samples
typedef CELL_T* Path;       // a system path, aka a list of cells of len setup.N
typedef CELL_T* Cell;       // a cell, aka a pointer to a CELL_T

/* make the preparatory calculations */
void precalculate(const SimSetup setup, SimValues& values, SimPrecalculated& precalculated);

/* generate a random initial path */
Path generate_initial(const SimSetup setup);

/* make an entire pass on the state n, storing the new state on n+1 */
STATS_T step(Path state, const SimSetup& setup, const SimPrecalculated& precalculated);

/* execute the simulation */
void metropolis(const MetroPath state, const SimSetup setup, SimValues& values, const SimPrecalculated precalculated);
