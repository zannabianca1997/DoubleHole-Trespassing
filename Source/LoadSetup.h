#pragma once

#include "CONST.h"
#include "SimpleIni/SimpleIni.h"

enum PathTypes {PATH_CENTRE=0, PATH_LEFT=-1, PATH_RIGTH=1};

/*Represent all data of a simulation*/
struct SimSetup{
	FACTOR_T t;
	FACTOR_T T_bar;
	FACTOR_T lambda;
	PathTypes euclid_path;
	PathTypes outher_vertex;
	unsigned int SEED;
	unsigned int N;
	unsigned int M;
	FACTOR_T alpha;
	unsigned int repeats;
	FACTOR_T delta;
	FACTOR_T delta_E;
	unsigned int samples;
	unsigned int samples_spacing;
};

/*Read the setups from a ini file*/
const SimSetup read_setup(CSimpleIniA& ini);


