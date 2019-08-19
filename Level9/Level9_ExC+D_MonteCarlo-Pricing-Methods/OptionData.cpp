/* OptionData.cpp

Implementation file for OptionDatacCEV class from header file OptionData.hpp

*/


#include "OptionData.hpp"


// default constructor
OptionData::OptionData() 
	: m_option (EuropeanOption()), H(0.0), D(0.05), betaCEV(1.0), scale(1.0) {}

// constructor
// takes an option as input
OptionData::OptionData(const EuropeanOption& op, const map<string, double>& CEVdata)
	: m_option(op), H(CEVdata.at("H")), D(CEVdata.at("D")), betaCEV(CEVdata.at("betaCEV")),
	scale(CEVdata.at("scale")) 
{}

// build option constructor
// option is built from input parameters
OptionData::OptionData(const map<string, double>& op, string ot, string underlying,
	map<string, double> cev_data, double b_adjust)
	: m_option(op, ot, underlying, b_adjust),
	H(cev_data.at("H")), D(cev_data.at("D")), betaCEV(cev_data.at("betaCEV")),
	scale(cev_data.at("scale"))
{}

// copy constructor
OptionData::OptionData(const OptionData& opd)
	: m_option(opd.m_option), H(opd.H), D(opd.D), betaCEV(opd.betaCEV), scale(opd.scale)
{}

// assignment operator
OptionData& OptionData::operator=(const OptionData& opd)
{
	// prevent self assignment
	if (this == &opd) return *this;

	// assign member data
	m_option = opd.m_option;
	H = opd.H;
	D = opd.D;
	betaCEV = opd.betaCEV;
	scale = opd.scale;
}


// run_sim function
void run_sim(const OptionData& option_data, const double& s_initial, double& sim_price,
	int& count, const int N, const int NSim)
{
	// Create the basic SDE (Context class)
	//Range<double> range(0.0, option_data.T());
	double v_prev = s_initial;
	double v_curr = 0.0;

	//std::vector<double> t_mesh = range.mesh(n);
	//std::vector<double> t_mesh = range.mesh(N);

	double step = option_data.T() / N;
	vector<double> t_mesh(double(N)+1);
	std::generate(t_mesh.begin(), t_mesh.end(),
		[start = 0.0, step]() mutable { return start += step; });

	//double k = option_data.T() / double(N);
	double k = option_data.T() / N;
	double sqrk = sqrt(k);

	// NormalGenerator is a base class
	// unique_ptr will manage the heap memory allocated for the random number
	std::unique_ptr<NormalGenerator> uptr_normal(new BoostNormal());

	// Normal random number
	double dW = 0.0;

	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration

		
		if ((i / 10000) * 10000 == i)
		{// Give status after each 1000th iteration

			cout << i << endl;
		}
		

		v_prev = s_initial;
		for (auto it = t_mesh.begin()+1; it != t_mesh.end(); ++it)
		{
			// Create a random number
			dW = uptr_normal->getNormal();

			// The FDM (in this case explicit Euler)
			v_curr = v_prev + (k * option_data.drift(*(it-1), v_prev))
				+ (sqrk * option_data.diffusion(*(it-1), v_prev) * dW);

			v_prev = v_curr;

			// Spurious values
			if (v_curr <= 0.0) count++;
		}
		
		sim_price += option_data.PayOff(v_curr) / NSim;
	}			// std::unique_ptr uptr_normal is destructed here

	sim_price *= exp(-option_data.r() * option_data.T());
}

