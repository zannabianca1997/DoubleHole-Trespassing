#pragma once

#include "CONST.h"
#include "LoadSetup.h"
#include "Metropolis.h"
#include "SimpleIni/SimpleIni.h"


/*Write out the setups in a readable format*/
const std::string pretty_print(const SimSetup setup);
const std::string pretty_print(const SimValues setup);
const std::string pretty_print(const SimPrecalculated setup);

/* output to file */
void to_file(CSimpleIniA& ini, const SimValues values);
void to_file(const char * filePath, const MetroPath values, const SimSetup setup);
