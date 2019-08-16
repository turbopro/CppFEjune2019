/* OptionData.cpp

Implementation file for OptionDatacCEV class from header file OptionData.hpp

*/

#include "OptionData.hpp"


// default constructor
OptionDataCEV::OptionDataCEV() 
	: m_option (EuropeanOption()), H(0.0), D(0.05), betaCEV(1.0), scale(1.0) {}

// constructor
// takes an option as input
OptionDataCEV::OptionDataCEV(const EuropeanOption& op, const map<string, double>& CEVdata)
	: m_option(op), H(CEVdata.at("H")), D(CEVdata.at("D")), betaCEV(CEVdata.at("betaCEV")),
	scale(CEVdata.at("scale")) 
{}

// build option constructor
// option is built from input parameters
OptionDataCEV::OptionDataCEV(const map<string, double>& op, string ot, string underlying,
	map<string, double> cev_data, double b_adjust)
	: m_option(op, ot, underlying, b_adjust),
	H(cev_data.at("H")), D(cev_data.at("D")), betaCEV(cev_data.at("betaCEV")),
	scale(cev_data.at("scale"))
{}



// copy constructor
OptionDataCEV::OptionDataCEV(const OptionDataCEV& opd)
	: m_option(opd.m_option), H(opd.H), D(opd.D), betaCEV(opd.betaCEV), scale(opd.scale)
{}

// assignment operator
OptionDataCEV& OptionDataCEV::operator=(const OptionDataCEV& opd)
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



// A.
void run_sim(const OptionDataCEV& option_data, const double& S_initial,
	double& sim_price, int& count)
{
	long N;
	cout << "Number of subintervals in time: ";
	cin >> N;

	// Create the basic SDE (Context class)
	Range<double> range(0.0, option_data.T());
	double VOld = S_initial;
	double VNew = 0.0;

	std::vector<double> t_mesh = range.mesh(N);

	// V2 mediator stuff
	long NSim = 50000;
	cout << "Number of simulations: ";
	cin >> NSim;

	double k = option_data.T() / double(N);
	double sqrk = sqrt(k);

	// NormalGenerator is a base class
	// unique_ptr will manage the heap memory allocated for the random number
	std::unique_ptr<NormalGenerator> uptr_normal(new BoostNormal());

	// Normal random number
	double dW = 0.0;
	double price = 0.0;	// Option price

	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration

		if ((i / 10000) * 10000 == i)
		{// Give status after each 1000th iteration

			cout << i << endl;
		}

		VOld = S_initial;
		for (unsigned long index = 1; index < t_mesh.size(); ++index)
		{
			// Create a random number
			dW = uptr_normal->getNormal();

			// The FDM (in this case explicit Euler)
			VNew = VOld + (k * option_data.drift(t_mesh[index - 1], VOld))
				+ (sqrk * option_data.diffusion(t_mesh[index - 1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) count++;
		}

		double tmp = option_data.PayOff(VNew);
		
		sim_price += (tmp) / double(NSim);
	}
}



// print function for vector
template <class T> void print(const std::vector<T>& myList)
{  // A generic print function for vectors

	std::cout << std::endl << "Size of vector is " << myList.size() << "\n[";
	for (auto it : myList) std::cout << it << ",";
	std::cout << "]\n";
}