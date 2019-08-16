// OptionData.hpp
//
// Encapsulate option data.
//
// (C) Datasim Education BV 2008-2011

#ifndef OptionData_HPP
#define OptionData_HPP

#include <algorithm>				// for max()
#include <memory>					// for shared pointer
#include "EuropeanOption.h"
#include "Range.cpp"
#include "NormalGenerator.hpp"

using namespace std;

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
		
			return max (K - S, 0.0);
		}
	}
};



class OptionDataCEV
{
	typedef std::unique_ptr<EuropeanOption> sp_EuroOption;
private:
	EuropeanOption m_option;

	// Extra data 
	double H;		// down and out barrier
	double D;		// dividend
	double betaCEV;	// elasticity factor (CEV model)
	double scale;	// scale factor in CEV model

public:
	OptionDataCEV();										// default constructor
	OptionDataCEV(const EuropeanOption& op, const map<string, double>& CEV_data);	// constructor
	OptionDataCEV(const map<string, double>& op, string ot,	// build option constructor
		string underlying, map<string, double> cev_data, double b_adjust = 0.0);
	OptionDataCEV(const OptionDataCEV& opd);				// copy constructor
	~OptionDataCEV() {}										// destructor
	OptionDataCEV& operator=(const OptionDataCEV& opd);		// assignment operator

	// Getter functions
	double T() const { return m_option.GetT(); }
	double r() const { return m_option.GetR(); }

	// Setter functions

	// PayOff
	double PayOff(double S) const 
	{
		return (m_option.OptionType() == "C") ? 
			max(S - m_option.GetK(), 0.0) : 
			max(m_option.GetK() - S, 0.0);
	}


	// SDE functions (all inline functions)
	// "double t" in the original function is not needed for the function
	// "double X" is essentially the asset/underlying price
	// All option parameters retrieved from the option as getter functions
	
	// Drift
	double drift(double t, double X) const
	{
		// if opt_type == "Index", b = r - D
		return (m_option.Underlying() == "Index") ? 
			m_option.GetB() * X:
			m_option.GetR() * X;
	}

	// Diffusion()
	double diffusion(double t, double X) const
	{
		return m_option.GetSig() * pow(X, betaCEV);
	}

	// Diffusion derivative
	double diffusionDerivative(double t, double X)
	{
		return 0.5 * (m_option.GetSig()) * betaCEV * (pow(X, (2.0 * betaCEV - 1.0)));
	}
};


// run simulation loop
// Takes an option_data object, an initial asset/underlying price, a double for the 
// simulated price calculated, and an integer for the count of surious values during
// the simulation run
void run_sim(const OptionDataCEV& option_data, const double& S_initial,
	double& sim_price, int& count);


#endif

