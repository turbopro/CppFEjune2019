/* AmericanOption.hpp

AmericanOption class header file

*/

#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include <string>
#include <array>
#include <map>				// for map
#include <algorithm>
#include "EuropeanOption.h"

using namespace std;

// The American option class is derived from the base European option class
// An American option may be considered a special type of an European option
class AmericanOption	:	public EuropeanOption
{
private:
	// all option parameters are part of the base EuropeanOption class

public:	// Public functions
	AmericanOption();										// Default constructor
	AmericanOption(const map<string, double>& option_parameters,	// constructor
		const string& option_type, const string& security, const double& b_adjust = 0.0);
	AmericanOption(const AmericanOption& option2);			// Copy constructor
	//AmericanOption(const string& optionType);				// Create option type
	virtual ~AmericanOption();								// destructor for base class

	AmericanOption& operator = (const AmericanOption& option2);	// assignment operator

	// Functions that calculate option price and sensitivities
	double Price(double U) const;					// use with default constructed AmericanOption
	double Price() const;							// use with constructor
	
	// Inline member functions to calculate Y1 and Y2
	double Y1() const
	{		
		return (0.5 - (b / (sig * sig)) + sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 
			0.5) + ((2 * r) / (sig * sig))));
	}

	double Y2() const
	{		
		return (0.5 - (b / (sig * sig)) - sqrt((b / (sig * sig) - 0.5) * (b / (sig * sig) - 
			0.5) + ((2 * r) / (sig * sig))));
	}
};


#endif
