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
#include <random>

#include <boost/shared_ptr.hpp>	// Boost C Library Shared Pointer header file
//#include <boost/range/adaptors.hpp>

int main()
{
	// All options are European
	
	
	/*	********************************** 
	-- A --
	Implement the above formulae for call and put option pricing using the data sets
	Batch 1 to Batch 4. Check your answers, as you will need them when we discuss
	numerical methods for option pricing.

	Cost of carry factor b must be included in formulae depending on the
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

	cout << "\n\n"
		<< "|===================================================|\n"
		<< "|   A: Batch 1 thru 4, Call and Put Option Prices   |\n"
		<< "|===================================================|\n";

	// Create vector of Map containers: function set_batch() stores Test Values into Map containers
	vector<map<string, double>> batches(map_size);
	for (int i = 0; i < map_size; i++)
		set_batch(batches[i], test_str0, test_val[i]);

	// Run the Batch Tests for Call and Put Options on a Stock
	cout << "\nUnderlying Security = Stock\n";
	int i = 0;
	for (auto it = batches.begin(); it != batches.end(); it++, i++)
	{
		cout << "\nBATCH " << i + 1 << ":  Test Run\n";
		cout << "\nRun a 'Call' option using Batch " << i + 1 << " parameters:\n";
		EuropeanOption callOption(*it, "C", "Stock");
		//cout << "S: "; double S; cin >> S;
		cout << "Option on a stock:\t\t" << callOption.Price()
			<< "\nBatch " << i + 1 << " 'Call' value:\t\t" << (*it)["C"]
			<< endl << endl;

		cout << "Run a 'Put' option using Batch " << i + 1 << " parameters:\n";
		EuropeanOption putOption(batches[i], "P", "Stock");
		cout << "Option on a stock:\t\t" << putOption.Price()
			<< "\nBatch " << i + 1 << " 'Put' value:\t\t" << (*it)["P"]
			<< endl << endl;
	}
	
	
	/*    *********************************
	-- B --
	Apply the put-call parity relationship to compute call and put option prices. For example, given the 
	call price, compute the put price based on this formula using Batches 1 to 4. Check your answers with 
	the prices from 	part a).Note that there are two useful ways to implement parity : As a mechanism 
	to calculate the call(or put) price for a corresponding put (or call) price, or as a mechanism to 
	check if a given set of put / call prices satisfy parity.The ideal submission will neatly implement 
	both approaches.
	*/

	// APPROACH 1: given a Stock price S, with T, K, r, sig, and its call price, we calculate the relevant 
	// put price that establishes the put-call parity relationship
	// We use a function, put_call_arity(), that takes a EuropeanOption object argument, and returns a 
	// tuple of two doubles: the put price and the call price

	cout << "\n\n"
		<< "|===============================================|\n"
		<< "|      B: Batch 1 thru 4, Put-Call Parity:      |\n"
		<< "|                  Approach 1                   |\n"
		<< "|===============================================|\n\n";

	cout << "Approach 1: For a call option, we calculate the corresponding put option\n"
		<< "price using the put-call parity formula, C + Ke^(-rT) = P + S\n"
		<< "For a put option, we do the reverse\n"
		<< "The call and put prices stored in each Batch are displayed as a reference:\n\n";

	string option_types[]{ "C", "P", "C", "P" };	// used to set the option type for the EuropeanOption object
	i = 0;		// numeric indexer
	for (auto it = batches.begin(); it != batches.end(); it++, i++)		// batches vector iterators
	{
		cout << "\nBatch " << i + 1 << " calculating Put-Call Parity prices\n";

		// Create a EuropeanOption object with values from each Batch, set as a Stock option
		EuropeanOption euro_option(*it, option_types[i], "Stock");
		
		// put_call_parity() function calculates and returns a tuple of put and call prices for the option object
		boost::tuple<double, double> parity_vals(euro_option.put_call_parity());

		// Display calculated prices
		cout << "\nPut Option Price:  " << parity_vals.get<0>()
			<< "\nCall Option Price: " << parity_vals.get<1>() << endl << endl;

		cout << "Batch " << i+1 << " stored call and put prices:\n"
			<< "\nPut Option price:  " << (*it)["P"]
			<< "\nCall Option price: " << (*it)["C"] << endl << endl << endl;
	}


	cout << "\n\n"
		<< "|===============================================|\n"
		<< "|      B: Batch 1 thru 4, Put-Call Parity:      |\n"
		<< "|                  Approach 2                   |\n"
		<< "|===============================================|\n\n";

	// APPROACH 2: given a set of put and call prices, we calculate the call and put prices
	// then compare the calculated prices vs the given prices
	// We use our check_put_call_parity() function

	cout << "Approach 2: We will compare the 'C' and 'P' prices stored for the individual batch\n" 
		<< "vector, with the corresponding calculated Call and Put values for that batch:\n";

	i = 0;		// numeric indexer
	for (auto it = batches.begin(); it != batches.end(); it++, i++)		// batches vector iterators
	{
		cout << "\nBatch " << i + 1 << " comparing stored vs calculated Put / Call prices\n";

		// Create a EuropeanOption object with values from each Batch, set as a Stock option
		EuropeanOption euro_option(*it, option_types[i], "Stock");

		// check_put_call_parity() function returns true if put-call parity exists for call/put prices
		bool parity_check = euro_option.check_put_call_parity((*it)["C"], (*it)["P"]);

		// Display results of check
		if (parity_check) 
			cout << "\nBatch " << i + 1 << " stored Call and Put prices are in put-call parity\n\n";
		else
			cout << "\nBatch " << i + 1 << " stored Call and Put prices are NOT in put-call parity\n\n";		
	}

	cout << endl;

	/*    *********************************
	-- C --
	Say we wish to compute option prices for a monotonically increasing range of underlying values 
	of S, for example 10, 11, 12, …, 50. To this end, the output will be a vector. This entails 
	calling the option pricing formulae for each value S and each computed option price will be 
	stored in a std::vector<double> object. It will be useful to write a global function that 
	produces a mesh array of doubles separated by a mesh size h.
	*/

	cout << "\n\n"
		<< "|==============================================|\n"
		<< "|               C: vector_pricer               |\n"
		<< "|==============================================|\n\n";

	// Set test parameters, input map and output vector
	// Input map<string,double> is a container with test parameter values
	// For the particular parameter under test, establish start/end values and step size, to 
	// be used to retrieve option prices relevant to the test parameter value
	// Set values for test parameter, option type, and underlying security
	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	// constant, while we increase the value of "S" monotnonically from a start to and end value
	
	cout << "\nSetting up test parameters ... \n";
	map<string, double> test_params_map{ {"T", 0.25}, { "K", 65.0 }, { "sig", 0.3 },
		{ "r", 0.08 }, { "S", 60 } };
	string test_param = "S", option_type = "P", underlying_security = "Stock";
	double param_start = 55.0, param_end = 66.0, step_size = 1.0;

	// Create vector for option prices
	cout << "\nCreating vector to store option prices ... \n";
	vector<double> option_prices;				// option prices vector store

	// Map container: map<string, double> to hold test parameter values
	//cout << "\nCreating map<string, double> container to store test parameters and option prices ... \n";
	//<map<string, double> params_map(((param_end - param_start) / step_size), test_params_map);

	// Call vector_pricer() to calculate option prices for various values of stock price S
	// vector_pricer() takes a map<string, double>, a vector of double, a test parameter double,
	// a start value double for the test parameter, and end value double for the test parameter, 
	// a step size double, an option type string, and an underlying security string  
	cout << "\nCalling vector_pricer function to calculate option prices based on test parameter ... \n";
	vector_pricer(test_params_map, option_prices, param_start, param_end, step_size, test_param,
		option_type, underlying_security);

	// display elements of prices vector
	for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	{
		if (option_type == "C") cout << "call option prices: " << (*it) << endl;
		else cout << "put option prices: " << (*it) << endl;
	}

	cout << endl << endl;

	
	/*
	//generate **********--D--**************
	//         *****************************
	double test;
	// Set test parameters, input/output matrix and vector
	// Prices matrix is a vector of map<string, double> containers with test parameter values
	// For the particular parameter under test, establish start/end values and step size, to 
	// be used to determine vector size
	// Set values for test parameter, option type, and underlying security
	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	// constant, while we increase the value of "S" monotnonically from a start to and end value
	
	cout << "\nSetting up test parameters ... \n";
	map<string, double> test_params_map{ {"T", 0.25}, { "K", 65.0 }, { "sig", 0.3 },
		{ "r", 0.08 }, { "S", 60 } };
	string test_param = "S", option_type = "P", underlying_security = "Stock";
	double param_start = 55.0, param_end = 66.0, step_size = 1.0;

	// Create vector for option prices
	cout << "\nCreating vector to store option prices ... \n";
	vector<double> option_prices;				// option prices vector store

	// Prices matrix container: vector of map<string, double>, of size based on test parameter values
	cout << "\nCreating prices matrix container to store test parameters and option prices ... \n";
	vector<map<string, double>> params_map(((param_end - param_start) / step_size), test_params_map);

	// Call matrix_pricer() to calculate option prices for various values of stock price S
	// matrix_pricer() takes a vector of map<string, double>, a vector of double, a test parameter double,
	// a start value double for the test parameter, a step size double, an option type string, and
	// an underlying security string  
	cout << "\nCalling matrix pricer function to calculate option prices based on test parameter ... \n";
	matrix_pricer(params_map, option_prices, test_param, param_start, step_size, 
		option_type, underlying_security);

	// display elements of prices vector
	for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	{
		if (option_type == "C") cout << "call option prices: " << (*it) << endl;
		else cout << "put option prices: " << (*it) << endl;
	}

	cout << endl << endl;
	


	/*
	// C setup matrix for testing various S prices
	// map contains options parameters as key, value pairs of type <string, double>: 
	// "T",T, "K",K, "sig",sig, "r",r, "S",S 
	// T, K, sig, r will remain constant, while S will increase monotonically from 
	// K-100 to K-1 in steps of 1
	//
	map<string, double> opt_map { {"T", 0.5}, { "K", 110.0 }, { "sig", 0.2 },
		{ "r", 0.05 }, { "S", 106 } };
	// create vector of option parameters with range of values
	string param[] = { "T", "K", "sig", "r", "S" };
	const int range_divider = 100;
	vector<map<string, double>> mat_options(range_divider, opt_map);
	vector<double> vecT(100);
	vec_range(vecT, 0.01, 1.01);

	vector<double> vecK(100);
	vec_range(vecK, 11.0, 111);

	vector<double> vecsig(100);
	vec_range(vecsig, 0.05, 0.55);

	vector<double> vecr(100);
	vec_range(vecr, 0.1, 10.1);

	vector<double> vecS(100);
	vec_range(vecS, 1, 101);

	int i = 0;
	for (auto it = mat_options.begin(); it != mat_options.end(); ++it, ++i)
	{
		(*it)["T"] = vecT[i];
		(*it)["K"] = vecK[i];
		(*it)["sig"] = vecsig[i];
		(*it)["r"] = vecr[i];
		(*it)["S"] = vecS[i];
	}

	i = 0;
	for (auto it = mat_options.begin(); it != mat_options.end(); ++it, ++i)
	{
		cout << "\nmat_options[\"sig\"]: " << (*it)["sig"] << endl;
	}


	//for (auto v : vecr) cout << "v: " << v << endl;

	cout << endl << endl;

	//vector<double> param_factor;
	//param_factor.push_back(get<0>(range_vec.at(0)));

	//cout << "\nparam_factor:" << param_factor[0] << endl << endl;

	/*
	map<string, double> opt_map{ {"T", 0.5}, { "K", 110.0 }, { "sig", 0.2 },
		{ "r", 0.05 }, { "S", 106 } };
	const int range = 5;		// set number pf steps for S
	// Create vector of map contaners with options
	vector<map<string, double>> mat_options(range_divider, opt_map);
	int i = 0;
	for (auto it = mat_options.begin(); it != mat_options.end(); ++it, ++i)
	{
		(*it)["S"] += i;
	}
	
	
	cout << endl << endl;
	

	// Get call option price for each value of S
	// Add call option price to map_options
	for (auto it = mat_options.begin(); it != mat_options.end(); it++)
	{
		(*it).emplace("C", EuropeanOption(*it, "C", "Stock").Price());
	}
	
	cout << endl << endl;

	
	for (auto vec : mat_options)
	{
		cout << "for Stock Price: " << vec["S"] 
			<< ", Call Option Price: " << vec["C"] << endl;
	}
	

	cout << endl << endl;

	cout << endl << endl;

	/*
	// Call option on a stock (b = r by default)
	EuropeanOption callOption;
	cout << "S: "; double S; cin >> S;
	cout << "Option on a stock: " << callOption.Price(S) << endl;

	/*
	// Option on a stock index
	
	// Input parameters:
	// optType = "C"
	// underlying = "Index"
	// K = 50.0;
	// T = 0.41667;
	// sig = 0.00;
	// r = 0.1;
	// S = 50.0			// Stock Price
	// q = 0.0			// Dividend yield
	// b = r - q		// Cost of Carry

	map<string, double> opt_params;
	opt_params.emplace("K", 50.0);
	opt_params.emplace("T", 0.41667);
	opt_params.emplace("sig", 0.0);
	opt_params.emplace("r", 0.1);
	opt_params.emplace("S", 50.0);
	string option_type = "C";
	string underlying = "Index";
	double dividend_yield = 0.0;		// Dividend yield (b_adjust input parameter)


	// create an index option object
	EuropeanOption optionIndex(opt_params, option_type, underlying, dividend_yield);
	
	cout << "\nOption Type: " << option_type << endl;
	
	cout << "\nOption on an index at Asset Price = 50.00:\n" 
		<< optionIndex.Price() << endl << endl;

	optionIndex.Print();

	cout << endl << endl;

	
	// Options on a future

	opt_params.clear();
	opt_params.emplace("K", 19.0);
	opt_params.emplace("T", 0.75);
	opt_params.emplace("r", 0.1);
	opt_params.emplace("sig", 0.28);
	opt_params.emplace("S", 20.0);
	option_type = "P";
	underlying = "Future";
	double future_b = 0.0;

	EuropeanOption futureOption(opt_params, option_type, underlying, future_b);

	//futureOption.optType = "P";
	//futureOption.K = 19.0;
	//futureOption.T = 0.75;
	//futureOption.r = 0.10;
	//futureOption.sig = 0.28;

	//futureOption.b = 0.0;

	cout << " option on a future: " << futureOption.Price() << endl;
	
	// Now change over to a call on the option
	futureOption.toggle();
	cout << " option on a future: " << futureOption.Price() << endl << endl;

	futureOption.Print();

	cout << endl;
	
	
	// Call option on currency
	
	opt_params.clear();
	opt_params.emplace("K", 1.60);
	opt_params.emplace("T", 0.5);
	opt_params.emplace("r", 0.06);
	opt_params.emplace("sig", 0.12);
	opt_params.emplace("S", 1.56);
	double risk_free_rate = 0.08;		// risk-free rate of foreign currency
	option_type = "C";
	underlying = "Currency";

	EuropeanOption currencyOption(opt_params, option_type, underlying, risk_free_rate);
	//currencyOption.optType = "C";
	//currencyOption.K = 1.60;
	//currencyOption.T = 0.5;
	//currencyOption.r = 0.06;
	//currencyOption.sig = 0.12;

	//double rf = 0.08;			// risk-free rate of foreign currency
	//currencyOption.b = currencyOption.r - rf;
	

	cout << " option on a currency: " << currencyOption.Price() << endl;

	currencyOption.Print();

	cout << endl << endl;

	
	cout << endl << "** Other pricing examples **" << endl << endl;

	
	////////   NOW CALCULATIONS OF SENSITIVITIES //////////////////////////////////

	// Call and put options on a future: Delta and Elasticity
	opt_params.clear();
	opt_params.emplace("K", 100.0);
	opt_params.emplace("T", 0.5);
	opt_params.emplace("r", 0.10);
	opt_params.emplace("sig", 0.36);
	opt_params.emplace("S", 105.0);
	future_b = 0.0;
	option_type = "P";
	underlying = 'F';
	
	EuropeanOption futureOption2(opt_params, option_type, underlying, future_b);
	//futureOption2.optType = "P";
	//futureOption2.K = 100.0;
	//futureOption2.T = 0.5;
	//futureOption2.r = 0.10;
	//futureOption2.sig = 0.36;

	//futureOption2.b = 0.0;

	cout << "Delta on a put future: " << futureOption2.Delta() << endl;

	// Now change over to a call on the option
	futureOption2.toggle();
	cout << "\nDelta on a call future: " << futureOption2.Delta() << endl << endl;

	
	// Some more data for testing; Calcuate price and delta a
	// For Stock, b = r: constructor creates the option properly
	opt_params.clear();
	opt_params.emplace("K", 60.0);
	opt_params.emplace("T", 0.75);
	opt_params.emplace("r", 0.10);
	opt_params.emplace("sig", 0.30);
	option_type = "C";
	underlying = "Stock";
		
	//stockOption.optType = "C";
	//stockOption.K = 60.0;
	//stockOption.T = 0.75;
	//stockOption.r = 0.10;
	//stockOption.sig = 0.30;

	//stockOption.b = stockOption.r;

	cout << "\nS: "; cin >> S;
	opt_params.emplace("S", S);
	EuropeanOption stockOption(opt_params, option_type, underlying);

	cout << "Call Option on a stock: " << stockOption.Price() << endl;
	cout << "Delta on a call stock: " << stockOption.Delta(63.0) << endl << endl;

	stockOption.toggle();
	cout << "Put Option on a stock: " << stockOption.Price() << endl;
	cout << "Delta on a put stock: " << stockOption.Delta(63.0) << endl << endl;
	

	
	/*
	// Calculating theta of a European stock index
	//EuropeanOption indexOption2;
	//indexOption2.optType = "P";
	//indexOption2.K = 405.0;
	//indexOption2.T = 0.0833;	// One month expiration
	//indexOption2.r = 0.07;
	//indexOption2.sig = 0.20;

	opt_params.clear();
	opt_params.emplace("K", 405.0);
	opt_params.emplace("T", 0.0833);
	opt_params.emplace("r", 0.07);
	opt_params.emplace("sig", 0.20);
	// assuming S = 395.0
	opt_params.emplace("S", 395.0);
	dividend_yield = 0.05;
	option_type = "P";
	underlying = "Index";
	 //double divYield = 0.05;		// Dividend yield, 5% per annum
	//indexOption2.b = indexOption2.r - divYield;
	 
	cout << "\nCalculating Price and Theta:\n";
	EuropeanOption indexOption(opt_params, option_type, underlying, dividend_yield);

	cout << " option on an index: " << indexOption.Price(395.0) << endl;
	cout << "Delta on a call index: " << indexOption.Delta(395.0) << endl << endl;

	//indexOption.toggle();
	//cout << " option on an index: " << indexOption.Price(395.0) << endl;
	//cout << "Delta on a put index: " << indexOption.Delta(395.0) << endl << endl;

	double res = indexOption.Theta();

	cout << "\nTheta: " << res << endl << endl;
	//cout << "\nTheta: " << indexOption.Theta() << endl << endl;
	

	/*
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
