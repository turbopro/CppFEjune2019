// OptionData.cpp
// Implementation file for OptionData.hpp header file

#include "OptionData.hpp"
#include "Range.hpp"
#include "NormalGenerator.hpp"




double SD(double price)
{
	return 0;
}

/*

// option_price
double option_price(OptionData& opd, const int N, const int NSim,
	const double s_initial);

// option_price_t
//double option_price_t(OptionData& opd, const double s_initial,
	//const int N, const int NSim);
double option_price_1(OptionData opd, vector<double> x, const double s_initial,
	int coun, NormalGenerator* p_normal, const double sk);

// option_price
double option_price(OptionData& opd, const int N, const int NSim,
	const double s_initial)
{

	//long N = 100;
	//std::cout << "Number of subintervals in time: ";
	//std::cin >> N;

	// Create the basic SDE (Context class)
	Range<double> range(0.0, opd.T);
	//double VOld = S_0;
	double VOld = s_initial;
	double VNew = 0.0;

	std::vector<double> x = range.mesh(N);


	// V2 mediator stuff
	//long NSim = 50000;
	//std::cout << "Number of simulations: ";
	//std::cin >> NSim;

	double k = opd.T / double(N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price
	//double output_price = 0.0; // , output_price_sq = 0.0;

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &opd;


	std::vector<double> res;
	int count = 0; // Number of times S hits origin

	// A.
	for (long i = 1; i <= NSim; ++i)
	{ // Calculate a path at each iteration

		if ((i / 10000) * 10000 == i)
		{// Give status after each 1000th iteration

			std::cout << i << std::endl;
		}

		//VOld = S_0;
		VOld = s_initial;
		for (unsigned long index = 1; index < x.size(); ++index)
		{

			// Create a random number
			dW = myNormal->getNormal();

			// The FDM (in this case explicit Euler)
			VNew = VOld + (k * drift(x[index - 1], VOld))
				+ (sqrk * diffusion(x[index - 1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) count++;
		}

		double tmp = opd.myPayOffFunction(VNew);
		price += (tmp) / double(NSim);
		//output_price = VNew;
		//output_price_sq = VNew * VNew;
	}

	delete myNormal;

	return price;
}

// option_price_t
double option_price_t(OptionData& opd, const double s_initial,
	const int N, const int NSim)
{

	// Create the basic SDE (Context class)
	Range<double> range(0.0, opd.T);
	//double VOld = S_0;
	double VOld = s_initial;
	double VNew = 0.0;

	std::vector<double> x = range.mesh(N);

	double k = opd.T / double(N);
	double sqrk = sqrt(k);

	// Normal random number
	double dW;
	double price = 0.0;	// Option price
	//double output_price = 0.0; // , output_price_sq = 0.0;

	// NormalGenerator is a base class
	NormalGenerator* myNormal = new BoostNormal();

	using namespace SDEDefinition;
	SDEDefinition::data = &opd;


	std::vector<double> res;
	int count = 0; // Number of times S hits origin

	// A.
	//for (long i = 1; i <= NSim; ++i)
	//{ // Calculate a path at each iteration

		//if ((i / 10000) * 10000 == i)
		//{// Give status after each 1000th iteration

		//	std::cout << i << std::endl;
		//}

		//VOld = S_0;
		VOld = s_initial;
		for (unsigned long index = 1; index < x.size(); ++index)
		{

			// Create a random number
			dW = myNormal->getNormal();

			// The FDM (in this case explicit Euler)
			VNew = VOld + (k * drift(x[index - 1], VOld))
				+ (sqrk * diffusion(x[index - 1], VOld) * dW);

			VOld = VNew;

			// Spurious values
			if (VNew <= 0.0) count++;
		}

		double tmp = opd.myPayOffFunction(VNew);
		price += (tmp) / double(NSim);
		//output_price = VNew;
		//output_price_sq = VNew * VNew;
	//}

	delete myNormal;

	return price;
}


// option_price_1
double option_price_1(OptionData opd, vector<double> x, const double s_initial,
	int count, NormalGenerator* p_normal, const double k)
{
	using namespace SDEDefinition;
	double dW = p_normal->getNormal();
	double VOld = s_initial, VNew = 0.0;
	double sqrk = sqrt(k);

	for (unsigned long index = 1; index < x.size(); ++index)
	{

		// Create a random number

		// The FDM (in this case explicit Euler)
		VNew = VOld + (k * drift(x[index - 1], VOld))
			+ (sqrk * diffusion(x[index - 1], VOld) * dW);

		VOld = VNew;

		// Spurious values
		if (VNew <= 0.0) count++;

		
		VNew = VOld + (k * drift(x[index - 1], VOld))
			+ (sqrk * diffusion(x[index - 1], VOld) * dW);

		VOld = VNew;

		// Spurious values
		if (VNew <= 0.0) count++;
		

		//}
		//delete p_normal;
		//return VNew;
	//}
*/