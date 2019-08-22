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


////////////////////////////////////////////////////////
// Helper Functions
//*************** Note ****************
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
template <typename V>
boost::tuple<double, double> SumSquaresAndSum(const V& container)
{ // Sum and sum of squares of a container

	double sum = 0.0;
	double sumSquares = 0.0;

	std::for_each(container.begin(), container.end(),
		[&sum, &sumSquares](double d) { sum += d; sumSquares += d * d; });

	return boost::tuple<double, double>(sum, sumSquares);
}

template <typename V>
boost::tuple<double, double> StandardDeviationAndError(const V& container, double r, double T)
{ // Standard deviation and error

	double sum;;
	double sumSquares;
	double M = double(container.size());

	boost::tie(sum, sumSquares) = SumSquaresAndSum<V>(container);

	// Now compute SD and SE
	double SD = (sqrt(sumSquares - (sum * sum) / M) * exp(-2.0 * r * T)) / (M - 1.0);
	double SE = SD / sqrt(M);

	return boost::tuple<double, double>(SD, SE);
}



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



#endif