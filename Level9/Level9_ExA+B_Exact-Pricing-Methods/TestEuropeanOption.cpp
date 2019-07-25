// TestEuropeanOption.cpp
//
// Test program for the exact solutions of European options. 
// Check answers with Haug 2007 book on option pricing.
//
// (C) Datasim Component Technology BV 2003-20011
//

#include "EuropeanOption.hpp"
#include <iostream>
#include <sstream>
#include <tuple>
//#include <string>

// STL
#include <vector>			// for vector, copy
#include <list>				// for list
#include <map>				// for map
#include <iterator>			// for iter
#include <algorithm>		// for count_if
#include <numeric>			// std::accumulate
#include "Array.h"			// Array template class
#include "ArrayException.h"	// Array exception class
//#include "STLHelperFunctions.h"	// STL helper functions
#include <boost/shared_ptr.hpp>	// Boost C Library Shared Pointer header file


/* Cost of carry factor b must be included in formulae depending on the
   derivative type. These are used in the generalised Black-Scholes formula. 
   If r is the risk-free interest and q is the continuous dividend yield then 
   the cost-of-carry b per derivative type is:

	a) Black-Scholes (1973) stock option model: b = r
	b) b = r - q Merton (1973) stock option model with continuous dividend yield
	c) b = 0 Black (1976) futures option model
	d) b = r - rf Garman and Kohlhagen (1983) currency option model, where rf is the 
	   'foreign' interest rate

	Test Values for option pricing follows:
	Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)
*/


