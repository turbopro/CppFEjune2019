// OptionData.hpp
//
// Encapsulate option data.
//
// (C) Datasim Education BV 2008-2011

#ifndef OptionData_HPP
#define OptionData_HPP

#include <algorithm> // for max()
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

using namespace std;
//using namespace SDEDefinition;

// Encapsulate all data in one place
// Perhaps this may be served better through the use of a class definition?
struct OptionData
{ // Option data + behaviour

	double K, T, r, sig;

	// Extra data 
	double H;		// down and out barrier
	double D;		// dividend
	double betaCEV;	// elasticity factor (CEV model)
	double scale;	// scale factor in CEV model

	int type;		// 1 == call, -1 == put

	double myPayOffFunction(double S)
	{ // Payoff function
		if (type == 1) { return max(S - K, 0.0); }	// Call
		else { return max(K - S, 0.0); }			// Put
	}
};

// SDEDefinition
// Namespace definition to hold together a pointer to an OptionData object
// and the associated SDE functions to be used for the simulations
// Perhaps this may be served better by use of a class definition 
namespace SDEDefinition
{ // Defines drift + diffusion + data

	OptionData* data;				// The data for the option MC

	double drift(double t, double X)
	{ // Drift term
		return (data->r) * X;		// r - D
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


////////////////////////////////////////////////////////
// Helper Functions
// *************** Note ****************
// The below temp[late functions, SumSquaresAndSum and StandardDeviationAndError, are
// "borrowed" as is from thread, "Level 9 Homework comments/questions", thread #29,
// dated 3/13/12, by Dr Duffy

template <typename V>
boost::tuple<double, double> SumSquaresAndSum(const V& container);

template <typename V>
boost::tuple<double, double> StandardDeviationAndError(const V& container, double r, double T);


////////////////////////////////////////////////////////
/// Utility Funtions

template <class T>
void print(const std::vector<T>& vec);


/////////////////////////////////////////////////////////
// Template functions definitions

// Some statistics-based functions

// Sum and Sum-of-Squares of the elements of a container
// Loop through the container
// Use a Lamda to compute the sum and the sum of squares for each element
// Return a tuple with the two calculated values
template <typename V>
boost::tuple<double, double> SumSquaresAndSum(const V& container)
{
	double sum = 0.0;
	double sumSquares = 0.0;

	std::for_each(container.begin(), container.end(),
		[&sum, &sumSquares](double d) { sum += d; sumSquares += d * d; });

	return boost::tuple<double, double>(sum, sumSquares);
}

// Standard Deviation and Standard Error
// Use SumSquaresAndSum to get sum and sum-of-squares of a container
// Use the returned values to compute Standard Deviation and Standard Error
// Return a tuple with the two calculated values
template <typename V>
boost::tuple<double, double> StandardDeviationAndError(const V& container, double r, double T)
{
	double sum;;
	double sumSquares;
	double M = double(container.size());

	boost::tie(sum, sumSquares) = SumSquaresAndSum<V>(container);

	// Now compute SD and SE
	double SD = (sqrt(sumSquares - (sum * sum) / M) * exp(-2.0 * r * T)) / (M - 1.0);
	double SE = SD / sqrt(M);

	return boost::tuple<double, double>(SD, SE);
}


// A generic print function for vectors
template <class T>
void print(const std::vector<T>& vec)
{
	std::cout << std::endl << "Size of vector is " << vec.size() << "\n[";

	// We must use a const iterator here, otherwise we get a compiler error.
	const std::vector<T>::iterator i;
	for (i = vec.begin(); i != vec.end(); ++i) 
		std::cout << *i << ",";

	std::cout << "]\n";
}


////////////////////////////////////////////////////////////
// Test Option Parameters
//
// Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
// Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557)
// Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326)
// Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).


#endif