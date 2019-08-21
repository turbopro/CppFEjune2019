/* AmericanOption.cpp

Implementation file for the AmericanOption.h header file

*/

#include "AmericanOption.h"
#include "EuropeanOptionException.h"
#include <cmath>

// Default constructor
// Calls the EuropeanOption() default constructor
AmericanOption::AmericanOption() : EuropeanOption() {}		

// Constructor
// Calls the EuropeanOption() constructor
AmericanOption::AmericanOption(const map<string, double>& option_parameters,	
	const string& option_type, const string& security, const double& b_adjust) 
	: EuropeanOption( option_parameters, option_type, security, b_adjust ) {}

// Copy constructor
// Calls the EuropeanOption() copy constructor
AmericanOption::AmericanOption(const AmericanOption& option2)
	: EuropeanOption(option2) {}


//AmericanOption::AmericanOption(const string& optionType) {}				// Create option type

// Destructor
AmericanOption::~AmericanOption() {}

// Assignment operator
// Checks for self-assignment; calls the EuropeanOption() assignment operator
AmericanOption& AmericanOption::operator = (const AmericanOption& option2) 
{
	if(this == &option2) return *this;

	EuropeanOption::operator=(option2);

	return *this;
}

// Functions that calculate option price and sensitivities
// Use with default constructor: asset price is accepted here as a single argument double
double AmericanOption::Price(double U) const
{
	// Use member functions D1 and D2 only when needed; no need for temporary variables
	// Return either call price or put price
	// Throw exception if either of Y1 or Y2 are set to values that may generate divide by
	// zero or other similar errors
	
	if (Y1() == 0 || Y1() == 1)
		throw InvalidValueException(to_string(Y1()));
	if (Y2() == 0 || Y2() == 1)
		throw InvalidValueException(to_string(Y2()));

	return (opt_type == "C" || opt_type == "c") ?
		((K / (Y1() - 1)) * pow((((Y1() - 1) / Y1()) * (U / K)), Y1())) :	// call price
		((K / (1 - Y2())) * pow((((Y2() - 1) / Y2()) * (U / K)), Y2()));	// put price
}

// Use with constructor: asset price is provided within the input map container
// Call single argument Price member function
double AmericanOption::Price() const
{
	return Price(S);
}






