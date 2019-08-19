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
//#include "OptionData.cpp"
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

	// a.
	Study the source code in the file TestMC.cpp and relate it to the theory that we have
	just discussed. The project should contain the following source files and you need to
	set project settings in VS to point to the correct header files:
	
	Compile and run the program as is and make sure there are no errors.


	// b.
	Run the MC program again with data from Batches 1 and 2. Experiment with different
	value of NT (time steps) and NSIM (simulations or draws). In particular, how many
	time steps and draws do you need in order to get the same accuracy as the exact
	solution?
	How is the accuracy affected by different values for NT/NSIM?

	Test Values for option pricing follows:
	Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)

	*/
	
	// Refactored the code:
	// Created a class OptionData to replace the struct, which includes the drift,
	// diffusion, and diffusion derivative
	// The OptionData class includes a EuropeanOption object, along with the added
	// parameters particular to the simulation requirements
	// Moved the simulation loop to a global function

	
	cout <<  "1 factor MC with explicit Euler\n";	 
	// create parameters for testing Batch 1 and 2
	map<string, double> cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	string option_type = "P", underlying = "Stock";
	
	// create test option from Batch 1	
	double S_initial = 60.0;
	map<string, double> params_b1{ {"K", 65.0}, {"S", S_initial}, {"T", 0.25}, 
	{"r", 0.08}, {"sig", 0.3} };
	
	// create test option from Batch 2
	//map<string, double> option_params_2{ {"K", 100.0}, {"S", S_initial}, {"T", 1.0},
	//{"r", 0.0}, {"sig", 0.2} };
	
	//EuropeanOption test_option(option_params, option_type, underlying);
	//OptionData cev_option0(test_option, cev_params);
	OptionData cev_b1(params_b1, option_type, underlying, cev_params);
	
	int count = 0;						// Count spurious values
	double sim_price = 0.0;				// Price after sim_run
	double target_price = 5.84628;		// Batch 1 'exact' price
	
	// Create vectors for a range of time steps and simulations
	vector<int> time_steps{ 500, 1000, 1500 }; // , 1000, 1500 };
	vector<int> sims{ 1000000, 1100000, 1200000, 1300000, 1400000, 1500000 };
	//vector<int> time_steps{ 500, 1000, 1500 };
	//vector<int> sims{ 50000, 100000, 200000, 300000 , 400000 , 500000, 600000,
		//700000, 800000, 900000, 1000000, 2000000 };
	
	// Simulation run moved to a function in OptionData.hpp
	
	// Create vector to store prices from simulation runs
	vector<tuple<int, int, double, int>> prices;

	// Run simulations for Batch 1
	for (auto step : time_steps)	// loop over range of time steps
	{
		for (auto sim : sims)		// loop over range of simulations
		{
			run_sim(cev_b1, S_initial, sim_price, count, step, sim);		// run simulation
			auto sim_run = std::make_tuple(step, sim, sim_price, count);	// build output
			prices.push_back(sim_run);			// store simulation values
			sim_price = 0; count = 0;			// reset simulation price and count
		}
	}
		
	// Display results
	cout << endl << endl;
	for (auto price : prices)
	{
		cout << "\nSize of mesh:\t\t" << get<0>(price)
			<< "\nNumber of simulations run:\t" << get<1>(price)
			<< "\nBatch 1 Put price:\t\t" << target_price 
			<< "\nSimulated approximation:\t" << get<2>(price) 
			<< "\nCount of spurious values:\t" << get<3>(price) << endl;
	}
	
	cout << "\nFrom the simulation runs above, the following NT/NSIM values generate"
		<< "\nthe best simulated price approximations:\nNT:\t" << time_steps[2]
		<< "\nNSIM:\t" << sims[2] << " & " << sims[4] << endl;
	cout << endl << endl;

		
	/////////////////////////
	/*
	// c) Now we do some stress-testing of the MC method. Take Batch 4. What values	
	do we need to assign to NT and NSIM in order to get an accuracy to two places
	behind the decimal point? How is the accuracy affected by different values 
	for NT/NSIM?

	Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)
	*/

	/*
	cout <<  "1 factor MC with explicit Euler\n";
	// create parameters for testing Batch 4
	map<string, double> cev_params{ { "H", 0.0 }, { "D", 0.0 }, { "betaCEV", 1.0 }, { "scale", 1.0 } };
	string option_type = "C", underlying = "Stock";
	double S_initial = 100.0;
	map<string, double> params_b4{ {"K", 100.0}, {"S", S_initial}, {"T", 30.0},
		{"r", 0.08}, {"sig", 0.3} };

	OptionData cev_b4(params_b4, option_type, underlying, cev_params);

	count = 0;						// Count spurious values
	sim_price = 0.0;				// simulated price
	target_price = 92.17570;		// 'exact' price
	double sim_epsilon = 0.025;			// delta to determine range of acceptable simulated prices 

	// Create ranges for time_steps and nsims
	Range<int> t_range(500, 1500);
	vector<int> time_steps{ 1000 }; // = t_range.mesh(10);
	//vector<int> time_steps = t_range.mesh(10);
	Range<int> s_range(100000, 2000000);
	vector<int> sims{ 200000 }; // = s_range.mesh(19);
	//vector<int> sims = s_range.mesh(19);

	/*
	double x = 30.0 / 1000;
	vector<double> testvec(10);
	std::generate(testvec.begin(), testvec.end(),
		[step = 0.0, x]() mutable { return step += x; });
	
	cout << endl << endl;
	for (auto x : testvec)
		std::cout << x << endl;
	cout << endl << endl;

	cout << "\n\nt_steps:\n";
	print(time_steps);
	cout << "\n\nsims:\n";
	print(sims);
	
	
	// Reset vector to store prices from simulation runs
	//prices.clear();
	// Create vector to store prices from simulation runs
	vector<tuple<int, int, double, int>> prices;

	for (auto step : time_steps)		// loop over time steps
	{
		for (auto sim : sims)			// loop over simulations
		{
			run_sim(cev_b4, S_initial, sim_price, count, step, sim);
			//if (abs(sim_price - target_price) <= sim_epsilon)	// filter simulation price
			//{
				auto sim_run = std::make_tuple(step, sim, sim_price, count);	// build output
				prices.push_back(sim_run);					// add filtered price to output vector 
			//}
			sim_price = 0; count = 0;	// reset simulation variables
		}
	}


	// display results
	cout << endl << endl;
	for (auto price : prices)
	{
		cout << "\nNumber of Time Steps:\t\t" << get<0>(price)
			<< "\nNumber of simulations run:\t" << get<1>(price)
			<< "\nTarget price:\t\t\t" << target_price 
			<< "\nSimulated approximation:\t" << get<2>(price)
			<< "\nCount of spurious values:\t" << get<3>(price) << endl;
	}

	cout << endl << endl;

	//cout << "Price, after discounting: " << sim_price << ", " << endl;
	//cout << "Number of times origin is hit: " << count << endl;

	*/
	return 0;
}