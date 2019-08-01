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
	// 'Kernel' functions for option calculations
	double CallPrice(double U) const;
	double PutPrice(double U) const;
	double CallDelta(double U) const;
	double PutDelta(double U) const;
	//double CallTheta(double U) const;
	//double PutTheta(double U) const;
	//double CallRho(double U) const;
	//double PutRho(double U) const;
		
	// Gaussian functions
	double n(double x) const;
	double N(double x) const;

	// static data member for comparison of double variables
	static const double epsilon;

	// Member data are private

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
	EuropeanOption(const EuropeanOption& option2);			// Copy constructor
	EuropeanOption(const string& optionType);				// Create option type
	virtual ~EuropeanOption();								// destructor for base class

	EuropeanOption& operator = (const EuropeanOption& option2);	// assignment operator

	// Functions that calculate option price and sensitivities
	double Price(double U) const;							// use with default constructor
	double Price() const;									// use with constructor
	double Delta(double U) const;							// use with default constructor
	double Delta() const;									// use with constructor
	double Theta(double U) const;							// use with default constructor
	double Theta() const;									// use with constructor

	// getter functions
	string OptionType() const { return opt_type; }			// return type of option
	string Underlying() const { return unam; }				// return type of underlying security
	double ParityFactor()const								// return put-call parity factor
	{ return (K * exp(-r * T)); }

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

	// calculate and return a tuple of call and put prices at put-call parity
	boost::tuple<double, double> put_call_parity() const;
	// check if call and put prices at Stock price S make for a put-call parity
	bool check_put_call_parity(const double& call_price, const double& put_price) const;

	// print option parameters
	void Print() const;

};

// store Test Parameter names and values into a Map<String, Double> container
void set_batch(map<string, double>& batch, const vector<string>& option_param,
	const vector<double>& option_param_val);

// ============================================================================
// These constants are used to create a Vector of Map containers to store the
// four Batches of test values, and, also for creating map<string, double> 
// containers to be used as input arguments to the constructor
// ============================================================================
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


/*
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
*/

// Create a vector of doubles of increasing value
// vector<double> vec_range(const double& start, const double& end, const int& length);
void vec_range(vector<double>& vec, const double& start, const double& end);

// **********************************************
// matrix_pricer()
// Takes a vector of map<srtring, double>, a vector of doubles, a test parameter string, 
// a test parameter start value double, a test parameter step size double, an option type
// string, and an underlying security name string; no return, return is void
// Both vectors are reference objects whose values are updated during function execution
void matrix_pricer(vector<map<string, double>>& price_matrix, vector<double>& prices, 
	const string test_param, const double& param_start, const double& step_size,
	const string option_type = "C", const string underlying = "Stock");

void vector_pricer(map<string, double>& test_params, vector<double>& prices, 
	const double& param_start, const double& param_end, const double& step_size, 
	string test_param, string option_type = "C", string underlying = "Stock");

#endif