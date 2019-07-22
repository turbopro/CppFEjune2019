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
#include <map>				// for map
#include "Array.h"
using namespace std;

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


public:

	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.

	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry

	string optType;	// Option name (call, put)
	string unam;	// Name of underlying asset


public:	// Public functions
	EuropeanOption();							// Default call option
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	EuropeanOption (const string& optionType);	// Create option type
	virtual ~EuropeanOption();	

	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions that calculate option price and sensitivities
	double Price(double U) const;
	double Delta(double U) const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

};

// set Batch_n test values
using namespace Turbopro::Containers;		// namespace for Array template class
void setBatch(Array<map<string, double> >& Batch);

// Batch Test Values:
// Batch 1: T = 0.25, K = 65,    sig = 0.30, r = 0.08, S = 60    (then C = 2.13337, P = 5.84628).
// Batch 2: T = 1.0,  K = 100,   sig = 0.2,  r = 0.0,  S = 100   (then C = 7.96557, P = 7.96557).
// Batch 3: T = 1.0,  K = 10,    sig = 0.50, r = 0.12, S = 5     (C = 0.204058, P = 4.07326).
// Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).



//mapstrdbl_t.emplace("T", 1.0);



typedef std::pair<string, double> strdbl_t;
const strdbl_t Batch1[] =
{
	strdbl_t("T", 0.25), strdbl_t("K", 65.0), strdbl_t("sig", 0.3), strdbl_t("r", 0.08),
	strdbl_t("S", 60.0), strdbl_t("C", 2.13337), strdbl_t("P", 5.84628)
};

const strdbl_t Batch2[] =
{
	strdbl_t("T", 1.0), strdbl_t("K", 100), strdbl_t("sig", 0.2), strdbl_t("r", 0.0),
	strdbl_t("S", 100), strdbl_t("C", 7.96557), strdbl_t("P", 7.96557)
};

const strdbl_t Batch3[] =
{
	strdbl_t("T", 1.0), strdbl_t("K", 10), strdbl_t("sig", 0.5), strdbl_t("r", 0.12),
	strdbl_t("S", 5.0), strdbl_t("C", 0.204058), strdbl_t("P", 4.07326)
};

const strdbl_t Batch4[] =
{
	strdbl_t("T", 30.0), strdbl_t("K", 100.0), strdbl_t("sig", 0.3), strdbl_t("r", 0.08),
	strdbl_t("S", 100.0), strdbl_t("C", 92.17570), strdbl_t("P", 1.2475)
};

/*
    

	

*/



#endif