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

// In general, we would use similar functions in Boost::Math Toolkit
// And assuming that the distribution for the underlying Stock Price 
// follows a normal distribution with mean = 0.0, std dev = 1.0, we
// would re-write n(x) and N(x) as follows:

// standard normal probability density function: use boost C++ library
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

/*
// calculate d1 and d2
double EuropeanOption::D1D2Probabilities() const
{
	double tmp = sig * sqrt(T);
	d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	d2 = d1 - tmp;
}
*/

double EuropeanOption::CallPrice(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));
}

double EuropeanOption::PutPrice(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));
}

double EuropeanOption::CallDelta(double U) const
{
	//std::cout << "\ninside " << __FUNCTION__ << ", U " << U << std::endl;
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * N(d1);
}

double EuropeanOption::PutDelta(double U) const
{
	//std::cout << "\ninside " << __FUNCTION__ << ", U: " << U << std::endl;
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}

// CallGamma()
double EuropeanOption::CallGamma(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	//return (exp(-r * T) * K * n(d2)) / (S * S * sig * sqrt(T));
	return (exp((b-r) * T) * n(d1)) / (S * sig * sqrt(T));
}

// PutGamma()
double EuropeanOption::PutGamma(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	//return (exp(-r * T) * K * n(d2)) / (S * S * sig * sqrt(T));
	return (exp((b - r) * T) * n(d1)) / (S * sig * sqrt(T));
}

/*
// CallRho()
double EuropeanOption::CallRho(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return K * exp(-r * T) * T * N(d2);
}

// PutRho()
double EuropeanOption::PutRho(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return -(K * exp(-r * T) * T * N(-d2));
}
*/


/////////////////////////////////////////////////////////////////////////////////////
/*
void EuropeanOption::init()
{	// Initialise all default values

	// Default values
	r = 0.05;
	sig= 0.2;

	K = 110.0;
	T = 0.5;

	b = r;			// Black and Scholes stock option model (1973)
	
	opt_type = "C";		// European Call Option (this is the default type)
	unam = "Stock";
}
void EuropeanOption::copy( const EuropeanOption& o2)
{

	r	= o2.r;
	sig = o2.sig;	
	K	= o2.K;
	T	= o2.T;
	b	= o2.b;
	S	= o2.S;
	
	optType = o2.optType;
	unam = o2.unam;	
}
*/

// default constructor
EuropeanOption::EuropeanOption()
	: T(0.5), K(110.0), sig(0.2), r(0.05), S(100.0),		// S set at 100 as default
	opt_type("C"), unam("Stock"), b(0.05) {}


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
// We employ the colon initiliser to set data members
// For the different types of underlying securities, additional initilisation occurs in the 
// curly braces
// option type is checked for validity; throw exception if invalid value
// underlying security type is checked for validity; throw exception if invalid value
EuropeanOption::EuropeanOption(const map<string, double>& op, const string& ot,
	const string& security, const double& b_adjust)
	: T(op.at("T")), K(op.at("K")), sig(op.at("sig")), r(op.at("r")), 
	S(op.at("S")), b(b_adjust)
{
	// throw InvalidUnderlyingException if underlying security type not valid
	if (security == "Currency" || security == "Future" ||
		security == "Stock" || security == "Index") unam = security;
	else throw InvalidUnderlyingException(security);
	
	if (security == "Stock") b = r;			// Black and Scholes stock option model (1973)
	else if (security == "Future") b = 0;
	else b = r - b_adjust;				// security = Currency or Index

	// throw InvalidOptionTypeException if option_type not valid
	if (ot == "C" || ot == "c" || ot == "P" || ot == "p") opt_type = ot;
	else throw InvalidOptionTypeException(ot);
}

// copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& o2)
	: T(o2.T), K(o2.K), sig(o2.sig), r(o2.r), S(o2.S), 
	opt_type(o2.opt_type), unam(o2.unam), b(o2.b) {}

EuropeanOption::EuropeanOption (const string& optionType)
{	// Create option type

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

	r = option2.r;
	sig = option2.sig;
	K = option2.K;
	T = option2.T;
	b = option2.b;
	S = option2.S;
	opt_type = option2.opt_type;
	unam = option2.unam;

	return *this;
}

// Functions that calculate option price and sensitivities



// use with default constructor: asset price is accepted here as a single argument double
double EuropeanOption::Price(double U) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	//return (U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	
	return (opt_type == "C" || opt_type == "c") ?
		(U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2)) :	// call price
		(K * exp(-r * T) * N(-d2)) - (U * exp((b - r) * T) * N(-d1));	// put price

	/*
	if (opt_type == "C" || opt_type == "c")
	{
		//cout << "calling call option on a/an " << unam << endl;
		//return CallPrice(U);
		return (U * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
	else
	{
		//cout << "calling put option on a/an " << unam << endl;
		//return PutPrice(U);
		return (K * exp(-r * T) * N(-d2)) - (U * exp((b - r) * T) * N(-d1));
	}
	*/
}

// Use with constructor: asset price is provided within the input map container
double EuropeanOption::Price() const
{
	return Price(S);
}

