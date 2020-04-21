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
	ini.SetValue("Values", "Eta_a", to_char_arr(std::to_string(values.eta_a)));
	ini.SetValue("Values", "Eta_b", to_char_arr(std::to_string(values.eta_b)));
	/* saving the statistic */
	ini.SetValue("Stats", "Accepted", to_char_arr(std::to_string(values.accepted)));
	ini.SetValue("Stats", "Accepted_E", to_char_arr(std::to_string(values.accepted_E)));
	ini.SetValue("Stats", "Calc_time", to_char_arr(std::to_string(values.calc_time)));
}
void to_file(const char * filePath, const MetroPath values, const SimSetup setup){
	// first we convert the data to a vector
	std::vector<CELL_T> data(values, values + ((setup.N + 2*setup.M)  * setup.samples));
	unsigned long shape[] = {setup.samples, setup.N + 2*setup.M};
	npy::SaveArrayAsNumpy<CELL_T>(filePath, false, 2, shape, data);
}

/* pretty printing implementations */
const std::string pretty_print(const SimSetup setup){
	std::stringstream ss; //this stream will be loaded with all the value in clear format
	ss  << "Physical parameters" << std::endl 
		<< "\tt=" << setup.t << std::endl
		<< "\tT_bar=" << setup.T_bar << std::endl 
		<< "\tlambda=" << setup.lambda << std::endl 
		<< "\teuclid_path=" << to_string(setup.euclid_path) << std::endl
		<< "\touther_vertex=" << to_string(setup.outher_vertex) << std::endl
		<< "Simulation parameters" << std::endl 
		<< "\tSEED=" << setup.SEED << std::endl
		<< "\tN=" << setup.N << std::endl 
		<< "\tM=" << setup.M << std::endl 
		<< "\talpha=" << setup.alpha << std::endl 
		<< "\trepeats=" << setup.repeats << std::endl 
		<< "\tdelta=" << setup.delta << std::endl 
		<< "\tdelta_E=" << setup.delta_E << std::endl 
		<< "\tsamples=" << setup.samples << std::endl
		<< "\tsamples_spacing=" << setup.samples_spacing << std::endl;
	return ss.str(); //return a string
}
const std::string pretty_print(const SimValues values){
	std::stringstream ss; //this stream will be loaded with all the value in clear format
	ss  << "Simulation values" << std::endl 
		<< "\teta_a=" << values.eta_a << std::endl 
		<< "\teta_b=" << values.eta_b << std::endl 
		<< "\taccepted=" << values.accepted << std::endl
		<< "\taccepted_E=" << values.accepted_E << std::endl
		<< "\tCalc_time=" << values.calc_time << std::endl;
	return ss.str(); //return a string
}
