#pragma once

#include "CONST.h"
#include "SimpleIni/SimpleIni.h"

enum PathTypes {PATH_CENTRE=0, PATH_LEFT=-1, PATH_RIGTH=1};

/*Represent all data of a simulation*/
struct SimSetup{
	FACTOR_T T_bar;
	FACTOR_T lambda;
	PathTypes start_path;
	unsigned int SEED;
	unsigned int N;
	unsigned int repeats;
	FACTOR_T delta;
	unsigned int samples;
	unsigned int samples_spacing;
};

/*Read the setups from a ini file*/
const SimSetup read_setup(CSimpleIniA& ini);


