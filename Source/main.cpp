#include "CONST.h"

#include <iostream>
#include <string>

// input output modules
#include "LoadSetup.h"
#include "Output.h"

//calculation modules
#include "Metropolis.h"
#include "Ran2.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char** argv) {
	if(argc != 3) {// wrong usage
		std::cout << "Usage: " << argv[0] << " setup_file out_file" << std::endl
				  << "\tsetup_file: the init file for the simulation" << std::endl
				  << "\tout_file: the output file";
		return 0;
	}
	const char* setup_file = argv[1];
	const char* out_file = argv[2];
	
	CSimpleIniA ini;
	ini.LoadFile(setup_file); //load the file
	const SimSetup setup = read_setup(ini); //load the setups
	SimValues values; SimPrecalculated precalculated; // creating space for the values
	precalculate(setup, values, precalculated);  // precalculating important values
#ifdef VERBOSE
	std::cout << pretty_print(setup); 
#endif
	ran2::set_seed(setup.SEED); // initializing random number generator
	MetroPath sim_result = generate_initial(setup); //opening space for the simulation and setting up the initial path
	metropolis(sim_result, setup, values, precalculated); // executing the simulation
#ifdef VERBOSE
	std::cout << pretty_print(values);
#endif
	to_file(ini, values); // saving the value to ini format
	ini.SaveFile(setup_file); // saving ini file
	to_file(out_file, sim_result, setup); // saving data*/
	return 0;
}
