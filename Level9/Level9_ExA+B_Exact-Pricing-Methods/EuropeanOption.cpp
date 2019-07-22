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

//////////// Gaussian functions /////////////////////////////////

// In general, we would use similar functions in Boost::Math Toolkit

double EuropeanOption::n(double x) const
{ 

	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

double EuropeanOption::N(double x) const
{ // The approximation to the cumulative normal distribution


	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - N(-x);
	}

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

EuropeanOption::EuropeanOption(const EuropeanOption& o2)
{ // Copy constructor

	copy(o2);
}

EuropeanOption::EuropeanOption (const string& optionType)
{	// Create option type

	init();
	optType = optionType;

	if (optType == "c")
		optType = "C";

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

// setBatch() definition
// hard-coded values
void setBatch(Array<map<string, double> >& Batch)
{
	// Batch Test Values:
	// Batch 1: T = 0.25, K = 65,    sig = 0.30, r = 0.08, S = 60    (then C = 2.13337, P = 5.84628).
	// Batch 2: T = 1.0,  K = 100,   sig = 0.2,  r = 0.0,  S = 100   (then C = 7.96557, P = 7.96557).
	// Batch 3: T = 1.0,  K = 10,    sig = 0.50, r = 0.12, S = 5     (C = 0.204058, P = 4.07326).
	// Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).

	Batch[0].emplace("T", 0.25); Batch[0].emplace("K", 65.0); Batch[0].emplace("sig", 0.3);
	Batch[0].emplace("r", 0.08); Batch[0].emplace("S", 60.0); Batch[0].emplace("C", 2.13337);
	Batch[0].emplace("P", 5.84628);

	Batch[1].emplace("T", 1.0); Batch[1].emplace("K", 100);   Batch[1].emplace("sig", 0.2);
	Batch[1].emplace("r", 0.0); Batch[1].emplace("S", 100.0); Batch[1].emplace("C", 7.96557);
	Batch[1].emplace("P", 7.96557);

	Batch[2].emplace("T", 1.0);  Batch[2].emplace("K", 10);  Batch[2].emplace("sig", 0.5);
	Batch[2].emplace("r", 0.12); Batch[2].emplace("S", 5.0); Batch[2].emplace("C", 0.204058);
	Batch[2].emplace("P", 4.07326);

	Batch[3].emplace("T", 30.0); Batch[3].emplace("K", 100.0); Batch[3].emplace("sig", 0.3);
	Batch[3].emplace("r", 0.08); Batch[3].emplace("S", 100.0); Batch[3].emplace("C", 92.17570);
	Batch[3].emplace("P", 1.2475);
}
