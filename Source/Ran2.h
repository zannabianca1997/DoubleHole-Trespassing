#pragma once

namespace ran2{
	void set_seed(unsigned int seed);
	double ran2();
	double gauss_ran2(double mean, double stddev);
	
	inline double simmetric_ran2(double max_d){
		return (2*ran2() - 1) * max_d;
	}
}
