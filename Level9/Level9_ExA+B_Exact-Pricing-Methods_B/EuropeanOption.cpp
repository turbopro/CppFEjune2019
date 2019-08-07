// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// (C) Datasim Component Technology BV 2003-2011
//


#include "EuropeanOption.hpp"
#include "EuropeanOptionException.h"
#include <cmath>
#include <iostream>
#include <string>
#include <map>

//using namespace boost::math;

// definition of static data member for comparison of double variables
const double EuropeanOption::epsilon = 1.0e-05;

//////////// Gaussian functions /////////////////////////////////

// From the Black-Scholes stock option model, we assume, inter alia, 
// that the distribution for the underlying Stock Price follows a 
// normal distribution with mean = 0.0, std dev = 1.0.
// Thus, we re-write n(x) and N(x) using the Boost::Math libraries as follows:

// standard normal probability density function
double EuropeanOption::n(double x) const
{  
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

// standard normal cumulative distribution function
double EuropeanOption::N(double x) const
{ // The approximation to the cumulative normal distribution

	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return cdf(myNormal, x);
}


// Kernel Functions (Haug)
// all moved to public member functions

/////////////////////////////////////////////////////////////////////////////////////

// default constructor
// default constructor takes default values, which includes a value for S
EuropeanOption::EuropeanOption()
	: T(0.5), K(110.0), sig(0.2), r(0.05), S(100.0), opt_type("C"), unam("Stock"), b(0.05) {}

// constructor takes four arguments: 
// op		-	map<string, vector> with test parameter values
//				We use a map to map option parameter to value for ease of reference 
// ot		-	option type
// security	-	Name of underlying security type
// b_adjust	-	Value to be used to adjust b: adjusted by q = dividend, or foreign interest 
//				rate, R
//				For a Stock, b = r; for an index, b = r - q(dividend); for a future, b = 0.0;
//				for a currency, b = r - R(foreign exchange interest rate)
//
// We employ the colon initialiser to set data members
// For the different types of underlying securities/assets, additional initilisation occurs in the 
// curly braces
// Input value checking is done here, which may incur cost in construction of the option,
// but input errors should be intercepted at input time: perhaps a check_input_valid class
// may be more optimal
// Option type is checked for validity; throw exception if invalid value
// Underlying security type is checked for validity; throw exception if invalid value
// Throw InvalidParameterValueException if either of parameter values, T, K, S, or sig is zero
// T, K, S, or sig will create divide by zero errors
// Moreover, S = 0 is not a sensible value for an asset price
EuropeanOption::EuropeanOption(const map<string, double>& op, const string& ot,
	const string& security, const double& b_adjust)
	: T(op.at("T")), K(op.at("K")), sig(op.at("sig")), r(op.at("r")), 
	S(op.at("S")), b(b_adjust)
{
	// check for valid input values
	// throw InvalidUnderlyingException if underlying security type not valid
	if (security == "Currency" || security == "Future" ||
		security == "Stock" || security == "Index") unam = security;
	else throw InvalidUnderlyingException(security);

	// throw InvalidOptionTypeException if option_type not valid
	if (ot == "C" || ot == "c" || ot == "P" || ot == "p") opt_type = ot;
	else throw InvalidOptionTypeException(ot);

	// throw InvalidParameterValueException if either of parameter values, T, K, S,
	// or sig is zero
	if (T == 0 || K == 0 || S == 0 || sig == 0)
		throw InvalidParameterValueException("0");

	// set b based on type of underlying asset
	if (security == "Stock") b = r;		// Black and Scholes stock option model (1973)
	else if (security == "Future") b = 0;
	else b = r - b_adjust;				// asset/security = Currency or Index
}

// copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& o2)
	: T(o2.T), K(o2.K), sig(o2.sig), r(o2.r), S(o2.S), 
	opt_type(o2.opt_type), unam(o2.unam), b(o2.b) {}

// Set option type
EuropeanOption::EuropeanOption (const string& optionType)
{
	if (optionType == "c" || optionType == "C")
		opt_type = "C";
	else if (optionType == "p" || optionType == "P")
		opt_type = "P";
	else opt_type = "C";
}

// destructor (virtual for base class)
EuropeanOption::~EuropeanOption() {}

// assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this == &option2) return *this;

	r = option2.r; sig = option2.sig; K = option2.K; T = option2.T;
	b = option2.b; S = option2.S;
	opt_type = option2.opt_type; unam = option2.unam;

	return *this;
}

