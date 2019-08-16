// HardCoded.cpp
//
// C++ code to price an option, essential algorithms.
//
// We take CEV model with a choice of the elaticity parameter
// and the Euler method. We give option price and number of times
// S hits the origin.
//
// (C) Datasim Education BC 2008-2011
//

#include "OptionData.hpp"
#include "EuropeanOption.h"
#include "EuropeanOptionException.h"
#include "NormalGenerator.hpp"
//#include "Range.cpp"
#include <cmath>
#include <iostream>
#include <vector>


int main()
{
	using std::cout; using std::cin; using std::endl;
	
	cout <<  "1 factor MC with explicit Euler\n";	 
	// create test option
	double S_0 = 60.0;
	map<string, double> option_params{ {"K", 65.0}, {"S", S_0}, {"T", 0.25}, {"r", 0.08},
	{"sig", 0.3} },
	cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	string option_type = "P", underlying = "Stock";
	//EuropeanOption test_option(option_params, option_type, underlying);
	//OptionDataCEV cev_option0(test_option, cev_params);
	OptionDataCEV cev_option(option_params, option_type, underlying, cev_params);
	
	int count = 0;						// Count spurious values
	double sim_price = 0.0;				// Price after sim_run
	run_sim(cev_option, S_0, sim_price, count);		// Simulation run moved to a function in 
													// OptionData.hpp
	
	// Discount the average price
	sim_price *= exp(-cev_option.r() * cev_option.T());

	cout << "Price, after discounting: " << sim_price << ", " << endl;
	cout << "Number of times origin is hit: " << count << endl;

	return 0;
}