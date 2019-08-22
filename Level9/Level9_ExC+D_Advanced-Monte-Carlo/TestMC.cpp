// TestMC.cpp
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
#include "NormalGenerator.hpp"
#include "Range.hpp"
#include "Range.cpp"
#include <cmath>
#include <iostream>
#include <vector>

#include <algorithm>
#include <numeric>
#include <list>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>




int main()
{
	std::cout <<  "1 factor MC with explicit Euler\n";
	OptionData myOption;		// Batch 1 parameters
	myOption.K = 65.0;
	myOption.T = 0.25;
	myOption.r = 0.08;
	myOption.sig = 0.3;
	myOption.type = -1;	// Put -1, Call +1
	double S_0 = 60;
	double Batch1_price = 5.84628;		// Put price 

	/*
	OptionData myOption;		// Batch 2 parameters
	myOption.K = 100.0;
	myOption.T = 1.0;
	myOption.r = 0.0;
	myOption.sig = 0.2;
	myOption.type = 1;	// Put -1, Call +1
	double S_0 = 100.0;
	double Batch2_price = 7.96557;		// Call price
	*/
	
	// Create vectors for time steps and number of simulations
	vector<int> t_steps{ 500, 1000, 1500 };
	vector<int> NSims{ 50000, 100000, 200000, 300000, 400000, 500000,
		600000, 700000, 800000, 900000, 1000000, 1500000, 2000000 };

	// Create tuple to hold simulation details and output
	vector<boost::tuple<boost::tuple<double, double>, double, int, int, int>> vals;
	vals.reserve(NSims.size() * t_steps.size());		// reserve space

	// Create random number and option price variables
	double dW = 0.0;
	double price = 0.0;

	// Create variables for simulation run
	double VOld = S_0;			// initial and current asset price 
	double VNew = 0.0;			// simulated price based on current price

	// Create SDE data, a pointer to an OptionData object
	using namespace SDEDefinition;
	SDEDefinition::data = &myOption;

	std::vector<double> prices;					// simulated prices vector

	// loop over t_steps vector for time steps values
	for (auto N : t_steps)
	{
		// Create the basic SDE (Context class)
		Range<double> range(0.0, myOption.T);
		std::vector<double> x = range.mesh(N);		// mesh range

		double k = myOption.T / double(N);
		double sqrk = sqrt(k);
		
		int count = 0;				// Number of times S hits origin

		// Loop over sims vector for number of simulations values
		for (auto NSim : NSims)
		{
			prices.reserve(NSim);						// reserve space

			// NormalGenerator is a base class
			// std::unique_ptr manages heap memory without the need for the delete function
			std::unique_ptr<NormalGenerator> myNormal{ new BoostNormal() };

			// Run simulation
			for (long i = 1; i <= NSim; ++i)
			{ // Calculate a path at each iteration

				// Give status after each 1000th iteration for debug purposes
				if ((i / 10000) * 10000 == i) { std::cout << i << std::endl; }
				
				for (unsigned long index = 1; index < x.size(); ++index)
				{
					dW = myNormal->getNormal();	// Create a random number

					// The FDM (in this case explicit Euler)
					VNew = VOld + (k * drift(x[index - 1], VOld))
						+ (sqrk * diffusion(x[index - 1], VOld) * dW);

					VOld = VNew;

					if (VNew <= 0.0) count++;	// Count spurious values
				}

				double tmp = myOption.myPayOffFunction(VNew);	// calculate payoff
				price += (tmp) / double(NSim);

				prices.push_back(price);	// collect prices for SD and SE calculations

				VOld = S_0, VNew = 0.0;		// reset values
			}

			price *= exp(-myOption.r * myOption.T);		// Discounting the average price

			// Calculate SD and SE
			boost::tuple<double, double> sum_and_squares(SumSquaresAndSum(prices));
			boost::tuple<double, double> SDandSE(
				StandardDeviationAndError(prices, myOption.r, myOption.T));

			// Collect values
			boost::tuple<boost::tuple<double, double>, double, int, int, int> 
				val{ SDandSE, price, count, N, NSim };
			vals.push_back(val);

			dW = 0.0;				// reset random number variable
			price = 0.0;			// reset Option price
			count = 0;				// reset count
			prices.clear();			// reset prices vector
		}
	}
	
	for (auto val : vals)	// loop and print values for simulations
	{
		std::cout << "\nTime Steps:\t" << get<3>(val) << endl;
		std::cout << "\nNo of sims:\t" << get<4>(val) << endl;
		std::cout << "\nStd Deviation:\t" << get<0>(get<0>(val)) << endl;
		std::cout << "\nStd Error:\t" << get<1>(get<0>(val)) << endl;
		std::cout << "\nPrice after discounting: " << get<1>(val) << endl;
		std::cout << "\nPrice from exact method: " << Batch1_price << endl;
		std::cout << "\nNo of times origin  hit: " << get<2>(val) << endl << endl;
	}

	// unique_ptr manages memory without the need for delete
	//delete myNormal;

	return 0;
}





