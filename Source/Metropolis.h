#pragma once

#include "CONST.h"
#include "LoadSetup.h"


/* represent the values for the simulation*/
struct SimValues {
	FACTOR_T eta_a;
	FACTOR_T eta_b;
	STATS_T accepted;
	STATS_T accepted_E;
	unsigned int calc_time;
};

/* precalculated values for the simulation */
typedef FACTOR_T * SimPrecalculated;

/* represent the system */
typedef CELL_T* MetroPath;  // a metropolis walks, aka a list of path of len setup.samples
typedef CELL_T* Path;       // a system path, aka a list of cells of len setup.N
typedef CELL_T* Cell;       // a cell, aka a pointer to a CELL_T

/* make the preparatory calculations */
void precalculate(const SimSetup setup, SimValues& values, SimPrecalculated& precalculated);

/* generate a random initial path */
Path generate_initial(const SimSetup setup);

/* execute the simulation */
void metropolis(const MetroPath state, const SimSetup setup, SimValues& values, const SimPrecalculated precalculated);