// Functions that calculate option price and sensitivities
// Use with default constructor: asset price is accepted here as a single argument double
double EuropeanOption::Price(double U) const
{
	// Use member functions D1 and D2 only when needed; no need for temporary variables
	// return either call price or put price
	return (opt_type == "C" || opt_type == "c") ?
		(U * exp((b - r) * T) * N(D1(U))) - (K * exp(-r * T) * N(D2(U))) :	// call price
		(K * exp(-r * T) * N(-(D2(U)))) - (U * exp((b - r) * T) * N(-(D1(U))));	// put price
}

// Use with constructor: asset price is provided within the input map container
// call single argument Price member function
double EuropeanOption::Price() const
{
	return Price(S);
}

// Use with default constructor: asset price is accepted here as a single argument double
double EuropeanOption::Delta(double U) const 
{
	// return either call delta or put delta
	return (opt_type == "C" || opt_type == "c") ?
		exp((b - r) * T) * N(D1(U)) :		// call delta
		//exp((b - r) * T) * (N(D1(U)) - 1.0);	// put delta
		-(exp((b - r) * T) * N(-(D1(U))));	// put delta
}

// Use with constructor: asset price is provided within the input map container
// call single argument Delta member function
double EuropeanOption::Delta() const
{
	return Delta(S);
}

// Use with default constructor: asset price is accepted here as a single argument double
// Gamma value is the same for call or put options
double EuropeanOption::Gamma(double U) const
{
	return (exp(-r * T) * K * n(D2(U))) / (S * S * sig * sqrt(T));
	//return (exp((b - r) * T) * n(D1(U))) / (S * sig * sqrt(T));
}

// Use with constructor: asset price is provided within the input map container
// call single argument Gamma member function
double EuropeanOption::Gamma() const
{
	return Gamma(S);
}

// Modifier functions
void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)

	if (opt_type == "C")
		opt_type = "P";
	else
		opt_type = "C";
}


// print option parameters
void EuropeanOption::Print() const
{
	std::cout << "Option Parameters:\n"
		<< "\nOption Type:\t" << opt_type
		<< "\nUnderlying Security:\t" << unam
		<< "\nT: " << T
		<< "\nK: " << K
		<< "\nsig: " << sig
		<< "\nr: " << r
		<< "\nb: " << b
		<< "\nS: " << S << endl;
}

// set_batch() definition
// set batch values from option_param and option_param_val vectors 
void set_batch(map<string, double>& batch, const vector<string>& option_param, 
	const vector<double>& option_param_val)
{
	for (unsigned int i = 0; i < option_param_val.size(); i++)
	{
		batch[option_param[i]] = option_param_val[i];
	}
}

// put_call_parity() function: get the Call or Put price of the Stock option
// Calculate the relevant Put price if option type is a call option; conversely,
// calculate the Call price if option type is a put option
// Use the put-call-parity formula, C + Ke^(-rT) = P + S, to calculate the 
// corresponding Put price given a Call price, or, conversely, Call price given 
// a Put price
// Returns a tuple of doubles, Put price with corresponding Call price
// ParityFactor() is an inline member method that returns the value of Ke^(-rT)
// Throw InvalidOptionTypeException if option type is incorrect
boost::tuple<double, double> EuropeanOption::put_call_parity() const
{
	if (OptionType() == "C" || OptionType() == "c")				// check option type
	{
		double call_price = Price();		// get call price
		return boost::tuple<double, double>((call_price - S + ParityFactor()), call_price);	
	}
	else if (OptionType() == "P" || OptionType() == "p")
	{
		double put_price = Price();			// get put price
		return boost::tuple<double, double>(put_price, (put_price + S - ParityFactor()));
	}
	else
	{
		// throw exception
		throw InvalidOptionTypeException(OptionType());
	}	
}

// Check if call and put prices for a given stock option at price S make for a put-call parity
bool EuropeanOption::check_put_call_parity(const double& call_price, const double& put_price) const
{
	// get parity put and call prices for Stock at price S
	boost::tuple<double, double> parity_prices(put_call_parity());

	// We use static data member epsilon for comparison of calculated vs given call/put prices
	// return true if prices are "equal": that is, if the prices lie within epsilon tolerance
	return (std::abs(put_price - parity_prices.get<0>()) < epsilon &&
			std::abs(call_price - parity_prices.get<1>()) < epsilon);
}

// create vector of doubles: increasing/decreasing monotonically
//vector<double> vec_range(const double& start, const double& end, const int& length)
void vec_range(vector<double>& vec, const double& start, const double& end)
{
	// create a vector of length num
	size_t sz = vec.size();

	// now assign the values to the vector
	for (size_t i = 0; i < sz; i++)
	{
		vec[i] = start + i * ((end - start) / sz);
	}
	//return vec;
}

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
//
// Loop over the test parameter from start to end value in step_size steps:
//	For each iteration
//	  Set test_param to the current test value
//	  Get option price from an anonymous EuropeanOption object
//	  Add to output vector  
void vector_pricer(map<string, double>& test_params, vector<double>& prices,
	const string test_param, const double& param_end, const double& step_size,
	const string option_type, const string underlying, const double& b_adjust)
{
	for (double param_idx = test_params.at(test_param); param_idx <= param_end; param_idx += step_size)
	{
		test_params[test_param] = param_idx;
		prices.push_back(EuropeanOption(test_params, option_type, underlying, b_adjust).Price());
	}
}

