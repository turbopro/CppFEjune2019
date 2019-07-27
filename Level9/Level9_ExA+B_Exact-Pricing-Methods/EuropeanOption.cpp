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
#include "Array.h"

//using namespace boost::math;


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
	cout << "\we're here: " << __FUNCTION__ << endl;
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
	cout << "\we're here: " << __FUNCTION__ << endl;
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

void EuropeanOption::init()
{	// Initialise all default values

	// Default values
	r = 0.05;
	sig= 0.2;

	K = 110.0;
	T = 0.5;

	b = r;			// Black and Scholes stock option model (1973)
	
	optType = "C";		// European Call Option (this is the default type)
}

void EuropeanOption::copy( const EuropeanOption& o2)
{

	r	= o2.r;
	sig = o2.sig;	
	K	= o2.K;
	T	= o2.T;
	b	= o2.b;
	
	optType = o2.optType;
	
}

EuropeanOption::EuropeanOption() 
{ // Default call option

	init();
}


// constructor takes four arguments: 
// arg[0] = map with test parameter values
// arg[1] = option type
// arg[2] = underlying security type
// arg[3] = value to be used to adjust b: dividend or interest rate
EuropeanOption::EuropeanOption(const map<string, double>& op, const string& ot,
	const string& security, const double& b_adjust)
	: T(op.at("T")), K(op.at("K")), sig(op.at("sig")), r(op.at("r")), S(op.at("S")),
	optType(ot), unam(security), b(b_adjust)
{
	if (unam == "Stock") b = r;
	else if (unam == "Future") b = 0;
	else if (unam == "Currency" || unam == "Index") b = r - b_adjust;
	else b = r;		// default to Stock cost of carry: Black and Scholes stock option model (1973) 
}

EuropeanOption::EuropeanOption(const EuropeanOption& o2)
{ // Copy constructor

	copy(o2);
}

EuropeanOption::EuropeanOption (const string& optionType)
{	// Create option type

	if (optionType == "c" || optionType == "C")
		optType = "C";
	else if (optionType == "p" || optionType == "P")
		optType = "P";
	else optType = "C";

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

	copy (option2);

	return *this;
}

// Functions that calculate option price and sensitivities
// use with constructor: asset price is provided within the input tuple
double EuropeanOption::Price() const
{
	if (optType == "C")
	{	
		cout << "calling call";
		return CallPrice(S);
	}
	else
	{
		cout << "calling put";
		return PutPrice(S);
	}
}

// use with default constructor: asset price is provided as a single argument double
double EuropeanOption::Price(double U) const
{
	if (optType == "C")
	{
		cout << "calling call\n";
		return CallPrice(U);
	}
	else
	{
		cout << "calling put\n";
		return PutPrice(U);
	}
}

double EuropeanOption::Delta(double U) const 
{
	if (optType == "C")
		return CallDelta(U);
	else
		return PutDelta(U);

}

double EuropeanOption::Delta() const
{
	if (optType == "C")
		return CallDelta(S);
	else
		return PutDelta(S);

}

double EuropeanOption::Theta(double U) const		// use with default constructor
{
	if (optType == "C")
		return CallTheta(U);
	else
		return PutTheta(U);
}

double EuropeanOption::Theta() const
{
	//cout << "\we're here: " << __FUNCTION__ << endl;
	if (optType == "C")
		return CallTheta(S);
	else
		return PutTheta(S);
}


// Modifier functions
void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)

	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}


// print option parameters
void EuropeanOption::Print() const
{
	std::cout << "Option Parameters:\n"
		<< "\nOption Type:\t" << optType
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