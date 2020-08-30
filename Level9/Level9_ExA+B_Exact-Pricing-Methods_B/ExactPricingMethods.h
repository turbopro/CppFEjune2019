/* ExactPricingMethods.h

Header file for declarations of helper functions for the European and
American options
 
*/

#ifndef ExactPricingMethods_hpp
#define ExactPricingMethods_hpp


#include <string>
#include <array>
#include <map>				// for map
#include <algorithm>
#include "EuropeanOption.h"

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions

using namespace std;

// Store test parameter names and values for Batches 1 thru 4 into a
// Map<String, Double> container
void set_batch(map<string, double>& batch, const vector<string>& option_param,
	const vector<double>& option_param_val);

// **********************************************
// The following constants are used to create a Vector of Map containers to store the
// four Batches of test values, and, also for creating map<string, double> 
// containers to be used as input arguments to the option constructor

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


// ******************************************************************

// Typedef definition of pointer to member function: used to pass member functions
// as arguments to functions
// We use in the declarations for vector_pricer() and matrix_pricer() functions,
// to pass either the Price(), Gamma(), or Delta() member functions as function arguments,
// and also to set the range of values for any of the option parameters to be tested
// "EuroPriceFn" is a function pointer to a const member function that takes a single
// argument double and returns a double: used to call an option price and/or sensitivities
// method
typedef double (EuropeanOption::* EuroPriceFn)(double) const;

// EuroSetFn is a function pointer to a member function that takes a single argument
// double with no return value: used to set an option parameter value
typedef void(EuropeanOption::* EuroSetFn)(double);


//-------------------------------------------
// vector and matrix pricer functions
//-------------------------------------------
// vector_pricer() 4-argument version
// Takes an option, a vector of double for output, a function pointer to a
// member setter function, and a vector of doubles with input parameters
// We use this function to calculate the option price for an option test
// parameter over a range of values
// option			-	input option with the test parameters
// option_prices	-	output vector for calculated option prices
// p_setter_fn		-	function pointer to member setter function
// param_vec		-	vector of input parameters
void vector_pricer(EuropeanOption& option, vector<double>& option_prices,
	const EuroSetFn p_setter_fn, const vector<double>& param_vec);


// vector_pricer() 5-argument version
// Takes an extra function pointer to a member function that calculates an option
// price, delta or gamma
// option			-	input option with the test parameters
// option_prices	-	output vector for calculated option prices
// p_setter_fn		-	function pointer to member setter function
// p_price_fn		-	function pointer to member function for price and sensitivities
// param_vec		-	vector of input parameters
void vector_pricer(EuropeanOption& option, vector<double>& option_prices,
	const EuroSetFn p_setter_fn, const EuroPriceFn p_price_fn, const vector<double>& param_vec);


// matrix_pricer()
// Takes an option, a map of input prameters, a map of output option prices,
// and a map of function pointers to member setter functions
// The map with the input parameters includes a vector of doubles for the test
// parameter's initial value, start value, end value, and step size, with a
// string identifier as its key.
// The map with the option prices includes a vector of doubles of the
// calculated option prices, with a string identifier for the test parameter
// The map with the function pointer to member setter functions includes a 
// function pointer and a string idenfier to the member setter function
// This function loops over the input map parameters, and for each map element
// sets the option test parameter, then calls the Price() function
// The returned option price is added to the output map vector along with the
// relevant test parameter as an identifier
// option			-	input option with the test parameters
// params			-	input map of parameters
// option_prices_map	-	map of output prices with a string key as an identifier
// p_setter_fn		-	map of function pointers to member setter functions
void matrix_pricer(EuropeanOption& option, const map<string, vector<double>>& params,
	map<string, vector<double>>& option_prices_map, const map<string, EuroSetFn> p_setter_fn);


// matrix_pricer()
// This version takes an additional argument, a function pointer to a price and/or
// sensitivities member function
// We use this version to test each option parameter over a range of values for each
// option price or option delta or option gamma functions
// p_price_fn		-	map of function pointers to member setter functions
// fn_name			-	name of the price and sensitivities member functions
void matrix_pricer(EuropeanOption& option, const map<string, vector<double>>& params,
	map<string, vector<double>>& prices_map, const EuroPriceFn p_price_fn,
	const map<string, EuroSetFn> p_setter_fn);


// generate a range of values: use to generate a range of doubles for h
template<typename ForwardIterator, typename T>
void strided_iota(ForwardIterator first, ForwardIterator last, T value, T stride)
{
	while (first != last)
	{
		*first++ = value;
		value *= stride;
	}
}


// display prices and/or option sensitivity measures
void display_measures(map<string, vector<double>> option_measures, string option_type = "C");
void display_measures(vector<double> option_measures, string option_type = "C");

#endif


