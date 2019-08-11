/* Option.hpp
//
// Base class for the European, American and other options
// a
//
// (C) Datasim Component Technology BV 2003-2011
*/

#ifndef ExactPricingMethods_hpp
#define ExactPricingMethods_hpp


#include <string>
#include <array>
#include <map>				// for map
#include <algorithm>
//#include "Option.h"
#include "EuropeanOption.h"

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions

using namespace std;
/*
class Option
{
private:
	// Gaussian functions: using Boost::Math library functions
	double n(double x) const;
	double N(double x) const;

	// Member data 
	double T;		// Strike price
	double K;		// Expiry date
	double sig;		// Volatility
	double r;		// Interest rate
	double S;		// Asset Price
	double b;		// Cost of carry

	string opt_type;// Option type: "C" = call, "P" = put
	string unam;	// Name of underlying asset

	// static data member for comparison of double variables
	// floating point precision factor
	static const double epsilon;

public:	// Public functions
	Option();										// Default call option
	Option(const map<string, double>& option_parameters,	// constructor
		const string& option_type, const string& security, const double& b_adjust = 0.0);
	Option(const Option& option2);			// Copy constructor
	Option(const string& optionType);				// Create option type
	virtual ~Option();								// destructor for base class

	Option& operator = (const Option& option2);	// assignment operator

	// Functions that calculate option price and sensitivities
	double Price(double U) const;							// use with default constructed EuroOption
	double Price() const;									// use with constructor
	double Delta(double U) const;							// use with default constructed EuroOption
	double Delta() const;									// use with constructor
	double Gamma(double U) const;							// use with default constructed EuroOption
	double Gamma() const;									// use with constructor
	double DeltaDividedDiff(double h);						// divided differences to approximate option sensitivities
	double GammaDividedDiff(double h);						// divided differences to approximate option sensitivities

	// Inline member functions to calculate d1 and d2
	double D1(const double U) const
	{
		return (log(U / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	}
	double D2(const double U) const { return (D1(U) - (sig * sqrt(T))); }

	// getter functions
	string OptionType() const { return opt_type; }			// return type of option
	string Underlying() const { return unam; }				// return type of underlying security
	double ParityFactor()const { return (K * exp(-r * T)); }	// return put-call parity factor	

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	// calculate and return a tuple of call and put prices at put-call parity
	boost::tuple<double, double> put_call_parity() const;
	// check if call and put prices at Stock price S make for a put-call parity
	bool check_put_call_parity(const double& call_price, const double& put_price) const;

	// print option parameters
	void Print() const;
};
*/

// store Test Parameter names and values into a Map<String, Double> container
void set_batch(map<string, double>& batch, const vector<string>& option_param,
	const vector<double>& option_param_val);

// **********************************************
// The following constants are used to create a Vector of Map containers to store the
// four Batches of test values, and, also for creating map<string, double> 
// containers to be used as input arguments to the constructor

const int map_size = 4;			// size of the Map Array

// create vector of test value strings: ["T", "K", "sig", "r", "S", "C", "P"]
const vector<string> test_str0{ "T", "K", "sig", "r", "S", "C", "P" };

// create vector of test value doubles
const vector<double> test_val[]
{
	{ 0.25, 65, 0.30, 0.08, 60, 2.13337, 5.84628 },
	{ 1.0, 100, 0.2, 0.0, 100, 7.96557, 7.96557 },
	{ 1.0, 10, 0.5, 0.12, 5, 0.204058, 4.07326 },
	{ 30.0, 100.0, 0.3, 0.08, 100.0, 92.1757, 1.2475 }
};


// **********************************************
// matrix_pricer()
// Argument list:
// price_matrix	-	a map<string, map<string, double>> that contains the option test parameters
//					The string stores the name of the parameter under test: "S", "T", "K", "r" ...
//					The map<string, double> contains a map of the test parameters' names as strings
//					and the test parameters' values as doubles
// prices		-	a vector<doubles> to store calculated Call or Put option prices
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
// b_adjust		-	a double that holds the cost of carry adjustment
void matrix_pricer(map<string, map<string, double>>& price_matrix, vector<double>& prices,
	const string option_type = "C", const string underlying = "Stock", const double& b_adjust = 0.0);

/*
void matrix_pricer(vector<map<string, double>>& price_matrix, vector<double>& prices,
	const string test_param, const double& param_end, const double& step_size,
	const string option_type = "C", const string underlying = "Stock",
	const double& b_adjust = 0.0);
*/


// vector_pricer()
// Takes as input a map<string, double> of test parameters and a vector<double> to store
// calculated call and put option prices
// A test parameter is monotonically increased while other test parameters are held constant
// For each step, the call or put price is calculated and stored in the vector<double>
//
// Argument list:
// test_params	-	a map<string, double> that contains the option test parameters
// prices		-	a vector of double to store calculated prices
// test_param	-	a string that holds the test parameter's string
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// option_type	-	a string that holds the type of option, "C" = call or "P" = put
// underlying	-	a string that holds the type of underlying security/asset
// b_adjust		-	a double that holds the cost of carry adjustment
void vector_pricer(map<string, double>& price_matrix, vector<double>& prices,
	const string test_param, const double& param_end, const double& step_size,
	const string option_type = "C", const string underlying = "Stock",
	const double& b_adjust = 0.0);


