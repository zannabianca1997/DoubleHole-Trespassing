#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

#include "CONST.h"
#include "Output.h"
#include "SimpleIni/SimpleIni.h"
#include "libnpy/npy.hpp"

/* convert string to char array*/
char* to_char_arr(const std::string val){
	char* cstr = new char[val.size() + 1];
	strcpy(cstr, val.c_str());
	return cstr;
}
std::string to_string(const PathTypes val){
	switch(val){
		case PATH_CENTRE:
			return "CENTRE";
		case PATH_LEFT:
			return "LEFT";
		case PATH_RIGTH:
			return "RIGTH";
	}
}

/* writing to file*/
void to_file(CSimpleIniA& ini, const SimValues values){
	/* saving the calculated values */
	ini.SetValue("Values", "Eta_0", to_char_arr(std::to_string(values.eta_0)));
	ini.SetValue("Values", "Eta_d", to_char_arr(std::to_string(values.eta_d)));
	/* saving the statistic */
	ini.SetValue("Stats", "Accepted", to_char_arr(std::to_string(values.accepted)));
	ini.SetValue("Stats", "Calc_time", to_char_arr(std::to_string(values.calc_time)));
}
void to_file(const char * filePath, const MetroPath values, const SimSetup setup){
	// first we convert the data to a vector
	std::vector<CELL_T> data(values, values + (setup.N * setup.samples));
	unsigned long shape[] = {setup.samples, setup.N};
	npy::SaveArrayAsNumpy<CELL_T>(filePath, false, 2, shape, data);
}

/* pretty printing implementations */
const std::string pretty_print(const SimSetup setup){
	std::stringstream ss; //this stream will be loaded with all the value in clear format
	ss  << "Physical parameters" << std::endl 
		<< "\tT_bar=" << setup.T_bar << std::endl 
		<< "\tlambda=" << setup.lambda << std::endl 
		<< "\tstart_path=" << to_string(setup.start_path) << std::endl
		<< "Simulation parameters" << std::endl 
		<< "\tSEED=" << setup.SEED << std::endl
		<< "\tN=" << setup.N << std::endl 
		<< "\trepeats=" << setup.repeats << std::endl 
		<< "\tdelta=" << setup.delta << std::endl 
		<< "\tsamples=" << setup.samples << std::endl
		<< "\tsamples_spacing=" << setup.samples_spacing << std::endl;
	return ss.str(); //return a string
}
const std::string pretty_print(const SimValues values){
	std::stringstream ss; //this stream will be loaded with all the value in clear format
	ss  << "Simulation values" << std::endl 
		<< "\teta_0=" << values.eta_0 << std::endl 
		<< "\teta_d=" << values.eta_d << std::endl 
		<< "\taccepted=" << values.accepted << std::endl
		<< "\tCalc_time=" << values.calc_time << std::endl;
	return ss.str(); //return a string
}
const std::string pretty_print(const SimPrecalculated values){
	std::stringstream ss; //this stream will be loaded with all the value in clear format
	ss  << "Precalculated values" << std::endl 
		<< "\tQuartic factor=" << values.quartic_factor << std::endl 
		<< "\tSquare factor=" << values.square_factor << std::endl 
		<< "\tNear factor=" << values.near_factor << std::endl;
	return ss.str(); //return a string
}
