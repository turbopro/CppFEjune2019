// TestEuropeanOption.cpp
//
// Test program for the exact solutions of European options. 
// Check answers with Haug 2007 book on option pricing.
//
// (C) Datasim Component Technology BV 2003-20011
//

#include "EuropeanOption.h"
#include "EuropeanOptionException.h"
#include "ExactPricingMethods.h"
#include "AmericanOption.h"
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
//#include <functional>

#include <boost/shared_ptr.hpp>	// Boost C Library Shared Pointer header file
//#include <boost/range/adaptors.hpp>

int main()
{
	// We make the class EuropeanOption a base class
	// An American optionmay be considered a special case of an European option
	// The class AmericanOption is derived from the class EuropeanOption
	// We use public inheritance
	

	/*
	
	*****************  Groups A&B: Exact Pricing Methods  *********************
	
	*/
	
	//  A
	//  EUROPEAN OPTION


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

	
	//cout << "\n\n"
	//	<< "|===================================================|\n"
	//	<< "|   A: Batch 1 thru 4, Call and Put Option Prices   |\n"
	//	<< "|===================================================|\n";

	//try			// check for and catch EuropeanOption Exceptions
	//{
	//	// Create vector of Map containers: function set_batch() stores Test Values into Map containers
	//	vector<map<string, double>> batches(map_size);
	//	for (int i = 0; i < map_size; i++)
	//		set_batch(batches[i], test_str0, test_val[i]);

	//	//EuropeanOption calloption(batches[0], "C", "Stock");
	//	//calloption.Print();

	//	//EuropeanOption* popt = &calloption;
	//	//popt->Print();

	//	
	//	// Run the Batch Tests for Call and Put Options on a Stock
	//	cout << "\nUnderlying Security = Stock\n";
	//	int i = 0;
	//	
	//	for (auto it = batches.begin(); it != batches.end(); it++, i++)
	//	{
	//		cout << "\nBATCH " << i + 1 << ":  Test Run\n";
	//		cout << "\nRun a 'Call' option using Batch " << i + 1 << " parameters:\n";
	//		EuropeanOption callOption(*it, "C", "Stock");
	//		//cout << "S: "; double S; cin >> S;
	//		cout << "Option on a stock:\t\t" << callOption.Price()
	//			<< "\nBatch " << i + 1 << " 'Call' value:\t\t" << (*it)["C"]
	//			<< endl << endl;

	//		cout << "Run a 'Put' option using Batch " << i + 1 << " parameters:\n";
	//		EuropeanOption putOption(batches[i], "P", "Stock");
	//		cout << "Option on a stock:\t\t" << putOption.Price()
	//			<< "\nBatch " << i + 1 << " 'Put' value:\t\t" << (*it)["P"]
	//			<< endl << endl;
	//	}
	//	
	//	
	//	/*    *********************************
	//	-- B --
	//	Apply the put-call parity relationship to compute call and put option prices. For example, given the 
	//	call price, compute the put price based on this formula using Batches 1 to 4. Check your answers with 
	//	the prices from 	part a).Note that there are two useful ways to implement parity : As a mechanism 
	//	to calculate the call(or put) price for a corresponding put (or call) price, or as a mechanism to 
	//	check if a given set of put / call prices satisfy parity.The ideal submission will neatly implement 
	//	both approaches.
	//	*/
	//	
	//	// APPROACH 1: given a Stock price S, with T, K, r, sig, and its call price, we calculate the relevant 
	//	// put price that establishes the put-call parity relationship
	//	// We use a function, put_call_arity(), that takes a EuropeanOption object argument, and returns a 
	//	// tuple of two doubles: the put price and the call price
	//	
	//	

	//	cout << "\n\n"
	//		<< "|===============================================|\n"
	//		<< "|      B: Batch 1 thru 4, Put-Call Parity:      |\n"
	//		<< "|                  Approach 1                   |\n"
	//		<< "|===============================================|\n\n";

	//	cout << "Approach 1: For a call option, we calculate the corresponding put option\n"
	//		<< "price using the put-call parity formula, C + Ke^(-rT) = P + S\n"
	//		<< "For a put option, we do the reverse\n"
	//		<< "The call and put prices stored in each Batch are displayed as a reference:\n\n";

	//
	//	string option_types[]{ "C", "P", "C", "P" };	// used to set the option type for the EuropeanOption object
	//	i = 0;		// numeric indexer
	//	for (auto it = batches.begin(); it != batches.end(); it++, i++)		// batches vector iterators
	//	{
	//		cout << "\nBatch " << i + 1 << " calculating Put-Call Parity prices\n";

	//		// Create a EuropeanOption object with values from each Batch, set as a Stock option
	//		EuropeanOption euro_option(*it, option_types[i], "Stock");
	//	
	//		// put_call_parity() function calculates and returns a tuple of put and call prices for the option object
	//		boost::tuple<double, double> parity_vals(euro_option.put_call_parity());

	//		// Display calculated prices
	//		cout << "\nPut Option Price:  " << parity_vals.get<0>()
	//			<< "\nCall Option Price: " << parity_vals.get<1>() << endl << endl;

	//		cout << "Batch " << i+1 << " stored call and put prices:\n"
	//			<< "\nPut Option price:  " << (*it)["P"]
	//			<< "\nCall Option price: " << (*it)["C"] << endl << endl << endl;
	//	}
	//

	//	cout << "\n\n"
	//		<< "|===============================================|\n"
	//		<< "|      B: Batch 1 thru 4, Put-Call Parity:      |\n"
	//		<< "|                  Approach 2                   |\n"
	//		<< "|===============================================|\n\n";

	//	// APPROACH 2: given a set of put and call prices, we calculate the call and put prices
	//	// then compare the calculated prices vs the given prices
	//	// We use our check_put_call_parity() function

	//	cout << "Approach 2: We will compare the 'C' and 'P' prices stored for the individual batch\n" 
	//		<< "vector, with the corresponding calculated Call and Put values for that batch:\n";

	//	i = 0;		// numeric indexer
	//	for (auto it = batches.begin(); it != batches.end(); it++, i++)		// batches vector iterators
	//	{
	//		cout << "\nBatch " << i + 1 << " comparing stored vs calculated Put / Call prices\n";

	//		// Create a EuropeanOption object with values from each Batch, set as a Stock option
	//		EuropeanOption euro_option(*it, option_types[i], "Stock");

	//		// check_put_call_parity() function returns true if put-call parity exists for call/put prices
	//		bool parity_check = euro_option.check_put_call_parity((*it)["C"], (*it)["P"]);

	//		// Display results of check
	//		if (parity_check) 
	//			cout << "\nBatch " << i + 1 << " stored Call and Put prices are in put-call parity\n\n";
	//		else
	//			cout << "\nBatch " << i + 1 << " stored Call and Put prices are NOT in put-call parity\n\n";		
	//	}
	//
	//	cout << endl;

	//	/*    *********************************
	//	-- C --
	//	Say we wish to compute option prices for a monotonically increasing range of underlying values 
	//	of S, for example 10, 11, 12, …, 50. To this end, the output will be a vector. This entails 
	//	calling the option pricing formulae for each value S and each computed option price will be 
	//	stored in a std::vector<double> object. It will be useful to write a global function that 
	//	produces a mesh array of doubles separated by a mesh size h.
	//	*/
	//	

	//	cout << "\n\n"
	//		<< "|==============================================|\n"
	//		<< "|               C: vector_pricer               |\n"
	//		<< "|==============================================|\n\n";

	//	// Set test parameters, input map and output vector
	//	// Input map<string,double> is a container with test parameter values
	//	// For the particular parameter under test, establish start/end values and step size, to 
	//	// be used to retrieve option prices relevant to the test parameter value
	//	// Set values for test parameter, option type, and underlying security
	//	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	//	// constant, while we increase the value of "S" monotnonically from a start to and end value
	//	// 
	//	// For K = 65.0
	//	// Start value for S = 50.0
	//	// End value for S = 64
	//	// Step size = 1.0
	//	// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
	//	// the constructor; the default b_adjust parameter value of vector_pricer will suffice
	//
	//	cout << "\nSetting up test parameters ... \n";
	//	string test_param = "S", option_type = "C", underlying_security = "Stock";
	//	double param_start = 50.0, param_end = 64.0, step_size = 1.0;
	//	map<string, double> test_params_map{ {"T", 0.25}, { "K", 65.0 }, { "sig", 0.3 },
	//		{ "r", 0.08 }, { "S", param_start } };

	//	// Create vector for option prices
	//	cout << "\nCreating vector to store option prices ... \n";
	//	vector<double> option_prices;

	//	// Call vector_pricer() to calculate option prices for various values of stock price S
	//	// vector_pricer() takes a map<string, double>, a vector of double, an end value double 
	//	// for the test parameter, a step size value double, an option type string, and an 
	//	// underlying security string  
	//	cout << "\nCalling vector_pricer function to calculate option prices based on test parameter ... \n";
	//	vector_pricer(test_params_map, option_prices, test_param, param_end, step_size,
	//		option_type, underlying_security);

	//	// display elements of prices vector
	//	for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	//	{
	//		if (option_type == "C") cout << "call option prices: " << (*it) << endl;
	//		else cout << "put option prices: " << (*it) << endl;
	//	}

	//
	//	cout << endl << endl;

	//
	//	cout << "\n\n"
	//		<< "|==============================================|\n"
	//		<< "|               D: matrix_pricer               |\n"
	//		<< "|==============================================|\n\n";

	//	//	*****************************
	//	//	-- D --

	//	// Reset/Set test parameters, input/output matrix and vector
	//	// Prices matrix is a vector of map<string, double> containers with test parameter values
	//	// For the particular parameter under test, establish start/end values and step size, to 
	//	// be used to determine vector size
	//	// Set values for test parameter, option type, and underlying security
	//	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	//	// constant, while we increase the value of "S" monotnonically from a start to and end value
	//	// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
	//	// the constructor; the default b_adjust parameter value of matrix_pricer will suffice
	//
	//	cout << "\n1.  Resetting and Setting up test parameters ... \n";
	//	//map<string, double> test_params_map{ {"T", 0.25}, { "K", 65.0 }, { "sig", 0.3 },
	//		//{ "r", 0.08 }, { "S", 60 } };
	//	//test_params_map["T"] = 0.25; test_params_map["K"] = 65.0; 
	//	//test_params_map["sig"] = 0.3; test_params_map["r"] = 0.08;
	//	//test_params_map["param_start"] = 55.0; test_params_map["param_end"] = 65.0;
	//	//test_params_map["step_size"] = 1.0;
	//	
	//	// create a map for testing parameter "S"
	//	map<string, double> test_params_S;
	//	test_params_S["T"] = 0.25; test_params_S["K"] = 65.0;
	//	test_params_S["sig"] = 0.3; test_params_S["r"] = 0.08;
	//	test_params_S["S"] = 55.0; test_params_S["param_end"] = 65.0;
	//	test_params_S["step_size"] = 1.0;
	//	
	//	// create a map for testing parameter "K"
	//	map<string, double> test_params_K;
	//	test_params_K["T"] = 0.25; test_params_K["S"] = 60.0;
	//	test_params_K["sig"] = 0.3; test_params_K["r"] = 0.08;
	//	test_params_K["K"] = 40.0; test_params_K["param_end"] = 90.0;
	//	test_params_K["step_size"] = 1.0;
	//	
	//	// create a map for testing parameter "T"
	//	map<string, double> test_params_T;
	//	test_params_T["S"] = 60.0; test_params_T["K"] = 65.0;
	//	test_params_T["sig"] = 0.3; test_params_T["r"] = 0.08;
	//	test_params_T["T"] = 0.083; test_params_T["param_end"] = 1.0;
	//	test_params_T["step_size"] = 0.083;

	//	// create a map for testing parameter "r"
	//	map<string, double> test_params_r;
	//	test_params_r["S"] = 60.0; test_params_r["K"] = 65.0;
	//	test_params_r["sig"] = 0.3; test_params_r["T"] = 0.25;
	//	test_params_r["r"] = 0.005; test_params_r["param_end"] = 0.1;
	//	test_params_r["step_size"] = 0.005;

	//	// create a map for testing parameter "sig"
	//	map<string, double> test_params_sig;
	//	test_params_sig["S"] = 60.0; test_params_sig["K"] = 65.0;
	//	test_params_sig["r"] = 0.08; test_params_sig["T"] = 0.25;
	//	test_params_sig["sig"] = 0.01; test_params_sig["param_end"] = 0.5;
	//	test_params_sig["step_size"] = 0.01;

	//	//param_start = 55.0; param_end = 65.0; step_size = 1.0;
	//	//test_params_map["S"] = param_start;		// set test parameter to start value
	//	
	//	//test_param = "S"; 
	//	option_type = "C"; underlying_security = "Stock";		

	//	// Clear vector for option prices
	//	cout << "\n2.  Clearing vector to store option prices ... \n";
	//	option_prices.clear();				// option prices vector store

	//	// Prices matrix container: vector of map<string, double>, of size based on test parameter values
	//	cout << "\n3.  Creating prices matrix container to store input test parameters and\n"
	//		<< "output option prices ... \n";
	//	map<string, map<string, double>> params_map;
	//	params_map["S"] = (test_params_S);
	//	//params_map["K"] = (test_params_K);
	//	//params_map["T"] = (test_params_T);
	//	//params_map["r"] = (test_params_r);
	//	//params_map["sig"] = (test_params_sig);

	//	// Call matrix_pricer() to calculate option prices for various values of stock price S, with other
	//	// parameters, K, T, sig, r, b, option type, and underlying asset held constant
	//	// matrix_pricer() takes a vector of map<string, double>, a vector of double, a test parameter string,
	//	// a step size double, an option type string, and an underlying security string  
	//	cout << "\n4.  Calling matrix pricer function to calculate option prices based on\ntest parameter: "
	//		<< test_param << ", in the range: " << param_start << " to " << param_end << endl << endl;
	//	matrix_pricer(params_map, option_prices, option_type, underlying_security);

	//	// display elements of prices vector
	//	for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	//	{
	//		if (option_type == "C") cout << "call option prices: " << (*it) << endl;
	//		else cout << "put option prices: " << (*it) << endl;
	//	}

	//}
	//catch (EuropeanOptionException& error_msg)	// catch OptionExceptions
	//{
	//	cout << error_msg.GetMessage() << endl << endl;
	//}
	//catch (...)	// catch all
	//{
	//	cout << "unknown exception caught..." << endl << endl;
	//}

	//cout << endl << endl;
	//



	//cout << "\n\n"
	//	<< "|==============================================|\n"
	//	<< "|     Option Sensitivities, aka the Greeks     |\n"
	//	<< "|==============================================|\n\n";

	////Option Sensitivities, aka the Greeks

	///*
	//a) Implement the above formulae for gamma for call and put future option pricing 
	//using the data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. 
	//(exact delta call = 0.5946, delta put = -0.3566).
	//*/	
	//
	//
	//// Set test parameters
	//cout << "\nResetting and Setting up test parameters ... \n";
	//map<string, double> opt_map{ {"T", 0.5}, { "K", 100.0 }, { "sig", 0.36 },
	//	{ "r", 0.1 }, { "S", 105 } };

	//// For b = 0.0, we set underlying_security = "Future" 
	//string test_param = "S", option_type = "C", underlying_security = "Future";

	//// Create Call type EuropeanOption object
	//cout << "\nCreating EuropeanOption ... \n";
	//EuropeanOption test_option(opt_map, option_type, underlying_security);

	//// Display option price
	//if (test_option.OptionType() == "C")
	//	cout << "\nCall option Delta value: " << test_option.Delta() << endl;
	//else
	//	cout << "\nPut option Delta value: " << test_option.Delta() << endl;

	//// Get put option price
	//// Toggle option type from call to put
	//test_option.toggle();
	//
	//// Display 
	//if (test_option.OptionType() == "C")
	//	cout << "\nAfter toggling the option type, Call option Delta value: " 
	//	<< test_option.Delta() << endl;
	//else
	//	cout << "\nAfter toggling the option type, Put option Delta value: " 
	//	<< test_option.Delta() << endl;
	//
	//cout << "\nExact call delta value = 0.5946, put delta value = -0.3566\n";

	//
	//cout << endl << endl;
	//
	///*
	//b) We now use the code in part a to compute call delta price for a monotonically 
	//increasing range of underlying values of S, for example 10, 11, 12, …, 50. To 
	//this end, the output will be a vector and it entails calling the above formula 
	//for a call delta for each value S and each computed option price will be store 
	//in a std::vector<double> object. It will be useful to reuse the above global 
	//function that produces a mesh array of double separated by a mesh size h.
	//*/
	//
	//// Set test parameters, input map and output vector
	//	// Input map<string,double> is a container with test parameter values
	//	// For the particular parameter under test, establish start/end values and step size, to 
	//	// be used to retrieve option prices relevant to the test parameter value
	//	// Set values for test parameter, option type, and underlying security
	//	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	//	// constant, while we increase the value of "S" monotnonically from a start to and end value
	//
	//
	//cout << "\nSetting up test parameters ... \n";
	//test_param = "S"; option_type = "C"; underlying_security = "Future";
	//double param_start = 75.0, param_end = 125.0, step_size = 1.0;
	//map<string, double> test_params_map{ {"T", 0.5}, { "K", 100.0 }, { "sig", 0.36 },
	//	{ "r", 0.1 }, { "S", param_start } };

	//// Create a map<string, vector<double>> container for option prices: 
	//// The string stores the name of the member function used to obtain the prices/values 
	//// The vector<double> stores the calculated prices/values returned by the member function  
	//cout << "\n1.  Creating map to hold vectors of Deltas, Gammas, and Option Prices ...\n";
	//map<string, vector<double>> option_measures;

	//// Call vector_pricer() to calculate option gamma prices for a range of values of stock price S
	//// vector_pricer() takes a map<string, double>, a map<string, vector<double>>, an end value
	//// double for the test parameter, a step size value double, a function pointer, a function
	//// name, an option type string, an underlying security string, and a b_adjust double
	//cout << "\n2.  We will calculate gamma values for the following option parameters that\n"
	//	<< "will be held constant:\n"
	//	<< "K = " << test_params_map["K"] << ", T = " << test_params_map["T"]
	//	<< ", sig = " << test_params_map["sig"] << ", and r = " << test_params_map["r"]
	//	<< "\n\n3.  The test parameter, " << test_param << ", will increase monotonically through a"
	//	<< " range of\nvalues from:\n"
	//	<< param_start << " to " << param_end << ", with a step size of: " << step_size
	//	<< "\n\nCalling vector_pricer function to calculate option gamma values:\n"<< endl;
	//
	//// Create vector of strings for EuropeanOption member function names, Delta, Gamma, Price
	//// Create map<string, EuroMemFn> that maps EuropeanOption member function names to pointer
	//// to member functions
	//// We use the "typedef double (EuropeanOption::* EuroMemFn)(double) const" declared in
	//// ExactPricingMethods.h for the type EuroMemFn
	//// We use the above containers as vector_pricer_by_fn function arguments:
	//// Function names serve as keys for the option_measures map<string, vector<double>> container
	//// Function pointers point to the relevant member functions that calculate the prices/values
	//vector<string> fn_name {"Delta", "Gamma", "Price" };
	//map<string, EuroMemFn> fn_name_ptr { {"Price", &EuropeanOption::Price},
	//	{"Delta", &EuropeanOption::Delta}, {"Gamma", &EuropeanOption::Gamma} };

	//// get values for gamma
	//vector_pricer_by_fn(test_params_map, option_measures, test_param, param_end, step_size, fn_name_ptr[fn_name[1]],
	//	fn_name[1], option_type, underlying_security);

	//// display elements of option_prices map
	//for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
	//{
	//	if (option_type == "C")
	//	{
	//		cout << "Call option " << it->first << " values are:\n";
	//		for (auto val : it->second)
	//			cout << val << endl;
	//	}
	//		//<< " prices: " << (*it) << endl;
	//	else
	//	{
	//		cout << "Put option " << it->first << ", values are:\n";
	//		for (auto val : it->second)
	//			cout << val << endl;
	//	}
	//}


	//cout << endl << endl;

	///*
	//c) Incorporate this into your above matrix pricer code, so you can input a matrix of 
	//option parameters and receive a matrix of either Delta or Gamma as the result.
	//*/

	//// Set test parameters matrix
	//// Use vector_pricer on each input vector
	//
	////====================

	//// Reset/Set test parameters, input/output matrix and vector
	//// Prices matrix is a vector of map<string, double> containers with test parameter values
	//// For the particular parameter under test, establish start/end values and step size, to 
	//// be used to determine vector size
	//// Set values for test parameter, option type, and underlying security
	//// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	//// constant, while we increase the value of "S" monotnonically from a start to and end value
	//// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
	//// the constructor; the default b_adjust parameter value of matrix_pricer will suffice

	//
	//cout << "\n1.  Resetting and Setting up test parameters ... \n";

	//// create a map for testing parameter "S"
	//map<string, double> test_params_S;
	//test_params_S["T"] = 0.25; test_params_S["K"] = 65.0;
	//test_params_S["sig"] = 0.3; test_params_S["r"] = 0.08;
	//test_params_S["S"] = 55.0; test_params_S["param_end"] = 65.0;
	//test_params_S["step_size"] = 1.0;

	//// create a map for testing parameter "K"
	//map<string, double> test_params_K;
	//test_params_K["T"] = 0.25; test_params_K["S"] = 60.0;
	//test_params_K["sig"] = 0.3; test_params_K["r"] = 0.08;
	//test_params_K["K"] = 40.0; test_params_K["param_end"] = 90.0;
	//test_params_K["step_size"] = 1.0;

	//// create a map for testing parameter "T"
	//map<string, double> test_params_T;
	//test_params_T["S"] = 60.0; test_params_T["K"] = 65.0;
	//test_params_T["sig"] = 0.3; test_params_T["r"] = 0.08;
	//test_params_T["T"] = 0.083; test_params_T["param_end"] = 1.0;
	//test_params_T["step_size"] = 0.083;

	//// create a map for testing parameter "r"
	//map<string, double> test_params_r;
	//test_params_r["S"] = 60.0; test_params_r["K"] = 65.0;
	//test_params_r["sig"] = 0.3; test_params_r["T"] = 0.25;
	//test_params_r["r"] = 0.005; test_params_r["param_end"] = 0.1;
	//test_params_r["step_size"] = 0.005;

	//// create a map for testing parameter "sig"
	//map<string, double> test_params_sig;
	//test_params_sig["S"] = 60.0; test_params_sig["K"] = 65.0;
	//test_params_sig["r"] = 0.08; test_params_sig["T"] = 0.25;
	//test_params_sig["sig"] = 0.01; test_params_sig["param_end"] = 0.5;
	//test_params_sig["step_size"] = 0.01;

	//option_type = "C"; underlying_security = "Stock";

	//// Clear vector for option prices
	//cout << "\n2.  Clearing vector to store option prices ... \n";
	//option_measures.clear();				// option measures vector store

	//// Prices matrix container: vector of map<string, double>, of size based on test parameter values
	//cout << "\n3.  Creating prices matrix container to store input test parameters and\n"
	//	<< "output option prices ... \n";
	//map<string, map<string, double>> params_map;
	//params_map["S"] = (test_params_S);
	////params_map["K"] = (test_params_K);
	////params_map["T"] = (test_params_T);
	////params_map["r"] = (test_params_r);
	////params_map["sig"] = (test_params_sig);

	//// Call matrix_pricer() to calculate option prices for various values of stock price S, with other
	//// parameters, K, T, sig, r, b, option type, and underlying asset held constant
	//// matrix_pricer_fn() takes a map<string, map<string, double>>, a vector of double, a test parameter
	//// string, a step size double, an option type string, and an underlying security string  
	//cout << "\n4.  Calling matrix pricer function to calculate option prices based on\ntest parameter: "
	//	<< test_param << ", in the range: " << param_start << " to " << param_end << endl << endl;
	//
	//// The matrix_pricer_by_fn() definition includes a call to the vector_pricer_by_fn() function
	//cout << "\nCalling matrix pricer function to calculate option prices, deltas and gammas "
	//	<< "\nbased on test parameter: " << test_param << " ... \n";
	//for (auto name_ptr : fn_name_ptr)
	//{
	//	matrix_pricer_by_fn(params_map, option_measures, name_ptr.second, name_ptr.first, 
	//		option_type, underlying_security);
	//}

	//// display elements of option_measures map
	//for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
	//{
	//	if (option_type == "C")
	//	{
	//		cout << "\nCall option " << it->first << " values are:\n";
	//		for (auto val : it->second)
	//			cout << val << endl;
	//	}
	//	else
	//	{
	//		cout << "\nPut option " << it->first << " values are:\n";
	//		for (auto val : it->second)
	//			cout << val << endl;
	//	}
	//}

	///*
	//d) We now use divided differences to approximate option sensitivities. In some cases, 
	//an exact formula may not exist (or is difficult to find) and we resort to numerical 
	//methods. In general, we can approximate first and second-order derivatives in S by 
	//3-point second order approximations, for example:

	//	Delta =>	d = (V(S + h) - V(S - h)) / 2h
	//	Gamma =>	g = (V(S + h) - 2V(S) + V(S - h)) / h^2

	//	d => delta
	//	g => gamma
	//	V(S) => option price at Asset price S
	//	h => delta change in S

	//In this case the parameter h is ‘small’ in some sense. By Taylor’s expansion you can 
	//show that the above approximations are second order accurate in h to the corresponding 
	//derivatives. 
	//
	//The objective of this part is to perform the same calculations as in parts a and b, 
	//but now using divided differences. Compare the accuracy with various values of the 
	//parameter h (In general, smaller values of h produce better approximations but we need 
	//to avoid round-offer errors and subtraction of quantities that are very close to each 
	//other). Incorporate this into your well-designed class structure.

	//*/

	//
	//// Set range of h with a vector of doubles
	//int range = 10;
	//std::vector<double> h_range(range);
	////strided_iota(std::begin(h_range), std::next(std::begin(h_range), vec_size), 10.0, 0.1);
	//strided_iota(std::begin(h_range), std::end(h_range), 10.0, 0.1);

	//// Set option test parameters
	//test_params_map["T"] = 0.25; test_params_map["K"] = 65.0;
	//test_params_map["sig"] = 0.3; test_params_map["r"] = 0.08;

	////param_start = 55.0; param_end = 65.0; step_size = 1.0;
	//test_params_map["S"] = 64;		// set test parameter to start value

	//test_param = "S"; option_type = "P"; underlying_security = "Stock";

	//// Clear vector for option prices
	//cout << "\nClearing map to store option prices ... \n";
	//option_measures.clear();				// option prices map store

	//
	//vector<double> gammas;

	//for (auto h : h_range)
	//{
	//	//EuropeanOption (test_params_map, option_type, underlying_security);
	//	gammas.push_back(
	//		EuropeanOption(test_params_map, option_type, underlying_security).GammaDividedDiff(h));
	//}

	//cout << endl;

	//for (auto gamma : gammas) cout << "gamma: " << gamma << endl;
	//

	//vector<double> deltas;

	//for (auto h : h_range)
	//{
	//	//EuropeanOption (test_params_map, option_type, underlying_security);
	//	deltas.push_back(
	//		EuropeanOption(test_params_map, option_type, underlying_security).DeltaDividedDiff(h));
	//}

	//cout << endl;

	//for (auto delta : deltas) cout << "delta: " << delta << endl;


	//cout << endl << endl;
	//
	//cout << "\nGamma at S = 64 by default: " 
	//	<< EuropeanOption(test_params_map, option_type, underlying_security).Gamma();
	//cout << "\nGamma at S = 64 as arg: "
	//	<< EuropeanOption(test_params_map, option_type, underlying_security).Gamma(64)
	//	<< endl << endl;
	
	
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	//  B
	//  AMERICAN OPTION

	//Test Values for option pricing follows :
	//Batch 1 : T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	//Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	//Batch 3 : T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	//Batch 4 : T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)

	/*
	cout << "\n\n"
		<< "|==============================================|\n"
		<< "|        B. Perpetual American Options         |\n"
		<< "|==============================================|\n\n";

	/*
	a) Program the above formulae, and incorporate into your well-designed options pricing classes.
	b) Test the data with K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106).	
	*/
	/*
	map<string, double> test_am_param{ {"K", 100.0}, {"S", 110.0}, {"T", 1.0}, {"r", 0.1}, {"sig", 0.1} };
	// For b = 0.02, set asset type to :Index:m and b-adjust = 0.08
	// We set T = 1 for completeness only; T does not factor into the calculation of price for American
	// options
	cout << "\nCreate American call option with the following parameters:\n"
		<< "K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110";
	AmericanOption test_am_option(test_am_param, "C", "Index", 0.08);
	
	cout << "\nPerpetual American option, call option price: " << test_am_option.Price();
	test_am_option.toggle();
	cout << "\nPerpetual American option, put option price: " << test_am_option.Price();
	cout << endl << endl;

	/*
	c) We now use the code in part a) to compute call and put option price for a monotonically 
	increasing range of underlying values of S, for example 10, 11, 12, …, 50. To this end, the 
	output will be a vector and this exercise entails calling the option pricing formulae in 
	part a) for each value S and each computed option price will be stored in a 
	std::vector<double> object. It will be useful to reuse the above global function that 
	produces a mesh array of double separated by a mesh size h.

	d) Incorporate this into your above matrix pricer code, so you can input a matrix of option 
	parameters and receive a matrix of Perpetual American option prices.
	
	*/

	// Set test parameters, input map and output vector
	// Input map<string,double> is a container with test parameter values
	// For the particular parameter under test, establish start/end values and step size, to 
	// be used to retrieve option prices relevant to the test parameter value
	// Set values for test parameter, option type, and underlying security
	// As an example, when we test parameter "S," we will hold parameters "K" "sig" "r" "b"
	// constant, while we increase the value of "S" monotnonically from a start to and end value
	//
	//

	/*
	cout << "\nSetting up test parameters ... \n";
	string test_param = "S", option_type = "C", underlying_security = "Index";
	double param_start = 75.0, param_end = 125.0, step_size = 1.0;
	map<string, double> test_params_map{ {"T", 1.0}, { "K", 100.0 }, { "sig", 0.1 },
		{ "r", 0.1 }, { "S", param_start } };
	double b_adjust = 0.08;

	// Create a map<string, vector<double>> container for option prices: 
	// The string stores the name of the member function used to obtain the prices/values 
	// The vector<double> stores the calculated prices/values returned by the member function  
	cout << "\n1.  Creating map to hold vectors of Deltas, Gammas, and Option Prices ...\n";
	map<string, vector<double>> option_measures;

	// Call vector_pricer() to calculate option prices for a range of values of stock price S
	// vector_pricer() takes a map<string, double>, a map<string, vector<double>>, an end value
	// double for the test parameter, a step size value double, a function pointer, a function
	// name, an option type string, an underlying security string, and a b_adjust double
	cout << "\n2.  We will calculate option prices for the following option parameters that\n"
		<< "will be held constant:\n"
		<< "K = " << test_params_map["K"] << ", sig = " << test_params_map["sig"] 
		<< ", and r = " << test_params_map["r"]
		<< "\n\n3.  The test parameter, " << test_param << ", will increase monotonically through a"
		<< " range of\nvalues from:\n"
		<< param_start << " to " << param_end << ", with a step size of: " << step_size
		<< "\nb = 0.02 will be set by setting b_adust - 0.08"
		<< "\n\nCalling vector_pricer function to calculate perpetual American option prices:\n\n";
	
	//	// Create vector for option prices
		cout << "\nCreating vector to store option prices ... \n";
		vector<double> option_prices;

	// Call vector_pricer() to calculate option prices for various values of stock price S
	// vector_pricer() takes a map<string, double>, a vector of double, an end value double 
	// for the test parameter, a step size value double, an option type string, and an 
	// underlying security string  
	cout << "\nCalling vector_pricer function to calculate perpetual American call option\n"
		<< "prices based on test parameter ... \n";
	vector_pricer(test_params_map, option_prices, test_param, param_end, step_size,
			option_type, underlying_security);

	// display elements of prices vector
	for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	{
		if (option_type == "C") cout << "American call option prices: " << (*it) << endl;
		else cout << "American put option prices: " << (*it) << endl;
	}

	// typedef double (EuropeanOption::* EuroMemFn)(double) const;		// for EuropeanOption
	//typedef double (AmericanOption::* AmerMemFn)(double) const;		// for AmericanOption
	//double (AmericanOption::* EurotoAmerFn)(double) const = &EuropeanOption::Price;		// for AmericanOption

	cout << endl << endl;

	/// testing prices()

	//EuropeanOption test_option;
	*/
	
	map<string, double> test_param0{ {"K", 100.0}, {"S", 110.0}, {"T", 1.0}, {"r", 0.1}, {"sig", 0.1} };
	// For b = 0.02, set asset type to :Index:m and b-adjust = 0.08
	// We set T = 1 for completeness only; T does not factor into the calculation of price for American
	// options
	cout << "\nCreate Eurpean call option with the following parameters:\n"
		<< "K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110, T = 1.0";
	EuropeanOption test_option(test_param0, "C", "Index", 0.08);
	AmericanOption test_am0(test_param0, "C", "Index", 0.08);
	
	cout << "\nEuropean option, call option price: " << test_option.Price();
	test_option.toggle();
	cout << "\nEuropean option, put option price: " << test_option.Price();
	cout << endl << endl;
	test_option.toggle();
	
	// create vector of prices for S in range 75 to 125

	vector<double> call_prices = prices(test_option, 95.0, 105.0, 1.0);
	for (auto price : call_prices)
		cout << "\nprice; " << price;

	cout << endl << endl;

	cout << "\nAmerican option, call option price: " << test_am0.Price();
	test_am0.toggle();
	cout << "\nEuropean option, put option price: " << test_am0.Price();
	cout << endl << endl;
	test_am0.toggle();

	// create vector of prices for S in range 75 to 125

	vector<double> call_am0 = prices(test_am0, 95.0, 125.0, 1.0);
	for (auto price : call_am0)
		cout << "\nprice; " << price;


	cout << endl << endl;



	cout << endl << endl;


	return 0;
}
