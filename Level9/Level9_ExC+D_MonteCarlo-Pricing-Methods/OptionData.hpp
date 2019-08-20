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
#include <boost/range/irange.hpp>
#include <iostream>

using namespace std;

class OptionData
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
	OptionData();											// default constructor
	OptionData(const EuropeanOption& op, const map<string, double>& CEV_data);	// constructor
	OptionData(const map<string, double>& op, string ot,	// build option constructor
		string underlying, map<string, double> cev_data, double b_adjust = 0.0);
	OptionData(const OptionData& opd);						// copy constructor
	~OptionData() {}										// destructor
	OptionData& operator=(const OptionData& opd);			// assignment operator

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

	// Diffusion
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


////////////////////////////////////////////////////////
// Monte Carlo Simulation

// run_simulation
// Takes an option_data object, an initial asset/underlying price, a double for the 
// simulated price calculated, and an integer for the count of surious values during
// the simulation run
void run_sim(const OptionData& option_data, const double& s_initial, double& sim_price,
	int& count, const int N, const int NSim);

//double sim_option_price(const OptionData& option_data, const double& s_initial, const int N, const int NSim);

// option_price_t
// return the option price for a calculate the option 
double option_price_t(const OptionData opd, double S_initial, int N);


////////////////
// run_sim1
// simulation using the option_price_t function
void run_sim1(const OptionData& option_data, const double& s_initial, double& sim_price,
	int& count, const int& N, const int& NSim);


///////////////////////////////////////////////////////
// Standard Deviation & Standard Error

// SD
//double SD(const OptionData& option_data, const double& s_initial, const int N, 
	//const int NSim);

// SE
//double SE(const int NSim);


//////////////////////////////////////////
// Utility Functions

// print function for vector
template <class T> void print(const std::vector<T>& vec)
{  // A generic print function for vectors

	std::cout << std::endl << "Size of vector is " << vec.size() << "\n[";
	for (auto it : vec) std::cout << it << ",";
	std::cout << "]\n";
}




// create range with Boost.Range irange
template<class Integer>
decltype(auto) iota_n(Integer last)
{
	return boost::irange(0, last);
}

template<class Integer, class StepSize>
decltype(auto) iota_n(Integer last, StepSize step_size)
{
	return boost::irange(0, last, step_size);
}



#endif

