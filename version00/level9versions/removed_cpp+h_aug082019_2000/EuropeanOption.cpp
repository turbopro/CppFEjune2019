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
/*
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

*/
/////////////////////////////////////////////////////////////////////////////////////

// default constructor
// default constructor takes default values, which includes a value for S
EuropeanOption::EuropeanOption()
	: Option()
	//T(0.5), K(110.0), sig(0.2), r(0.05), S(100.0), opt_type("C"), unam("Stock"), b(0.05)
{}



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
	:	Option{ op, ot, security, b_adjust } {}
/*
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
*/


// copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& o2)
	: Option { o2 } {}
	//T(o2.T), K(o2.K), sig(o2.sig), r(o2.r), S(o2.S), 
	//opt_type(o2.opt_type), unam(o2.unam), b(o2.b) {}

/*
// Set option type
EuropeanOption::EuropeanOption (const string& optionType)
{
	if (optionType == "c" || optionType == "C")
		opt_type = "C";
	else if (optionType == "p" || optionType == "P")
		opt_type = "P";
	else opt_type = "C";
}
*/

// destructor (virtual for base class)
EuropeanOption::~EuropeanOption() {}


// assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this == &option2) return *this;

	Option::operator=(option2);
	//r = option2.r; sig = option2.sig; K = option2.K; T = option2.T;
	//b = option2.b; S = option2.S;
	//opt_type = option2.opt_type; unam = option2.unam;

	return *this;
}



/*
// Functions that calculate option price and sensitivities
// Use with default constructor: asset price is accepted here as a single argument double
double EuropeanOption::Price(double U) const
{
	// Use member functions D1 and D2 only when needed; no need for temporary variables
	// return either call price or put price
	//return (opt_type == "C" || opt_type == "c") ?
		//(U * exp((b - r) * T) * N(D1(U))) - (K * exp(-r * T) * N(D2(U))) :	// call price
		//(K * exp(-r * T) * N(-(D2(U)))) - (U * exp((b - r) * T) * N(-(D1(U))));	// put price
	return Price(U);
}

// Use with constructor: asset price is provided within the input map container
// call single argument Price member function
double EuropeanOption::Price() const
{
	return Price();
}
*/

/*
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

*/