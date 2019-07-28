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
	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	double CallTheta(double U) const;
	double PutTheta(double U) const;
	double CallRho(double U) const;
	double PutRho(double U) const;
	
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;

//public:

	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.

	// create Tuple to hold Option Parameters
	// Tuple layout: T, K, sig, r, S, optType, unam, b_adjust (adjustment based on underlying security)
	//typedef boost::tuple<double, double, double, double, double, string, string, double> OptParams;

	//OptParams m_option;
	double T;		// Strike price
	double K;		// Expiry date
	double sig;		// Volatility
	double r;		// Interest rate
	double S;		// Asset Price
	double b;		// Cost of carry

	string opt_type;// Option type: "C" = call, "P" = put
	string unam;	// Name of underlying asset

public:	// Public functions
	EuropeanOption();										// Default call option
	EuropeanOption(const map<string, double>& op,			// constructor		--	added july 24
		const string& ot, const string& security, const double& b_adjust = 0.0);
	//EuropeanOption(map<string, double>& op);				// constructor		--	added july 24
	//EuropeanOption(const OptParams& op);					// constructor		-- added July 25
	EuropeanOption(const EuropeanOption& option2);			// Copy constructor
	EuropeanOption(const string& optionType);				// Create option type
	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price(double U) const;							// use with default constructor
	double Price() const;									// use with constructor
	double Delta(double U) const;							// use with default constructor
	double Delta() const;									// use with constructor
	double Theta(double U) const;							// use with default constructor
	double Theta() const;									// use with constructor

	// getter functions
	string OptionType() const { return opt_type; }			// get type of option
	string Underlying() const { return unam; }				// get type of underlying security 

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	// Put_call_parity(): determine if put and call prices meet the put-call parity requirments
	// Friend function to allow access to data members
	friend boost::tuple<double, double> put_call_parity(const EuropeanOption& EuroOption);

	// print option parameters
	void Print() const;

};

// store Test Values into a Map container
void set_batch(map<string, double>& batch, const vector<string>& S, const vector<double>& V);


// ==================================================================
// These constants are an Array of Map containers to store the four 
// Batches of test values, and, tuples of input test values to be
// used as input arguments to the constructor
// ==================================================================
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




// create Tuple typedef: includes Option Parameters of types doubles and strings
// tuples will be used as input argument to constructor
// Tuple layout: T, K, sig, r, S, "Option Type", "Underlying Security", b_adjust 
typedef boost::tuple<double, double, double, double, double, string, string, double> OptParams;
const vector<OptParams> opt_params
{
	(OptParams(0.25, 65, 0.30, 0.08, 60, "C", "Stock", 0.0)),
	(OptParams(1.0, 100, 0.2, 0.0, 100, "C", "Stock", 0.0)),
	(OptParams(1.0, 10, 0.5, 0.12, 5, "C", "Stock", 0.0)),
	(OptParams(30.0, 100.0, 0.3, 0.08, 100.0, "C", "Stock", 0.0))
};


#endif