// ******************************************************************

// Typedef definition of pointer to const member function: used to pass member functions
// as arguments to functions
// We use in the declarations for vector_pricer_by_fn() and matrix_pricer_by_fn() functions,
// to pass either the Price(), Gamma(), or Delta() member functions as function arguments
// The pointer points to a const member function that takes a single argument double and
// returns a double
typedef double (EuropeanOption::* EuroMemFn)(double) const;		// for EuropeanOption
//double (EuropeanOption::* europ)(double) const = &EuropeanOption::Price;
//double (EuropeanOption::* amer)(double) const = &AmericanOption::Price;
//typedef double (AmericanOption::* AmerMemFn)(double) const;		// for AmericanOption

// vector_pricer_by_fn()
// Takes as input a map<string, double> of test parameters and a map<string, vector<double>>
// to store calculated call and put option prices, or, various greeks' measures like Deltas
// and Gammas
// A test parameter is monotonically increased while other test parameters are held constant
// For each step, the relevant member function, Price(), Gamma(), or Delta() is calculated,
// and stored in the map<string, vector<double>> with the name of the relevant member
// function
//
// Argument list:
// test_params	-	a map<string, double> that contains the option test parameters
// measures		-	a map<string, vector<double>> to store calculated prices/values
// test_param	-	a string that holds the test parameter's string
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// fn_ptr		-	a EuropeanOption pointer to member function
//					(allows us to choose the requisite member function for testing)
// fn_name		-	a member function name
//					(to be used as a tag for the output vector of values)
// option_type	-	a string that holds the type of option, "C" = call or "P" = put
// underlying	-	a string that holds the type of underlying security/asset
// b_adjust		-	a double that holds the cost of carry adjustment
//
// option_type, underlying, and b_adjust default to "C" for call options, "Stock" for the
// underlying security/asset, and 0.0 for the adjustment for Stock, respectively
void vector_pricer_by_fn(const map<string, double>& test_params, map<string, vector<double>>& measures,
	const string test_param, const double& param_end, const double& step_size,
	const EuroMemFn fn_ptr, const string fn_name,
	const string option_type = "C", const string underlying = "Stock", const double& b_adjust = 0.0);


// matrix_pricer_by_fn()
// Takes as input a map<string, map<string, double>> of test parameters and a
// map<string, vector<double>> to store calculated call and put option prices with a string
// identifier
// The map<string, map<string, double> container includes the parameter to be tested, the
// list of other parameters that are held constant, and the step size and end value of the
// test parameter
// vector_pricer_by_fn() function is called to calculate and store the values/prices in a vector
//
// Argument list:
// price_matrix	-	a map<string, map<string, double>> that contains the option test parameters
// measures		-	a map<string, vector<double>> to store calculated Call or Put option prices
//					in a vector with a string identifier
// fn_ptr		-	a EuropeanOption pointer to member function
//					(allows us to choose the requisite member function for testing)
// fn_name		-	a member function name
//					(to be used as a tag for the output vector of values)
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
// b_adjust		-	a double that holds the cost of carry adjustment
void matrix_pricer_by_fn(
	map<string, map<string, double>>& price_matrix, map<string, vector<double>>& prices,
	const EuroMemFn fn_ptr, const string fn_name, const string option_type = "C",
	const string underlying = "Stock", const double& b_adjust = 0.0);


// **********************************************
/* Divided Difference:

Formulas:

Delta may be estimated by twking the first derivative of the option price function
V = Option price, S = Asset price, h = Delta change in Asset price

d = (V(S + h) - V(S - h)) / 2h

We use our matrix_pricer with S constant and vary the value of h

*/

// generate a range of doubles for h
template<typename ForwardIterator, typename T>
void strided_iota(ForwardIterator first, ForwardIterator last, T value, T stride)
{
	while (first != last)
	{
		*first++ = value;
		value *= stride;
	}
}


// testing ****************************
// WORKING
// does part A, EuroOption basics
// test prices()
void prices(EuropeanOption option, vector<double>& option_prices,
	string test_param, double param_start, double param_end, double step);

// test v_pricer()
//vector<double> v_pricer(vector<EuropeanOption>& test_option);
void v_pricer(vector<EuropeanOption>& test_option, vector<double>& prices);

// testing ****************************
// WORKING
// does part A, EuroOption basics
// test m_pricer()
//map<string, vector<double>> m_prices(EuropeanOption& option, map<string, vector<double>>& params);
void m_prices(EuropeanOption& option, map<string, vector<double>>& params,
	map<string, vector<double>>& prices);


// testing ****************************
// --- not yet WORKING
// does part A, EuroOption basics
// prices()
void prices_fn(EuropeanOption& option, map<string, vector<double>>& prices_map, EuroMemFn fn_ptr,
	string fn_name, string test_param, double param_start, double param_end, double step);

// vector<double>& option_prices, 


#endif
