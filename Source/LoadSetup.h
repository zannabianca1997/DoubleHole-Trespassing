#pragma once

#include "CONST.h"
#include "SimpleIni/SimpleIni.h"

/*Represent all data of a simulation*/
struct SimSetup{
	FACTOR_T t;
	FACTOR_T T_bar;
	FACTOR_T lambda;
	FACTOR_T first_vertex;
	FACTOR_T second_vertex;
	FACTOR_T outher_vertex;
	unsigned int SEED;
	unsigned int N;
	unsigned int M;
	FACTOR_T alpha;
	unsigned int repeats;
	FACTOR_T delta;
	unsigned int samples;
	unsigned int samples_spacing;
};

/*Read the setups from a ini file*/
const SimSetup read_setup(CSimpleIniA& ini);


