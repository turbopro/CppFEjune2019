// EuropeanOption.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only.
//
// (C) Datasim Component Technology BV 2003-2011
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp


#include <string>
#include <array>
#include <map>				// for map
#include "Array.h"

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions

using namespace std;
using namespace Turbopro::Containers;

class EuropeanOption
{
private:		

	void init();	// Initialise all default values
	void copy(const EuropeanOption& o2);

	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	

	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


//public:

	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.

	// create Tuple to hold Option Parameters
	// Tuple layout: T, K, sig, r, S, optType, unam, b_adjust (adjustment based on underlying security)
	typedef boost::tuple<double, double, double, double, double, string, string, double> OptParams;

	//OptParams m_option;
	double T;		// Strike price
	double K;		// Expiry date
	double sig;		// Volatility
	double r;		// Interest rate
	double S;		// Asset Price
	double b;		// Cost of carry

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset


public:	// Public functions
	EuropeanOption();										// Default call option
	//EuropeanOption(map<string, double>& op, string ot,	// constructor		--	added july 24
		//char security, double costofcarry_adjust = 0.0);
	EuropeanOption(OptParams& op);							// constructor		-- added July 25
	EuropeanOption(const EuropeanOption& option2);			// Copy constructor
	EuropeanOption(const string& optionType);				// Create option type
	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price(double U) const;							// for use with default constructor
	double Price() const;
	double Delta(double U) const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	// print option parameters
	void Print() const;

};

// store Test Values into a Map container
void set_batch(map<string, double>& batch, const vector<string>& S, const vector<double>& V);


#endif