// matrix_pricer()
// Takes as input a map<string, map<string, double>> of test parameters and a vector<double>
// to store calculated call and put option prices
// We loop through the map and call the vector_pricer() function that calculates and stores
// the prices in the vector<double>
//
// Agument list:
// price_matrix	-	a vector of map<string, map<string, double>> that contains the option
//					test parameters
// prices		-	a vector<double> to store calculated Call or Put option prices
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
// b_adjust		-	a double that holds the cost of carry adjustment
//
// Loop over the test_params map with an iterator
// Call vector_pricer() to calculate and store the option prices
// The map and vector are reference objects whose values are updated during 
// function execution
void matrix_pricer(map<string, map<string, double>>& price_matrix, vector<double>& prices, 
	const string option_type, const string underlying, const double& b_adjust)
{
	
	for (auto it = price_matrix.begin(); it != price_matrix.end(); ++it)
	{
		vector_pricer(it->second, prices, it->first, it->second.at("param_end"), 
			it->second.at("step_size"), option_type, underlying, b_adjust);
	}
}

/*
void matrix_pricer(vector<map<string, double>>& price_matrix, vector<double>& prices,
	const string test_param, const double& param_end, const double& step_size,
	const string option_type, const string underlying, const double& b_adjust)
*/


// vector_pricer_by_fn() 
// Has nine input arguments:
// test_params	-	a map<string, double> that contains the option test parameters
// prices		-	a map<string, vector<double>> to store calculated prices/values
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// fn_ptr		-	a EuropeanOption pointer to member function
//					(we choose the requisite member function for testing)
// fn_name		-	a member function name
//					(to be used as a tag for the output vector of values)
// test_param	-	a string that holds the test parameter's string
// option_type	-	a string that holds the type of option, "C" = call or "P" = put
// underlying	-	a string that holds the type of underlying security/asset
//
// Create a temporary vector of doubles to store calculated prices/values
// Loop over from the test parameter start to end value in step_size steps:
//	In each iteration
//		Get and store values/prices in temp_vec
//		We use std::invoke which takes as arguments the pointer to member function,
//		an anonymous EuropeanOption, and the current test parameter value, the
//		argument to the member function 
// Add the member function name and vector of calculated prices/values to the prices map
void vector_pricer_by_fn(const map<string, double>& test_params, map<string, vector<double>>& prices,
	const double& param_end, const double& step_size, const EuroMemFn fn_ptr, 
	const string fn_name, const string test_param, const string option_type, 
	const string underlying)
{
	// Create temporary vector
	vector<double> prices_vals_vec;

	// Loop over test parameter range of values; get and store values/prices
	for (double param_idx = test_params.at(test_param); param_idx < param_end; param_idx += step_size)
	{		
		prices_vals_vec.push_back(
			std::invoke(fn_ptr, EuropeanOption(test_params, option_type, underlying), param_idx));
	}

	// assign member funtion name and vector of computed values to prices map
	prices[fn_name] = prices_vals_vec;
}

// matrix_pricer_by_fn()
void matrix_pricer_by_fn(
	const vector<map<string, double>>& price_matrix, map<string, vector<double>>& prices,
	const double& param_end, const double& step_size, const EuroMemFn fn_ptr,
	const string fn_name, const string test_param, const string option_type,
	const string underlying)
{
	for (auto it = price_matrix.begin(); it != price_matrix.end(); ++it)
	{
		vector_pricer_by_fn(*it, prices, param_end, step_size, fn_ptr, fn_name, test_param,
			option_type, underlying);
	}
}

//
// divided differences to approximate option sensitivities
// Delta approximation using formula: d = (V(S + h) - V(S - h)) / 2h
double EuropeanOption::DeltaDividedDiff(double h)
{
	double price_plus_h  = Price(S + h);	
	double price_minus_h = Price(S - h);
	return  (price_plus_h - price_minus_h) / (2 * h);
}

// divided differences to approximate option sensitivities
// Gamma approximation using formula: g = (V(S + h) - 2V(S) + V(S - h)) / h^2
double EuropeanOption::GammaDividedDiff(double h)
{
	double price_plus_h  = Price(S + h);
	double price_minus_h = Price(S - h);
	double price_at_S    = Price(S);
	return  (price_plus_h - (2 * price_at_S) + price_minus_h) / (h * h);
}