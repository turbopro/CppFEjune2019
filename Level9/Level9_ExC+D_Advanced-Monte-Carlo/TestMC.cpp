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


// SDEDefinition
namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term

		return (data->r) * X; // r - D
	}


	double diffusion(double t, double X)
	{ // Diffusion term

		double betaCEV = 1.0;
		return data->sig * pow(X, betaCEV);

	}

	double diffusionDerivative(double t, double X)
	{ // Diffusion term, needed for the Milstein method

		double betaCEV = 1.0;
		return 0.5 * (data->sig) * (betaCEV)* pow(X, 2.0 * betaCEV - 1.0);
	}
} // End of namespace


int main()
{
	std::cout <<  "1 factor MC with explicit Euler\n";
	OptionData myOption;
	myOption.K = 65.0;
	myOption.T = 0.25;
	myOption.r = 0.08;
	myOption.sig = 0.3;
	myOption.type = -1;	// Put -1, Call +1
	double S_0 = 60;
	

	vector<int> t_steps{ 500, 1000, 1500 };
	vector<int> sims{ 50000, 100000, 200000, 300000, 400000, 500000 };

	//boost::tuple<boost::tuple<double, double>, double, int> vals;
	vector<boost::tuple<boost::tuple<double, double>, double, int>> vals;
	vals.reserve(5);

	//double prices = 0.0;
	//long NSim = 20;

	//std::vector<double> avg_prices;
	//avg_prices.reserve(NSim);
	

	for (auto N : t_steps)
	{
		//long N = 100;
		//std::cout << "Number of subintervals in time: ";
		//std::cin >> N;


		// Create the basic SDE (Context class)
		Range<double> range(0.0, myOption.T);
		double VOld = S_0;
		double VNew = 0.0;

		std::vector<double> x = range.mesh(N);
		std::vector<double> avg_prices;
		//avg_prices.reserve(NSim);

		// V2 mediator stuff
		long NSim = 400000;
		std::cout << "Number of simulations: ";
		std::cin >> NSim;

		avg_prices.reserve(NSim);

		double k = myOption.T / double(N);
		double sqrk = sqrt(k);

		// Normal random number
		double dW = 0.0;
		double price = 0.0;	// Option price
		//double output_price = 0.0; // , output_price_sq = 0.0;

		// NormalGenerator is a base class
		NormalGenerator* myNormal = new BoostNormal();
		//std::unique_ptr manages heap memory without the need to use the delete
		// function to clean up memory
		//std::unique_ptr<NormalGenerator> myNormal{ new BoostNormal() };

		using namespace SDEDefinition;
		SDEDefinition::data = &myOption;

		std::vector<double> res;
		int coun = 0; // Number of times S hits origin



		// A.
		for (long i = 1; i <= NSim; ++i)
		{ // Calculate a path at each iteration

			if ((i / 10000) * 10000 == i)
			{// Give status after each 1000th iteration

				std::cout << i << std::endl;
			}

			VOld = S_0;
			for (unsigned long index = 1; index < x.size(); ++index)
			{

				// Create a random number
				dW = myNormal->getNormal();

				// The FDM (in this case explicit Euler)
				VNew = VOld + (k * drift(x[index - 1], VOld))
					+ (sqrk * diffusion(x[index - 1], VOld) * dW);

				VOld = VNew;

				// Spurious values
				if (VNew <= 0.0) coun++;
			}

			double tmp = myOption.myPayOffFunction(VNew);
			price += (tmp) / double(NSim);

			avg_prices.push_back(price);	// collect price for SD and SE calculations
		}


		// D. Finally, discounting the average price
		price *= exp(-myOption.r * myOption.T);

		std::cout << "\navg_prices.size(): " << avg_prices.size() << endl << endl;

		// calculate SD, SE
		boost::tuple<double, double> sum_and_squares(SumSquaresAndSum(avg_prices));
		boost::tuple<double, double> SDandSE(
			StandardDeviationAndError(avg_prices, myOption.r, myOption.T));

		//get<0>(vals) = SDandSE;
		//get<1>(vals) = price;
		//get<2>(vals) = coun;

		boost::tuple<boost::tuple<double, double>, double, int> val{ SDandSE, price, coun };
		vals.push_back(val);

		delete myNormal;
	}
	
	
	//cout << "\nsum: " << get<0>(sum_and_squares) << endl;
	//cout << "\nsquares: " << get<1>(sum_and_squares) << endl << endl;
	
	for (auto val : vals)
	{
		std::cout << "\nSD : " << get<0>(get<0>(val)) << endl;
		std::cout << "\nSE : " << get<1>(get<0>(val)) << endl << endl;
		std::cout << "\nPrice, after discounting: " << get<1>(val) << ", " << std::endl;
		std::cout << "Number of times origin is hit: " << get<2>(val) << endl << endl;
	}
	
	//cout << "\nSD : " << get<0>(get<0>(vals)) << endl;
	//cout << "\nSE : " << get<1>(get<0>(vals)) << endl << endl;

	// Cleanup; V2 use scoped pointer
	//delete myNormal;


	//std::cout << "\nPrice, after discounting: " << get<1>(vals) << ", " << std::endl;
	//std::cout << "Number of times origin is hit: " << get<2>(vals) << endl;


	return 0;
}





