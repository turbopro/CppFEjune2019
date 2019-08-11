/* Option.hpp
//
// EuropeanOption Base class
// a
//
// (C) Datasim Component Technology BV 2003-2011
*/

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp


#include <string>
#include <array>
#include <map>				// for map
#include <algorithm>

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions

using namespace std;

class EuropeanOption
{
private:
	// Gaussian functions: using Boost::Math library functions
	double n(double x) const;
	double N(double x) const;

protected:
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
	EuropeanOption();										// Default call option
	EuropeanOption(const map<string, double>& option_parameters,	// constructor
		const string& option_type, const string& security, const double& b_adjust = 0.0);
	EuropeanOption(const EuropeanOption& option2);			// Copy constructor
	EuropeanOption(const string& optionType);				// Create option type
	virtual ~EuropeanOption();								// destructor for base class

	EuropeanOption& operator = (const EuropeanOption& option2);	// assignment operator

	// Functions that calculate option price and sensitivities
	virtual double Price(double U) const;					// use with default constructed EuroOption
	virtual double Price() const;							// use with constructor
	virtual double Delta(double U) const;					// use with default constructed EuroOption
	virtual double Delta() const;							// use with constructor
	virtual double Gamma(double U) const;					// use with default constructed EuroOption
	virtual double Gamma() const;							// use with constructor
	virtual double DeltaDividedDiff(double h);				// divided differences to approximate option sensitivities
	virtual double GammaDividedDiff(double h);				// divided differences to approximate option sensitivities

	// Inline member functions to calculate d1 and d2
	virtual double D1(const double U) const
	{
		return (log(U / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	}
	virtual double D2(const double U) const { return (D1(U) - (sig * sqrt(T))); }

	// getter functions
	virtual string OptionType() const { return opt_type; }			// return type of option
	virtual string Underlying() const { return unam; }				// return type of underlying security
	virtual double ParityFactor()const { return (K * exp(-r * T)); }	// return put-call parity factor

	// Modifier functions
	virtual void toggle();		// Change option type (C/P, P/C)

	// calculate and return a tuple of call and put prices at put-call parity
	virtual boost::tuple<double, double> put_call_parity() const;
	// check if call and put prices at Stock price S make for a put-call parity
	virtual bool check_put_call_parity(const double& call_price, const double& put_price) const;

	// print option parameters
	virtual void Print() const;

	//get vector of prices
	//vector<double>& option_prices()const;
};



#endif