int main()
{ 
	using namespace Turbopro::Containers;		// namespace for Array template class

	// All options are European
	
	/*
	// create map containers for Batch Test Values
	// store Batch Test Values in an Array of Map containers
	const int map_size = 4;
	// create vector of test value strings: ["T", "K", "sig", "r", "S", "C", "P"]
	vector<string> test_str0{ "T", "K", "sig", "r", "S", "C", "P" };

	// create vector of test value doubles
	vector<double> test_val[]
	{
		{ 0.25, 65, 0.30, 0.08, 60, 2.13337, 5.84628 },
		{ 1.0, 100, 0.2, 0.0, 100, 7.96557, 7.96557 },
		{ 1.0, 10, 0.5, 0.12, 5, 0.204058, 4.07326 },
		{ 30.0, 100.0, 0.3, 0.08, 100.0, 92.1757, 1.2475 }
	};

	// create Array of Map containers: function set_batch() stores Test Values into Map containers
	Array<map<string, double>> batches(map_size);
	for (int i = 0; i < map_size; i++)
		set_batch(batches[i], test_str0, test_val[i]);

	for (int i = 0; i < batches.Size(); i++)
	{
		cout << "\nBATCH " << i+1 << ":  Test Run\n";
		cout << "\nRun a 'Call' option using Batch " << i+1 << " parameters:\n";
		EuropeanOption callOption(batches[i], "C", 'S');
		//cout << "S: "; double S; cin >> S;
		cout << "Option on a stock:\t" << callOption.Price(batches[i]["S"])
			<< "\nBatch " << i+1 << " 'Call' value:\t" << batches[i]["C"] 
			<< endl << endl;

		cout << "Run a 'Put' option using Batch " << i+1 << " parameters:\n";
		EuropeanOption putOption(batches[i], "P", 'S');
		cout << "Option on a stock:\t" << putOption.Price(batches[i]["S"])
			<< "\nBatch " << i+1 << " 'Put' value:\t" << batches[i]["P"] 
			<< endl << endl;
	}
	*/

	// create vector of test value doubles
	vector<double> test_val[]
	{
		{ 0.25, 65, 0.30, 0.08, 60, 2.13337, 5.84628 },
		{ 1.0, 100, 0.2, 0.0, 100, 7.96557, 7.96557 },
		{ 1.0, 10, 0.5, 0.12, 5, 0.204058, 4.07326 },
		{ 30.0, 100.0, 0.3, 0.08, 100.0, 92.1757, 1.2475 }
	};
	
	// create Tuple typedef: includes Option Parameters doubles, and Option type string
	// Tuple layout: T, K, sig, r, S, "Option Type", "Underlying Security", b_adjust 
	typedef boost::tuple<double, double, double, double, double, string, string, double> OptionParams;
	OptionParams test_params1(0.25, 65, 0.30, 0.08, 60);
	OptionParams test_params2(1.0, 100, 0.2, 0.0, 100);
	OptionParams test_params3(1.0, 10, 0.5, 0.12, 5);
	OptionParams test_params4(30.0, 100.0, 0.3, 0.08, 100.0);

	for (int i = 0; i < 4; i++)
	{
		cout << "\nBATCH " << i + 1 << ":  Test Run\n";
		cout << "\nRun a 'Call' option using Batch " << i + 1 << " parameters:\n";
		EuropeanOption callOption(, "C", 'S');
		//cout << "S: "; double S; cin >> S;
		cout << "Option on a stock:\t" << callOption.Price(batches[i]["S"])
			<< "\nBatch " << i + 1 << " 'Call' value:\t" << batches[i]["C"]
			<< endl << endl;

		cout << "Run a 'Put' option using Batch " << i + 1 << " parameters:\n";
		EuropeanOption putOption(batches[i], "P", 'S');
		cout << "Option on a stock:\t" << putOption.Price(batches[i]["S"])
			<< "\nBatch " << i + 1 << " 'Put' value:\t" << batches[i]["P"]
			<< endl << endl;
	}

	int i = 1;
	//for (auto vec_vals : test_val)
	//{
		//OptionParams test_params_
		//for (auto it = vec_vals.begin(); it != vec_vals.end(); it++)
			
	//}


	cout << endl << endl;

	
	/*
	// Call option on a stock (b = r by default)
	EuropeanOption callOption;
	cout << "S: "; double S; cin >> S;
	cout << "Option on a stock: " << callOption.Price(S) << endl;

	
	// Option on a stock index
	// create input tuple
	OptionParams opt_params(0.41667, 50.0, 0.0, 0.1, 50.0, "C", "Index", 0.0);

	//map<string, double> opt_params;
	//opt_params.emplace("K", 50.0);
	//opt_params.emplace("T", 0.41667);
	//opt_params.emplace("sig", 0.0);
	//opt_params.emplace("r", 0.1);
	//double dividend_yield = 0.0;		// Dividend yield
	//string option_type = "C";
	//char underlying = 'I';

	EuropeanOption optionIndex(opt_params);
	//indexOption.optType = "C";
	//indexOption.K = 50.0;
	//indexOption.T = 0.41667;
	//indexOption.sig = 0.00;
	//indexOption.r = 0.1;
	

	//double q = 0.0;		// Dividend yield
	//indexOption.b = indexOption.r - q;

	//cout << indexOption.optType << endl;
	cout << "\nOption Type: " << opt_params.get<5>() << endl;
	
	cout << " option on an index at Asset Price = 50.00:\n" 
		<< optionIndex.Price() << endl << endl;

	optionIndex.Print();

	cout << endl << endl;

	/*
	// Options on a future
	opt_params.clear();
	opt_params.emplace("K", 19.0);
	opt_params.emplace("T", 0.75);
	opt_params.emplace("r", 0.1);
	opt_params.emplace("sig", 0.28);
	option_type = "P";
	underlying = 'F';


	EuropeanOption futureOption(opt_params, option_type, underlying);
	//futureOption.optType = "P";
	//futureOption.K = 19.0;
	//futureOption.T = 0.75;
	//futureOption.r = 0.10;
	//futureOption.sig = 0.28;

	//futureOption.b = 0.0;

	cout << "Put option on a future: " << futureOption.Price(20.0) << endl;

	
	// Now change over to a call on the option
	futureOption.toggle();
	cout << "\nCall option on a future: " << futureOption.Price(20.0) << endl << endl;

	futureOption.Print();

	cout << endl;
	
	// Call option on currency
	opt_params.clear();
	opt_params.emplace("K", 1.60);
	opt_params.emplace("T", 0.5);
	opt_params.emplace("r", 0.06);
	opt_params.emplace("sig", 0.12);
	double risk_free_rate = 0.08;
	option_type = "C";
	underlying = 'C';


	EuropeanOption currencyOption(opt_params, option_type, underlying, risk_free_rate);
	//currencyOption.optType = "C";
	//currencyOption.K = 1.60;
	//currencyOption.T = 0.5;
	//currencyOption.r = 0.06;
	//currencyOption.sig = 0.12;

	//double rf = 0.08;		// risk-free rate of foreign currency
	//currencyOption.b = currencyOption.r - rf;

	cout << endl << "** Other pricing examples **" << endl << endl;

	cout << "Call option on a currency: " << currencyOption.Price(1.56) << endl;

	currencyOption.Print();

	cout << endl << endl;


	
	////////   NOW CALCULATIONS OF SENSITIVITIES //////////////////////////////////

	// Call and put options on a future: Delta and Elasticity
	opt_params.clear();
	opt_params.emplace("K", 100.0);
	opt_params.emplace("T", 0.5);
	opt_params.emplace("r", 0.10);
	opt_params.emplace("sig", 0.36);
	option_type = "P";
	underlying = 'F';


	EuropeanOption futureOption2(opt_params, option_type, underlying);
	//futureOption2.optType = "P";
	//futureOption2.K = 100.0;
	//futureOption2.T = 0.5;
	//futureOption2.r = 0.10;
	//futureOption2.sig = 0.36;

	//futureOption2.b = 0.0;

	cout << "Delta on a put future: " << futureOption2.Delta(105.0) << endl;

	// Now change over to a call on the option
	futureOption2.toggle();
	cout << "\nDelta on a call future: " << futureOption2.Delta(105.0) << endl << endl;

	
	// Some more data for testing; Calcuate price and delta a
	opt_params.clear();
	opt_params.emplace("K", 60.0);
	opt_params.emplace("T", 0.75);
	opt_params.emplace("r", 0.10);
	opt_params.emplace("sig", 0.30);
	option_type = "C";
	underlying = 'S';

	EuropeanOption stockOption(opt_params, option_type, underlying);
	//stockOption.optType = "C";
	//stockOption.K = 60.0;
	//stockOption.T = 0.75;
	//stockOption.r = 0.10;
	//stockOption.sig = 0.30;

	//stockOption.b = stockOption.r;

	cout << "\nS: "; cin >> S;
	cout << "Call Option on a stock: " << stockOption.Price(S) << endl;
	cout << "Delta on a call stock: " << stockOption.Delta(63.0) << endl << endl;

	stockOption.toggle();
	cout << "Put Option on a stock: " << stockOption.Price(S) << endl;
	cout << "Delta on a put stock: " << stockOption.Delta(63.0) << endl << endl;


	/*
	// Calculating theta of a European stock index
	EuropeanOption indexOption2;
	indexOption2.optType = "P";
	indexOption2.K = 405.0;
	indexOption2.T = 0.0833;	// One month expiration
	indexOption2.r = 0.07;
	indexOption2.sig = 0.20;

	double divYield = 0.05;		// Dividend yield, 5% per annum
	indexOption2.b = indexOption2.r - divYield;


	// Stock Option: Rho
	EuropeanOption stockOption2;
	stockOption2.optType = "C";
	stockOption2.K = 75.0;
	stockOption2.T = 1.0;
	stockOption2.r = 0.09;
	stockOption2.sig = 0.19;

	stockOption2.b = stockOption2.r;


	// Calculating Cost of Carry of a European stock index
	EuropeanOption indexOption3;
	indexOption3.optType = "P";
	indexOption3.K = 490.0;
	indexOption3.T = 0.222225;
	indexOption3.r = 0.08;
	indexOption3.sig = 0.15;

	double divYield3 = 0.05;		// Dividend yield, 5% per annum
	indexOption3.b = indexOption3.r - divYield3 ;

	*/
	return 0;
}
