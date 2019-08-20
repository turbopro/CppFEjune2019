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



template <class T> 
void print(const std::vector<T>& vec)
{  // A generic print function for vectors
	
	std::cout << std::endl << "Size of vector is " << vec.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	const std::vector<T>::iterator i;
	for (i = vec.begin(); i != vec.end(); ++i)
	{
			std::cout << *i << ",";
	}

	std::cout << "]\n";
}

//*************** Note ****************
// The below functions "borrowed" from thread, "Level 9 Homework comments/questions",
// thread #29, dated 3/13/12, by Dr Duffy

template <typename V>
boost::tuple<double, double> SumSquaresAndSum(const V& container);

template <typename V>
boost::tuple<double, double> StandardDeviationAndError(const V& container, double r, double T);


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
	
	long N = 100;
	std::cout << "Number of subintervals in time: ";
	std::cin >> N;

	
	// Create the basic SDE (Context class)
	Range<double> range (0.0, myOption.T);
	double VOld = S_0;
	double VNew = 0.0;

	std::vector<double> x = range.mesh(N);
	std::vector<double> avg_prices;

	// V2 mediator stuff
	long NSim = 50000;
	std::cout << "Number of simulations: ";
	std::cin >> NSim;

	double k = myOption.T / double (N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price
	//double output_price = 0.0; // , output_price_sq = 0.0;

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &myOption;

	std::vector<double> res;
	int coun = 0; // Number of times S hits origin

	// A.
	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration
			
		if ((i/10000) * 10000 == i)
		{// Give status after each 1000th iteration

				std::cout << i << std::endl;
		}

		VOld = S_0;
		// option_price_t(OptionData opd, vector<double> x, const double s_initial,
		//	double output_price, int coun, NormalGenerator* p_normal)
		for (unsigned long index = 1; index < x.size(); ++index)
		{

			// Create a random number
			dW = myNormal->getNormal();
				
			// The FDM (in this case explicit Euler)
			VNew = VOld  + (k * drift(x[index-1], VOld))
						+ (sqrk * diffusion(x[index-1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) coun++;
		}
			
		double tmp = myOption.myPayOffFunction(VNew);
		price += (tmp)/double(NSim);
		
		avg_prices.push_back(price);
		//output_price = VNew;
		//output_price_sq = VNew * VNew;
	}
	

	// D. Finally, discounting the average price
	price *= exp(-myOption.r * myOption.T);

	cout << "\navg_prices.size(): " << avg_prices.size() << endl << endl;

	// calculate SD, SE
	boost::tuple<double, double> sum_and_squares(SumSquaresAndSum(avg_prices));
	boost::tuple<double, double> SDandSE(
		StandardDeviationAndError(avg_prices, myOption.r, myOption.T));
	
	cout << "\nsum: " << get<0>(sum_and_squares) << endl;
	cout << "\nsquares: " << get<1>(sum_and_squares) << endl << endl;
	cout << "\nSD: " << get<0>(SDandSE) << endl;
	cout << "\nSE: " << get<1>(SDandSE) << endl << endl;
	
	//double SD = sqrt((output_price_sq - ((output_price * output_price) / NSim)) / (NSim - 1));
	//double SE = SD / sqrt(NSim);

	// Cleanup; V2 use scoped pointer
	//delete myNormal;


	std::cout << "\nPrice, after discounting: " << price << ", " << std::endl;
	std::cout << "Number of times origin is hit: " << coun << endl;
	
	//std::cout << "\nSD:\t" << SD << endl;
	//std::cout << "\nSE:\t" << SE << endl;


	return 0;
}



/*

#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <list>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
*/


//*************** Note ****************
// The below functions "borrowed" from thread, "Level 9 Homework comments/questions",
// thread #29, dated 3/13/12, by Dr Duffy

// Some statistics-based functions
template <typename V>
boost::tuple<double, double> SumSquaresAndSum(const V& container)
{ // Sum and sum of squares of a container

	double sum = 0.0;
	double sumSquares = 0.0;

	std::for_each(container.begin(), container.end(), 
		[&sum, &sumSquares] (double d) { sum += d; sumSquares += d*d;});

	return boost::tuple<double, double> (sum, sumSquares);
}


template <typename V>
boost::tuple<double, double> StandardDeviationAndError(const V& container, double r, double T)
{ // Standard deviation and error

	double sum;;
	double sumSquares;
	double M = double(container.size());

	boost::tie(sum, sumSquares) = SumSquaresAndSum<V>(container);

	// Now compute SD and SE
	double SD = (sqrt(sumSquares - (sum*sum)/M) * exp(-2.0*r*T)) / (M - 1.0);
	double SE = SD/sqrt(M);

	return boost::tuple<double, double> (SD, SE);
}


