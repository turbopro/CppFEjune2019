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
#include <cmath>
#include <iostream>
#include <vector>


int main()
{
	using std::cout; using std::cin; using std::endl;
	
	cout << "\n\n"
		<< "|===================================================|\n"
		<< "|         A: Run Simulation: Explicit Euler         |\n"
		<< "|===================================================|\n\n\n";
	
	/*
	Study the source code in the file TestMC.cpp and relate it to the theory that we have
	just discussed. The project should contain the following source files and you need to
	set project settings in VS to point to the correct header files:
	
	Compile and run the program as is and make sure there are no errors.

	Test Values for option pricing follows:
	Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).

	*/
	
	// Refactored the code:
	// Created a class OptionData to replace the struct, which includes the drift,
	// diffusion, and diffusion derivative
	// The OptionData class includes a EuropeanOption object, along with the added
	// parameters particular to the simulation requirements
	// Moved the simulation loop to a global function

	
	cout <<  "1 factor MC with explicit Euler\n";	 
	// create test option from Batch 1
	double S_initial = 100.0;
	//map<string, double> option_params{ {"K", 65.0}, {"S", S_initial}, {"T", 0.25}, 
	//{"r", 0.08}, {"sig", 0.3} },
	map<string, double> option_params{ {"K", 100.0}, {"S", S_initial}, {"T", 1.0},
	{"r", 0.0}, {"sig", 0.2} },
	cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	string option_type = "P", underlying = "Stock";
	//EuropeanOption test_option(option_params, option_type, underlying);
	//OptionData cev_option0(test_option, cev_params);
	OptionData cev_option(option_params, option_type, underlying, cev_params);
	
	int count = 0;						// Count spurious values
	double sim_price = 0.0;				// Price after sim_run
	int n = 500; //, nsim = 1000000;

	vector<int> nsim_vec{ 50000, 100000, 200000, 300000, 400000, 500000 , 600000,
		700000, 800000, 900000, 1000000, 2000000 };
	/*
	vector<int> nsim_vec{50000, 100000, 200000, 300000, 400000, 500000, 600000, 
		700000, 800000, 900000, 1000000, 2000000};
	*/

	// Simulation run moved to a function in OptionData.hpp
	// Create vector to store prices from simulation runs
	vector<tuple<double, double, int>> prices_vec;
	for (auto n_sim : nsim_vec)
	{
		run_sim(cev_option, S_initial, sim_price, count, n, n_sim);
		auto sim_run = std::make_tuple (n_sim, sim_price, count);
		prices_vec.push_back(sim_run);
		sim_price = 0; count = 0;
	}
	
	
	// display results
	cout << endl << endl;
	for (auto price : prices_vec)
	{
		cout << "\nNumber of simulations run: " << get<0>(price)
			<< "\nTarget price: 7.96557 :: vs :: simulated approximation: " << get<1>(price) 
			<< "\ncount of spurious values: " << get<2>(price) << endl;
	}
	
	cout << endl << endl;

	//cout << "Price, after discounting: " << sim_price << ", " << endl;
	//cout << "Number of times origin is hit: " << count << endl;

	/*
	/////////////////////////
	// b.
	Run the MC program again with data from Batches 1 and 2. Experiment with different
	value of NT (time steps) and NSIM (simulations or draws). In particular, how many 
	time steps and draws do you need in order to get the same accuracy as the exact 
	solution? 
	How is the accuracy affected by different values for NT/NSIM?
	
	Test Values for option pricing follows:
	Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	*/
	/*
	cout << "1 factor MC with explicit Euler\n";
	// create test option for Batch 2
	double S_initial = 100.0;
	//map<string, double> option_params{ {"K", 100.0}, {"S", S_initial}, {"T", 1.0},
	//{"r", 0.0}, {"sig", 0.2} },
		//cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	map<string, double> option_params{ {"K", 65.0}, {"S", S_initial}, {"T", 0.25},
	{"r", 0.08}, {"sig", 0.3} },
		cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	string option_type = "P", underlying = "Stock";
	//EuropeanOption test_option(option_params, option_type, underlying);
	//OptionData cev_option0(test_option, cev_params);
	OptionData cev_option0(option_params, option_type, underlying, cev_params);

	int count = 0;						// Count spurious values
	double sim_price = 0.0;				// Price after sim_run
	//int N = 1000, NSim = 50000;
	// Simulation run moved to a function in OptionData.hpp
	run_sim(cev_option0, S_initial, sim_price, count);

	// Discount the average price
	sim_price *= exp(-cev_option0.r() * cev_option0.T());

	cout << "Price, after discounting: " << sim_price << ", " << endl;
	cout << "Number of times origin is hit: " << count << endl;

	cout << "\nFor N = 1000, and NSim = 1000000, Call Option Price: 7.97529\n"
		<< "Exact value: 7.96557" << endl << endl;
	*/


	/*
	
	SD = sqrt((price*price)/

	*/

	return 0;
}