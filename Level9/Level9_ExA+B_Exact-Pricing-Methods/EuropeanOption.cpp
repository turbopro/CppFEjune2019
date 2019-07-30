// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// (C) Datasim Component Technology BV 2003-2011
//


#include "EuropeanOption.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <map>
//#include "Array.h"

//using namespace boost::math;

// static data member for comparison of double variables
const double EuropeanOption::epsilon = 1.0e-05;

//////////// Gaussian functions /////////////////////////////////

// In general, we would use similar functions in Boost::Math Toolkit
// And assuming that the distribution for the underlying Stock Price 
// follows a normal distribution with mean = 0.0, std dev = 1.0, we
// would re-write n(x) and N(x) as follows:

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
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;


	return exp((b-r)*T) * N(d1);
}

double EuropeanOption::PutDelta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}

// CallTheta()
double EuropeanOption::CallTheta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return - (exp((b - r) * T) * U * n(d1) * sig) / (2 * sqrt(T)) -
	//return -(U * exp((b - r) * T) * n(d1) * sig) / (2 * sqrt(T));// -
		(r * (K * exp(-r * T)) * N(d2)) + 
		((r - b) * (U * exp((b - r) * T) * N(d1)));
}

// PutTheta()
double EuropeanOption::PutTheta(double U) const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(U / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return -(U * exp((b - r) * T) * n(d1) * sig) / (2 * sqrt(T));// +
		//(r * (K * exp(-r * T)) * N(-d2)); //s-
		//((r - b) * (U * exp((b - r) * T) * N(-d1)));
}

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
	: T(0.5), K(110.0), sig(0.2), r(0.05), S(1.0),		// delisting threshold for a stock = $1.00
	opt_type("C"), unam("Stock"), b(0.05) {}


// constructor takes four arguments: 
// arg[0] = map with test parameter values
// arg[1] = option type
// arg[2] = underlying security type
// arg[3] = value to be used to adjust b: dividend or interest rate
EuropeanOption::EuropeanOption(const map<string, double>& op, const string& ot,
	const string& security, const double& b_adjust)
	: T(op.at("T")), K(op.at("K")), sig(op.at("sig")), r(op.at("r")), S(op.at("S")),
	opt_type(ot), unam(security), b(b_adjust)
{
	if (unam == "Stock") b = r;
	else if (unam == "Future") b = 0;
	else if (unam == "Currency" || unam == "Index") b = r - b_adjust;
	else b = r;		// default to Stock cost of carry: Black and Scholes stock option model (1973) 
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

	//init();
	//optType = optionType;

	//if (optType == "c")
	//	optType = "C";

}



EuropeanOption::~EuropeanOption()
{

}


EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{

	if (this == &option2) return *this;

	//copy (option2);
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
// use with constructor: asset price is provided within the input tuple
double EuropeanOption::Price() const
{
	if (opt_type == "C")
	{	
		cout << "calling call option on a/an " << unam << endl;
		return CallPrice(S);
	}
	else
	{
		cout << "calling put option on a/an " << unam << endl;
		return PutPrice(S);
	}
}

// use with default constructor: asset price is provided as a single argument double
double EuropeanOption::Price(double U) const
{
	if (opt_type == "C")
	{
		cout << "calling call option on a/an " << unam << endl;
		return CallPrice(U);
	}
	else
	{
		cout << "calling put option on a/an " << unam << endl;
		return PutPrice(U);
	}
}

double EuropeanOption::Delta(double U) const 
{
	if (opt_type == "C")
		return CallDelta(U);
	else
		return PutDelta(U);

}

double EuropeanOption::Delta() const
{
	if (opt_type == "C")
		return CallDelta(S);
	else
		return PutDelta(S);

}

double EuropeanOption::Theta(double U) const		// use with default constructor
{
	if (opt_type == "C")
		return CallTheta(U);
	else
		return PutTheta(U);
}

double EuropeanOption::Theta() const
{
	if (opt_type == "C")
		return CallTheta(S);
	else
		return PutTheta(S);
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
void set_batch(map<string, double>& batch, const vector<string>& S, const vector<double>& V)
{
	for (unsigned int i = 0; i < V.size(); i++)
	{
		batch[S[i]] = V[i];
	}
}

// put_call_parity() function: get the Call or Put price of the Stock option
// Calculate the relevant Put price if Call Price is retireved; calculate
// the Call price if Put price is retrieved
// Use the put-call-parity formula, C + Ke^(-rT) = P + S, to calculate
// Put price given Call price, or, conversely, Call price given Put price
// Returns a tuple of doubles: Put price and relevant Call price
// ParityFactor() returns the value of Ke^(-rT)
boost::tuple<double, double> EuropeanOption::put_call_parity() const
{
	// Get call and put prices from option
	// Calculate relevant put price when call price given
	// Calculate relevant call price when put price given
	// Calculate put or call parity price; return tuple with calculated prices
	if (OptionType() == "C")				// check option type
	{
		double call_price = Price();		// set call price
		double parity_put_price = call_price - S + ParityFactor();	  // calculate put price

		return boost::tuple<double, double>(parity_put_price, call_price);	// tuple(put_price, call_price)
	}
	else
	{
		double put_price = Price();
		double parity_call_price = put_price + S - ParityFactor();

		return boost::tuple<double, double>(put_price, parity_call_price);
	}

	return boost::tuple<double, double> (0.0, 0.0);
}

// Check if call and put prices for a given stock option at price S make for a put-call parity
bool EuropeanOption::check_put_call_parity(const double& call_price, const double& put_price) const
{
	// get parity put and call prices for Stock at price S
	boost::tuple<double, double> parity_prices(put_call_parity());

	// We use static data member epsilon for comparison of calculated vs given call/put prices
	// return true if prices are "equal" (within epsilon tolerance)
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
