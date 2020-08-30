/* EuropeanOption.hpp

EuropeanOption Base class

(C) Datasim Component Technology BV 2003-2011

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

	// Member data is set as "protected" to allow easier access by derived classes
	// for derived class member function instantiations: see calculations of Y1()
	// and Y2() in derived class AmericanOption

protected:
	// Member data 
	double T;		// Strike price
	double K;		// Expiry date
	double sig;		// Volatility
	double r;		// Interest rate
	double S;		// Asset Price
	double b;		// Cost of carry

	string opt_type;// Option type: "C" = call, "P" = put
	string unam;	// Name of underlying asset/security

	// Static data member for comparison of double variables
	// Floating point precision factor
	static const double epsilon;

public:	// Public functions
	EuropeanOption();										// Default constructor
	// constructor takes four arguments: 
	// op		-	map<string, vector> with test parameter values
	//				We use a map to map option parameter name to parameter name value for
	//				ease of reference 
	// ot		-	option type
	// security	-	Name of underlying security type
	// b_adjust	-	Value to be used to adjust parameter b:
	//				b's value is calculated in the constructor based on type of underlying
	//				asset/security
	//				For a Stock, b = r; for an index, b = r - q(dividend); for a future, b = 0.0;
	//				for a currency, b = r - R(foreign exchange interest rate)
	EuropeanOption(const map<string, double>& option_parameters,	// constructor
		const string& option_type, const string& security, const double& b_adjust = 0.0);
	EuropeanOption(const EuropeanOption& option2);			// Copy constructor
	virtual ~EuropeanOption();								// destructor for base class

	EuropeanOption& operator = (const EuropeanOption& option2);	// assignment operator

	// Functions that calculate option price and sensitivities
	// All functions here set to virtual to allow instantiations by derived classes if needed
	virtual double Price(double U) const;			// use with default constructed EuroOption
	virtual double Price() const;					// use with constructor
	virtual double Delta(double U) const;			// use with default constructed EuroOption
	virtual double Delta() const;					// use with constructor
	virtual double Gamma(double U) const;			// use with default constructed EuroOption
	virtual double Gamma() const;					// use with constructor
	virtual double DeltaDividedDiff(double h);		// divided differences to approximate option sensitivities
	virtual double GammaDividedDiff(double h);		// divided differences to approximate option sensitivities

	// Inline member functions to calculate d1 and d2
	double D1(const double U) const
	{
		return (log(U / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	}
	double D2(const double U) const { return (D1(U) - (sig * sqrt(T))); }

	// getter functions
	string OptionType() const { return opt_type; }			// return type of option
	string Underlying() const { return unam; }				// return type of underlying security
	double ParityFactor()const { return (K * exp(-r * T)); }	// return put-call parity factor
	double GetS() const { return S; }						// return the price of the underlying Asset/Security

	// setter functions
	void SetS(double U) { S = U; }
	void SetK(double U) { K = U; }
	void SetT(double U) { T = U; }
	void SetR(double U) { r = U; }
	void SetSig(double U) { sig = U; }
	void SetB(double U) { b = U; }

	// Modifier functions
	void SetOptionType(const string& ot);		// Set the option type
	void toggle();								// Change option type: from C to P, or from P to C)

	// ---------- Put-Call parity ------------
	// calculate and return a tuple of call and put prices at put-call parity
	boost::tuple<double, double> put_call_parity() const;
	// check if call and put prices at Stock price S make for a put-call parity
	bool check_put_call_parity(const double& call_price, const double& put_price) const;

	// print option parameters
	virtual void Print() const;
};

#endif
