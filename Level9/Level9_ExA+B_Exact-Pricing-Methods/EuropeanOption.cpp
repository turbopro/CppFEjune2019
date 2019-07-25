// EurpeanOption.cpp
//
//	Author: Daniel Duffy
//
// (C) Datasim Component Technology BV 2003-2011
//


#include "EuropeanOption.hpp"
#include <cmath>
#include <iostream>
#include <map>
#include "Array.h"

//using namespace boost::math;


//////////// Gaussian functions /////////////////////////////////

// In general, we would use similar functions in Boost::Math Toolkit
// And assuming that the distribution for the underlying Stock Price 
// follows a normal distribution with mean = 0.0, std dev = 1.0, we
// would re-write n(x) and N(x) as follows:

double EuropeanOption::n(double x) const
{  
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

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

// constructor takes three arguments: 
// arg[0] = map with test parameter values
// arg[1] = option type
// arg[2] = underlying security type
EuropeanOption::EuropeanOption(map<string, double>& op, 
	string ot, char security, double adjustment)
{
	r = op["r"];
	sig = op["sig"]; 
	K = op["K"];
	T = op["T"];
	//b = r;			// Black and Scholes stock option model (1973)

	optType = ot;

	// set b, set unam based on type of underlying security 
	switch (security)
	{
		case 's':		// stock: b = r as per Black and Scholes stock option model (1973)
		case 'S': b = r; unam = "Stock"; break;		
		case 'i':		// stock index
		case 'I': b = r - adjustment; unam = "Stock Index"; break;
		case 'f':		// future
		case 'F': b = 0.0; unam = "Future"; break;
		case 'c':		// currency
		case 'C': b = r - adjustment; unam = "Currency"; break;
		// default to Stock settings
		default: b = r; unam = "Stock";
	}

	//unam = security;

	//std::cout << "\nr: " << r << ", sig: " << sig << ", K: "
		//<< K << ", T: " << T << ", b: " << b << endl;
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
		<< "\nK: " << K
		<< "\nT: " << T
		<< "\nsig: " << sig
		<< "\nr: " << r;
}

// set_batch() definition
void set_batch(map<string, double>& batch, const vector<string>& S, const vector<double>& V)
{
	for (int i = 0; i < V.size(); i++)
	{
		batch[S[i]] = V[i];
	}
}