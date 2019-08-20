// OptionData.hpp
//
// Encapsulate option data.
//
// (C) Datasim Education BV 2008-2011

#ifndef OptionData_HPP
#define OptionData_HPP

#include <algorithm> // for max()
using namespace std;
//using namespace SDEDefinition;

// Encapsulate all data in one place
struct OptionData
{ // Option data + behaviour

	double K;
	double T;
	double r;
	double sig;

	// Extra data 
	double H;		// down and out barrier
	double D;		// dividend
	double betaCEV;	// elasticity factor (CEV model)
	double scale;	// scale factor in CEV model

	int type;		// 1 == call, -1 == put

	double myPayOffFunction(double S)
	{ // Payoff function

		if (type == 1)
		{ // Call

			return max(S - K, 0.0);
		}
		else
		{ // Put

			return max(K - S, 0.0);
		}
	}
};




//////////////////////////////////////////////
////


// Standard Deviation, Standard Error definitions
// SD
double SD(double price);

// SE
inline double SE(double price, int NSim) { return SD(price) / sqrt(NSim); }







#endif