// use with default constructor: asset price is accepted here as a single argument double
double EuropeanOption::Delta(double U) const 
{
	//double tmp = sig * sqrt(T);
	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));

	//return exp((b - r) * T) * N(d1);
	
	return (opt_type == "C" || opt_type == "c") ?
		exp((b - r) * T) * N(d1) :			// call delta
		exp((b - r) * T) * (N(d1) - 1.0);	// put delta

	/*
	if (opt_type == "C" || opt_type == "c")
		return CallDelta(U);
	else
		return PutDelta(U);
	*/
}

// Use with constructor: asset price is provided within the input map container
double EuropeanOption::Delta() const
{
	return Delta(S);
}


double EuropeanOption::Gamma(double U) const		// use with default constructor
{
	if (opt_type == "C")
		return CallGamma(U);
	else
		return PutGamma(U);
}

double EuropeanOption::Gamma() const
{
	//if (opt_type == "C")
		//return CallGamma(S);
	//else
		//return PutGamma(S);
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
// Returns a tuple of doubles: Put price and corresponding Call price
// ParityFactor() is an inline member method that returns the value of Ke^(-rT)
// Throw InvalidOptionTypeException if option type is incorrect
boost::tuple<double, double> EuropeanOption::put_call_parity() const
{
	if (OptionType() == "C" || OptionType() == "c")				// check option type
	{
		double call_price = Price();		// get call price
		//double parity_put_price = call_price - S + ParityFactor();	  // calculate put price

		//return boost::tuple<double, double>(parity_put_price, call_price);	// tuple(put_price, call_price)
		// tuple(put_price, call_price)
		return boost::tuple<double, double>((call_price - S + ParityFactor()), call_price);	
	}
	else if (OptionType() == "P" || OptionType() == "p")
	{
		double put_price = Price();			// get put price
		//double parity_call_price = put_price + S - ParityFactor();	// calculate call price

		//return boost::tuple<double, double>(put_price, parity_call_price);	// tuple(put_price, call_price)
		// tuple(put_price, call_price)
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

// matrix_pricer()
// Has seven input arguments:
// price_matrix	-	a vector of map<string, double> that contains the option test parameters
// prices		-	a vector<doubles> to store calculated Call or Put option prices
// test_param	-	a string that holds the test parameter's character
// param_start	-	a double that holds the value of the start value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
//
// Loop over from the test parameter start to end value in step_size steps
// In each iteration, create an anonymous EuropeanOption object using the constant test
// paramaters, and the current value of the increasing particular test parameter
// Call the Price() member method (single argument version) to retrieve the relevant Call 
// or Put option price
// Add the retrieved option price to the storage vector for prices and to the price
// matrix vector of map containers
// No return value; void function
// Both input vectors are reference objects whose values are updated during function execution
void matrix_pricer(vector<map<string, double>>& price_matrix, vector<double>& prices,
	const string test_param, const double& step_size,
	const string option_type, const string underlying)
{
	int i = 0;				// indexer
	double option_price;	// temp storage for calculated option price
	for (auto it = price_matrix.begin(); it != price_matrix.end(); ++it, ++i)
	{
		(*it)[test_param] += (i*step_size);					// set test parameter values
		option_price = EuropeanOption(*it, option_type, underlying).Price();	// calculate option price
		prices.push_back(option_price);						// add option price to prices vector
		(*it).emplace(option_type, option_price);			// add option price to vector of map containers
	}
}

// vector_pricer() 
// Has nine input arguments:
// test_params	-	a map<string, double> that contains the option test parameters
// prices		-	a map<string, vector<double>> to store calculated prices/values
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// fn_ptr		-	a EuropeanOption pointer to member function
// fn_name		-	a member function name
// test_param	-	a string that holds the test parameter's character
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
//
// Create a temporary vector of doubles to stores calculated prices/values
// Loop over from the test parameter start to end value in step_size steps
// In each iteration:
//	Get and store values/prices in temp_vec
//	We use std::invoke which takes as arguments the pointer to member function,
//	an anonymous EuropeanOption, and the current test parameter value, which is
//	the argument to the member function 
// Add the member function name and vector of calculated prices/values to the prices map
void vector_pricer(const map<string, double>& test_params, map<string, vector<double>>& prices,
	const double& param_end, const double& step_size, const EuroMemFn fn_ptr, 
	const string fn_name, const string test_param, const string option_type, 
	const string underlying)
{
	// Create temporary vector
	vector<double> prices_vals_vec;

	// Loop over test parameter range of values; get and store values/prices
	//for (double param_idx = test_params["S"]; param_idx < param_end; param_idx += step_size)
	for (double param_idx = test_params.at("S"); param_idx < param_end; param_idx += step_size)
	{		
		prices_vals_vec.push_back(
			std::invoke(fn_ptr, EuropeanOption(test_params, option_type, underlying), param_idx));
	}

	// assign member funtion name and vector of computed values to prices map
	prices[fn_name] = prices_vals_vec;
	//prices.at(fn_name) = prices_vals_vec;

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
		vector_pricer(*it, prices, param_end, step_size, fn_ptr, fn_name, test_param,
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