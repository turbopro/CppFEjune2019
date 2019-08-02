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
	double CallGamma(double U) const;
	double PutGamma(double U) const;
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
	double Gamma(double U) const;							// use with default constructor
	double Gamma() const;									// use with constructor

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

// **********************************************
// The following constants are used to create a Vector of Map containers to store the
// four Batches of test values, and, also for creating map<string, double> 
// containers to be used as input arguments to the constructor

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


// **********************************************
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
void matrix_pricer(vector<map<string, double>>& price_matrix, vector<double>& prices, 
	const string test_param, const double& step_size,
	const string option_type = "C", const string underlying = "Stock");

// Pointer to const member function: used to pass member functions as arguments to
// other functions
// We use in the following vector_pricer() to pass either Price(), Gamma(), or 
// Delta() member functions
typedef double (EuropeanOption::* EuroMemFn)(double) const;

// vector_pricer()
// Has seven input arguments:
// test_params	-	a map<string, double> that contains the option test parameters
// prices		-	a vector<doubles> to store calculated Call or Put option prices
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// test_param	-	a string that holds the test parameter's character
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
//void vector_pricer(map<string, double>& test_params, vector<double>& prices, 
void vector_pricer(map<string, double>& test_params, vector<double>& prices,
	const double& param_end, const double& step_size, EuroMemFn m_fp,
	string test_param, string option_type = "C", string underlying = "Stock");

#endif