#include <sstream>
#include <iostream>

#include "CONST.h"
#include "LoadSetup.h"


/* convert an array of char to a FACTOR_T */
FACTOR_T to_FACTOR_T(const char * value){
	std::stringstream ss; 
	FACTOR_T res;
	ss << std::string(value);
	ss >> res;
	return res;
}

/* convert an array of char to a STATS_T */
STATS_T to_STATS_T(const char * value){
	std::stringstream ss; 
	STATS_T res;
	ss << std::string(value);
	ss >> res;
	return res;
}

/* convert an array of char to a unsigned int */
unsigned int to_uint(const char * value){
	std::stringstream ss; 
	unsigned int res;
	ss << std::string(value);
	ss >> res;
	return res;
}

PathTypes to_PathTypes(const char * value){
	std::string check = std::string(value);
	if(check == "CENTRE") return PATH_CENTRE;
	if(check == "LEFT")   return PATH_LEFT;
	if(check == "RIGTH")  return PATH_RIGTH;
	std::cerr << "Unrecognized PATH type: " << check << std::endl;
	throw 1;
}

const SimSetup read_setup(CSimpleIniA& ini){
	const SimSetup setup = {  // convert all the values to the data structure
		to_FACTOR_T(ini.GetValue("Physical", "t", "NAN")),
		to_FACTOR_T(ini.GetValue("Physical", "T_bar", "NAN")),
		to_FACTOR_T(ini.GetValue("Physical", "lambda", "NAN")),
		to_PathTypes(ini.GetValue("Physical", "euclid_path", "CENTRE")),
		to_PathTypes(ini.GetValue("Physical", "outher_vertex", "CENTRE")),
		to_uint(ini.GetValue("Simulation", "SEED", "0")),
		to_uint(ini.GetValue("Simulation", "N", "0")),
		to_uint(ini.GetValue("Simulation", "M", "0")),
		to_FACTOR_T(ini.GetValue("Simulation", "alpha", "NAN")),
		to_uint(ini.GetValue("Simulation", "repeats", "0")),
		to_FACTOR_T(ini.GetValue("Simulation", "delta", "NAN")),
		to_FACTOR_T(ini.GetValue("Simulation", "delta_E", "NAN")),
		to_uint(ini.GetValue("Simulation", "samples", "0")),
		to_uint(ini.GetValue("Simulation", "samples_spacing", "0")) 
	};
	if(setup.euclid_path < 0){
		std::cerr << "Euclid path must be non-negative" << std::endl;
		throw 2;
	}
	return setup;
}
