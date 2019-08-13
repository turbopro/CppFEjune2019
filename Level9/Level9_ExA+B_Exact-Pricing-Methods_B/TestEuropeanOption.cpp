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

	// *******************************************************
	// First block of try/catch to segregate homework answers
	// *******************************************************
	
	cout << "\n\n"
		<< "|===================================================|\n"
		<< "|   A: Batch 1 thru 4, Call and Put Option Prices   |\n"
		<< "|===================================================|\n";

	try			// check for and catch EuropeanOption Exceptions
	{
		// Create vector of Map containers: function set_batch() stores Test Values into Map containers
		vector<map<string, double>> batches(map_size);
		for (int i = 0; i < map_size; i++)
			set_batch(batches[i], test_str0, test_val[i]);

		EuropeanOption calloption(batches[0], "C", "Stock");
		calloption.Print();
		
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
	

		cout << endl << endl;
		
		
		
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

		 //APPROACH 2: given a set of put and call prices, we calculate the call and put prices
		 //then compare the calculated prices vs the given prices
		 //We use our check_put_call_parity() function

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
		 
		// For K = 65.0
		// Start value for S = 50.0
		// End value for S = 64
		// Step size = 1.0
		// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
		// the constructor; the default b_adjust parameter value of vector_pricer will suffice
	

		// Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)

		cout << "\nSetting up test parameters ... \n";
		string test_param = "K", option_type = "C", underlying_security = "Stock";
		double param_initial = 60.0, param_start = 50.0, param_end = 64.0, step_size = 1.0;
		map<string, double> test_params_map{ {"T", 0.25}, { "K", 65.0 }, { "sig", 0.3 },
			{ "r", 0.08 }, { "S", 60.0 } };
		EuropeanOption test_euro(test_params_map, option_type, underlying_security);
		cout << "\ntest_euro parameters:\n";
		test_euro.Print();
		cout << "\ntest_euro call price: " << test_euro.Price() << endl;
		test_euro.toggle();
		cout << "\ntest_euro put price: " << test_euro.Price() << endl;
		test_euro.toggle();

		EuropeanOption test_euro_0(batches[0], option_type, underlying_security);
		double p_start = 60.0, p_end = 70.0, step_sz = 1.0;
		vector<EuropeanOption> k_test_vec;

		// Create vector for option prices
		cout << "\nCreating vector to store option prices ... \n";
		vector<double> option_prices;

		// Call vector_pricer() to calculate option prices for various values of stock price S
		// vector_pricer() takes a map<string, double>, a vector of double, an end value double 
		// for the test parameter, a step size value double, an option type string, and an 
		// underlying security string  
		cout << "\nCalling vector_pricer function to calculate option prices based on test parameter ... \n";
		//vector_pricer(test_params_map, option_prices, test_param, param_end, step_size,
			//option_type, underlying_security);
		//prices(test_euro, option_prices, test_param, p_start, p_end, step_sz);

		// create function pointers to setter member functions
		map<string, EuroSetFn> p_setter_fn
		{ {"S", &EuropeanOption::SetS}, {"K", &EuropeanOption::SetK}, {"T", &EuropeanOption::SetT},
			{"r", &EuropeanOption::SetR}, {"sig", &EuropeanOption::SetSig}, {"b", &EuropeanOption::SetB},
		};

		// input vector of values for test parameter 
		vector<double> param_vec{ param_initial, param_start, param_end, step_size };

		// get Call option prices for monotonically increasing values of S
		prices_setfn(test_euro, option_prices, p_setter_fn["S"], param_vec);

		// display elements of prices vector
		for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
		{
			if (option_type == "C") cout << "call option prices: " << (*it) << endl;
			else cout << "put option prices: " << (*it) << endl;
		}

		
		cout << endl << endl;
	
	
		cout << "\n\n"
			<< "|==============================================|\n"
			<< "|               D: matrix_pricer               |\n"
			<< "|==============================================|\n\n";

		/*	*****************************
			-- D --
		d) Now we wish to extend part c and compute option prices as a function of
		// i) expiry time, ii) volatility, or iii) any of the option pricing parameters.
		// Essentially, the purpose here is to be able to input a matrix (vector of vectors)
		// of option parameters and receive a matrix of option prices as the result.
		// Encapsulate this functionality in the most flexible/robust way you can think of.
		
		Reset/Set test parameters, input/output matrix and vector
		 Prices matrix is a vector of map<string, double> containers with test parameter values
		 For the particular parameter under test, establish start/end values and step size, to 
		 be used to determine vector size
		 Set values for test parameter, option type, and underlying security
		 As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
		 constant, while we increase the value of "S" monotnonically from a start to and end value
		 For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
		 the constructor; the default b_adjust parameter value of matrix_pricer will suffice
		*/

		cout << "\n1.  Resetting and Setting up test parameters ... \n";
		
		// We will use the batches map container for test options
		// Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628) 

		//EuropeanOption test_euro_0(batches[0], option_type, underlying_security);
		p_start = 60.0; p_end = 70.0; step_size = 1.0;
		
		// create map<string, vector<double>> to store input parameters 
		map<string, vector<double>> params
		{
			{ "S", { 60.0, 60.0, 70.0, 1.0 } },
			{ "K", { 65.0, 60.0, 70.0, 1.0 } },
			{ "T", { 0.25, 0.05, 1.0, 0.05 } },
			{ "r", { 0.08, 0.01, 0.1, 0.01 } },
			{ "sig", { 0.3, 0.05, 0.5, 0.05 } }
		};

		//map<string, vector<double>> euro_prices = m_prices(test_euro_0, params);
		map<string, vector<double>> euro_prices;
		matrix_prices_setfn(test_euro_0, params, euro_prices, p_setter_fn);

		// display elements of prices vector
		cout << "\nmarix_prices_setfn output:\n\n";
		display_measures(euro_prices, "C");
		/*
		for (auto it = euro_prices.begin(); it != euro_prices.end(); ++it)
		{
			if (option_type == "C")
			{
				cout << "call option prices for testparameter, - "
					<< (*it).first << " - are:\n";
				for (auto price : it->second)
					cout << price << endl;
			}
			else
			{
				cout << "\nput option prices for testparameter, - "
					<< (*it).first << " - are:\n";
				for (auto price : it->second)
					cout << price << endl;
			}
		}
		*/

	}
	catch (EuropeanOptionException& error_msg)	// catch OptionExceptions
	{
		cout << error_msg.GetMessage() << endl << endl;
	}
	catch (...)	// catch all
	{
		cout << "unknown exception caught..." << endl << endl;
	}

	cout << endl << endl;
	
	// *******************************************************




	// *******************************************************
	// Second block of try/catch to segregate homework answers
	// *******************************************************

	try
	{
		cout << "\n\n"
			<< "|==============================================|\n"
			<< "|     Option Sensitivities, aka the Greeks     |\n"
			<< "|==============================================|\n\n";

		//Option Sensitivities, aka the Greeks

		/*
		a) Implement the above formulae for gamma for call and put future option pricing 
		using the data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. 
		(exact delta call = 0.5946, delta put = -0.3566).
		*/	
	
	
		// Set test parameters
		cout << "\nResetting and Setting up test parameters ... \n";
		map<string, double> opt_map{ {"T", 0.5}, { "K", 100.0 }, { "sig", 0.36 },
			{ "r", 0.1 }, { "S", 105 } };

		// For b = 0.0, we set underlying_security = "Future" 
		string test_param = "S", option_type = "C", underlying_security = "Future";

		// Create Call type EuropeanOption object
		cout << "\nCreating EuropeanOption ... \n";
		EuropeanOption test_option(opt_map, option_type, underlying_security);

		// Display option price
		if (test_option.OptionType() == "C")
			cout << "\nCall option Delta value: " << test_option.Delta() << endl;
		else
			cout << "\nPut option Delta value: " << test_option.Delta() << endl;

		// Get put option price
		// Toggle option type from call to put
		test_option.toggle();
	
		// Display 
		if (test_option.OptionType() == "C")
			cout << "\nAfter toggling the option type, Call option Delta value: " 
			<< test_option.Delta() << endl;
		else
			cout << "\nAfter toggling the option type, Put option Delta value: " 
			<< test_option.Delta() << endl;
	
		cout << "\nExact call delta value = 0.5946, put delta value = -0.3566\n";

	
		cout << endl << endl;
	
		///*
		//b) We now use the code in part a to compute call delta price for a monotonically 
		//increasing range of underlying values of S, for example 10, 11, 12, …, 50. To 
		//this end, the output will be a vector and it entails calling the above formula 
		//for a call delta for each value S and each computed option price will be store 
		//in a std::vector<double> object. It will be useful to reuse the above global 
		//function that produces a mesh array of double separated by a mesh size h.
		//*/
		//
		// Set test parameters, input map and output vector
		// Input map<string,double> is a container with test parameter values
		// For the particular parameter under test, establish start/end values and step size, to 
		// be used to retrieve option prices relevant to the test parameter value
		// Set values for test parameter, option type, and underlying security
		// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
		// constant, while we increase the value of "S" monotnonically from a start to and end value
		//
		// data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. 
		// (exact delta call = 0.5946, delta put = -0.3566).
		
		// We use the same test_option as for part a) above
		cout << "\nSetting up test parameters ... \n";
		test_param = "S"; option_type = "C"; underlying_security = "Future";
		double param_initial = 105.0, param_start = 95.0, param_end = 115.0, step_size = 1.0;

		// create function pointers to setter member functions
		map<string, EuroSetFn> p_setter_fn
		{ {"S", &EuropeanOption::SetS}, {"K", &EuropeanOption::SetK}, {"T", &EuropeanOption::SetT},
			{"r", &EuropeanOption::SetR}, {"sig", &EuropeanOption::SetSig}, {"b", &EuropeanOption::SetB},
		};

		// input vector of values for test parameter 
		vector<double> param_vec{ param_initial, param_start, param_end, step_size };

		// Create a map<string, vector<double>> container for option prices: 
		// The string stores the name of the member function used to obtain the prices/values 
		// The vector<double> stores the calculated prices/values returned by the member function  
		//cout << "\n1.  Creating map to hold vectors of Deltas, Gammas, and Option Prices ...\n";
		//map<string, vector<double>> option_measures;

		// Call prices_fn() to calculate option delta prices for a range of values of stock price S
		// prices_fn() takes an option, a vector<double>, a function pointer to member function,
		// a test parameter string, parameter start value double, a parameter end value double,
		// a step size double, and a b_adjust double
		cout << "\n2.  We will calculate delta values for the following option parameters that\n"
			<< "will be held constant:\n"
			<< "K = " << opt_map["K"] << ", T = " << opt_map["T"] << ", sig = " << opt_map["sig"] 
			<< ", and r = " << opt_map["r"] << "\n\n3.  The test parameter, " 
			<< test_param << ", will increase monotonically through a range of\nvalues from:\n"
			<< param_start << " to " << param_end << ", with a step size of: " << step_size
			<< "\n\nCalling prices_fn function to calculate option delta values:\n"<< endl;
	
		// Create vector of strings for EuropeanOption member function names, Delta, Gamma, Price
		// Create map<string, EuroMemFn> that maps EuropeanOption member function names to pointer
		// to member functions
		// We use the "typedef double (EuropeanOption::* EuroMemFn)(double) const" declared in
		// ExactPricingMethods.h for the type EuroMemFn
		// We use the above containers as vector_pricer_by_fn function arguments:
		// Function names will serve as labels for the output vectors eventually
		// Function pointers point to the relevant member functions that calculate the prices/values
		vector<string> fn_name {"Delta", "Gamma", "Price" };
		map<string, EuroMemFn> p_price_fn { {"Price", &EuropeanOption::Price},
			{"Delta", &EuropeanOption::Delta}, {"Gamma", &EuropeanOption::Gamma} };

		// change option type to call, "C"
		test_option.toggle();
	
		// create vector of doubles to collect/store deltas
		vector<double> option_prices;
		//map<string, vector<double>> option_measures;
		// get values for delta for a monotonically increasing range of S values
		//prices_fn(test_option, option_measures, fn_name_ptr[fn_name[0]], fn_name[0], test_param, 
			//param_start, param_end, step_size);

		pricer_set_by_fn(test_option, option_prices, p_setter_fn["S"], p_price_fn[fn_name[0]], param_vec);

		// display deltas for range of S
		cout << "\nTest parameter:\t" << test_param
			<< "\nRange start:\t" << param_start
			<< "\nRange end:\t" << param_end
			<< "\nStep size:\t" << step_size
			<< "\nOption type:\t" << option_type << endl;

		display_measures(option_prices, "C");

		/*
		for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
		{
			if (option_type == "C")
			{
				cout << "\nCall option measure " << it->first << endl;
				for (auto price : it->second)
					cout << "\t" << price << endl;
			}
			else
			{
				cout << "\nPut option measure " << it->first << endl;
				for (auto price : it->second)
					cout << "\t" << price << endl;
			}
		}
		*/
		////////////////////////////////////
		// We now do the same range of value for S for delta, gamma, and price
		// Use the same test_option

		// clear output map
		//option_measures.clear();

		cout << "\n\nRun similar test of monotonically increasing test parameter S"
			"for Delta, Gamma, and Price:\n";

		// loop over the string vector of member function names and call pricer_ste_by_fn for
		// each option measure member function
		// collect each loop's vector output into a map<string, vector<double>>
		map<string, vector<double>> option_measures;

		for (auto name : fn_name)
		{
			// get values for delta for a monotonically increasing range of S values
			pricer_set_by_fn(test_option, option_prices, p_setter_fn["S"], p_price_fn[name], param_vec);
			
			option_measures[name] = option_prices;		// add option measures to map container
			option_prices.clear();						// clear vector of measures
		}
	

		// display deltas, gammas, and prices for range of S
		cout << "\nTest parameter:\t" << test_param
			<< "\nRange start:\t" << param_start
			<< "\nRange end:\t" << param_end
			<< "\nStep size:\t" << step_size
			<< "\nOption type:\t" << option_type << endl;

		for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
		{
			if (option_type == "C")
			{
				cout << "\nCall option measure " << it->first << endl;
				for (auto price : it->second)
					cout << "\t" << price << endl;
			}
			else
			{
				cout << "\nPut option measure " << it->first << endl;
				for (auto price : it->second)
					cout << "\t" << price << endl;
			}
		}



		cout << endl << endl;

		/*
		c) Incorporate this into your above matrix pricer code, so you can input a matrix of 
		option parameters and receive a matrix of either Delta or Gamma as the result.
		*/

		// Set test parameters matrix
		// data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. 
		// (exact delta call = 0.5946, delta put = -0.3566).
	
		//====================

		// Reset/Set test parameters, input/output matrix and vector
		// Prices matrix is a vector of map<string, double> containers with test parameter values
		// For the particular parameter under test, establish start/end values and step size, to 
		// be used to determine vector size
		// Set values for test parameter, option type, and underlying security
		// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
		// constant, while we increase the value of "S" monotnonically from a start to and end value
		// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
		// the constructor; the default b_adjust parameter value of matrix_pricer will suffice

	
		cout << "\n1.  Resetting and Setting up test parameters ... \n";

		// create a map for testing parameter "S"
	
		option_type = "C"; underlying_security = "Stock";

		// Clear vector for option prices
		cout << "\n2.  Clearing vector to store option prices ... \n";
		option_measures.clear();				// option measures vector store

		// Prices matrix container: vector of map<string, double>, of size based on test parameter values
		cout << "\n3.  Creating prices matrix container to store input test parameters and\n"
			<< "output option prices ... \n";
		map<string, map<string, double>> params_map;
	
		// create map<string, vector<double>> to store input parameters 
		map<string, vector<double>> params
		{
			{ "S", { 105.0, 85.0, 125.0, 1.0 } },
			{ "K", { 100.0, 80.0, 120.0, 1.0 } },
			{ "T", { 0.5, 0.25, 0.75, 0.05 } },
			{ "r", { 0.1, 0.05, 0.15, 0.01 } },
			{ "sig", { 0.36, 0.05, 0.5, 0.05 } }
		};


		// Call matrix_pricer() to calculate option prices for various values of stock price S, with other
		// parameters, K, T, sig, r, b, option type, and underlying asset held constant
		// matrix_pricer_fn() takes a map<string, map<string, double>>, a vector of double, a test parameter
		// string, a step size double, an option type string, and an underlying security string  
		cout << "\n4.  Calling matrix pricer function to calculate option prices based on\ntest parameter: "
			<< test_param << ", in the range: " << param_start << " to " << param_end << endl << endl;
	
		// The matrix_pricer_by_fn() definition includes a call to the vector_pricer_by_fn() function
		cout << "\nCalling matrix pricer function to calculate option prices, deltas and gammas "
			<< "\nbased on test parameter: " << test_param << " ... \n";
		//for (auto name_ptr : fn_name_ptr)
		//{
			//matrix_pricer_by_fn(params_map, option_measures, name_ptr.second, name_ptr.first, 
				//option_type, underlying_security);
		//}


		// test each option parameter across a range of values: get Deltas for test_option
		//m_prices_fn(test_option, params, option_measures, p_price_fn["Delta"], "Delta");
		matrix_pricer_by_fn0(test_option, params, option_measures, p_price_fn["Delta"], p_setter_fn, "Delta");


		// display elements of option_measures map
		for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
		{
			if (option_type == "C")
			{
				cout << "\nCall option measure " << it->first << " values are:\n";
				for (auto val : it->second)
					cout << val << endl;
			}
			else
			{
				cout << "\nPut option measure " << it->first << " values are:\n";
				for (auto val : it->second)
					cout << val << endl;
			}
		}

	}
	catch (EuropeanOptionException& error_msg)	// catch OptionExceptions
	{
		cout << error_msg.GetMessage() << endl << endl;
	}
	catch (...)	// catch all
	{
		cout << "unknown exception caught..." << endl << endl;
	}

	//cout << endl << endl;

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
	//// Set range of h; create vector of doubles of size = h
	//int range = 10;
	//std::vector<double> h_range(range);
	////strided_iota(std::begin(h_range), std::next(std::begin(h_range), vec_size), 10.0, 0.1);
	//strided_iota(std::begin(h_range), std::end(h_range), 10.0, 0.1);

	//// Set option test parameters
	//map<string, double> test_params_map;
	//test_params_map["T"] = 0.25; test_params_map["K"] = 65.0;
	//test_params_map["sig"] = 0.3; test_params_map["r"] = 0.08;

	////param_start = 55.0; param_end = 65.0; step_size = 1.0;
	//test_params_map["S"] = 64;		// set test parameter to start value

	//string test_param = "S", option_type = "P", underlying_security = "Stock";

	//// Clear vector for option prices
	//cout << "\nCreating map to store option prices ... \n";
	////option_measures.clear();				// option prices map store
	//map<string, vector<double>> option_measures;
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

	//// *******************************************************
	//// Section B
	//// *******************************************************
	//  AMERICAN OPTION

	//Test Values for option pricing follows :
	//Batch 1 : T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628)
	//Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	//Batch 3 : T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	//Batch 4 : T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750)

	
	//cout << "\n\n"
	//	<< "|==============================================|\n"
	//	<< "|        B. Perpetual American Options         |\n"
	//	<< "|==============================================|\n\n";

	///*
	//a) Program the above formulae, and incorporate into your well-designed options pricing classes.
	//b) Test the data with K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110 (check C = 18.5035, P = 3.03106).	
	//*/
	//
	//map<string, double> test_am_param{ {"K", 100.0}, {"S", 110.0}, {"T", 1.0}, {"r", 0.1}, {"sig", 0.1} };
	//// For b = 0.02, set asset type to :Index:m and b-adjust = 0.08
	//// We set T = 1 for completeness only; T does not factor into the calculation of price for American
	//// options
	//cout << "\nCreate American call option with the following parameters:\n"
	//	<< "K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110";
	//AmericanOption test_am_option(test_am_param, "C", "Index", 0.08);
	//
	//cout << "\nPerpetual American option, call option price: " << test_am_option.Price();
	//test_am_option.toggle();
	//cout << "\nPerpetual American option, put option price: " << test_am_option.Price();
	//cout << endl << endl;

	/*
	c) We now use the code in part a) to compute call and put option price for a monotonically 
	increasing range of underlying values of S, for example 10, 11, 12, …, 50. To this end, the 
	output will be a vector and this exercise entails calling the option pricing formulae in 
	part a) for each value S and each computed option price will be stored in a 
	std::vector<double> object. It will be useful to reuse the above global function that 
	produces a mesh array of double separated by a mesh size h.
	
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

	
	cout << "\nSetting up test parameters ... \n";
	string test_param = "S", option_type = "C", underlying_security = "Index";
	double param_start = 105.0, param_end = 115.0, step_size = 1.0, param_initial = 110.0;
	map<string, double> test_params_map{ {"T", 1.0}, { "K", 100.0 }, { "sig", 0.1 },
		{ "r", 0.1 }, { "S", param_initial } };
	double b_adjust = 0.08;

	// input vector of values for test parameter 
	vector<double> param_vec{ param_initial, param_start, param_end, step_size };

	// Create Call type AmericanOption object
	cout << "\nCreating AmericanOption ... \n";
	AmericanOption amer_option(test_params_map, option_type, underlying_security, b_adjust);

	cout << "\n2.  We will calculate option prices for the following option parameters that\n"
		<< "will be held constant:\n"
		<< "K = " << test_params_map["K"] << ", sig = " << test_params_map["sig"] 
		<< ", and r = " << test_params_map["r"]
		<< "\n\n3.  The test parameter, " << test_param << ", will increase monotonically through a"
		<< " range of\nvalues from:\n"
		<< param_start << " to " << param_end << ", with a step size of: " << step_size
		<< "\nb = 0.02 will be set by setting b_adust - 0.08"
		<< "\n\nCalling vector_pricer function to calculate perpetual American option prices:\n\n";
	
	// Create vector for option prices
	cout << "\nCreating vector to store option prices ... \n";
	vector<double> amer_call_option_prices;
	vector<double> amer_put_option_prices;

	// create function pointers to setter member functions
	map<string, EuroSetFn> p_setter_fn
	{ {"S", &EuropeanOption::SetS}, {"K", &EuropeanOption::SetK}, {"T", &EuropeanOption::SetT},
		{"r", &EuropeanOption::SetR}, {"sig", &EuropeanOption::SetSig}, {"b", &EuropeanOption::SetB},
	};

	// Call prices_setfn() to calculate option prices for a range of values of stock price S
	// prices_setfn() takes:
	// option			-	the option to be tested
	// vector<double>	-	output vector
	// function pointer	-	to a setter member function (SetT, SetK, SetS, SetSig ...)
	// vector<double>	-	input values for the test parameter
	cout << "\nCalling prices_setfn function to calculate perpetual American call option\n"
		<< "prices based on test parameter ... \n";
	
	prices_setfn(amer_option, amer_call_option_prices, p_setter_fn["S"], param_vec);

	cout << endl << endl;
	for (auto it : amer_call_option_prices) 
		cout << "American call option prices: " << it << endl;

	cout << "\nCalling prices_setfn function to calculate perpetual American put option\n"
		<< "prices based on test parameter ... \n";
	amer_option.toggle();
	prices_setfn(amer_option, amer_put_option_prices, p_setter_fn["S"], param_vec);

	cout << endl << endl;
	for (auto it : amer_put_option_prices)
		cout << "American put option prices: " << it << endl;

	cout << endl << endl;
	
	// -----------------------------
	// We make use of prices_fn to use any of the Delta, Gamma, or Price member functions
	// Function pointers point to the relevant member functions that calculate the prices/values
	vector<string> fn_name {"Delta", "Gamma", "Price"};
	map<string, EuroPriceFn> p_price_fn { {"Price", &EuropeanOption::Price},
		{"Delta", &EuropeanOption::Delta}, {"Gamma", &EuropeanOption::Gamma} };

	amer_call_option_prices.clear();
	amer_option.toggle();
	amer_option.Print();

	// get call option prices
	pricer_set_by_fn(amer_option, amer_call_option_prices, p_setter_fn["S"], p_price_fn["Price"], param_vec);

	cout << endl << endl;
	for (auto it = amer_call_option_prices.begin(); it != amer_call_option_prices.end(); ++it)
	{
		if (option_type == "C") cout << "American call option prices: " << (*it) << endl;
	}

	cout << endl << endl;

	// get put option prices
	amer_option.toggle();
	pricer_set_by_fn(amer_option, amer_call_option_prices, p_setter_fn["S"], p_price_fn["Price"], param_vec);

	cout << endl << endl;
	for (auto it = amer_call_option_prices.begin(); it != amer_call_option_prices.end(); ++it)
	{
		if (option_type == "C") cout << "American put option prices: " << (*it) << endl;
	}

	cout << endl << endl;


	// ********************************************************
	// d) Incorporate this into your above matrix pricer code, so you can input a matrix of option 
	// parametersand receive a matrix of Perpetual American option prices.
	
	
	// Set test parameters matrix
	// data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. 
	// (exact delta call = 0.5946, delta put = -0.3566).
	
	// --------Test the data with 
	// K = 100, sig = 0.1, r = 0.1, b = 0.02, S = 110
	// (check C = 18.5035, P = 3.03106).	
	//
	//====================

	// Reset/Set test parameters, input/output matrix and vector
	// Prices matrix is a vector of map<string, double> containers with test parameter values
	// For the particular parameter under test, establish start/end values and step size, to 
	// be used to determine vector size
	// Set values for test parameter, option type, and underlying security
	// As an example, when we test parameter "S," we will hold parameters "T" "K" "sig" "r" 
	// constant, while we increase the value of "S" monotnonically from a start to and end value
	// For a Stock, the b_adjust (cost of carry) parameter will be assigned the r value for in
	// the constructor; the default b_adjust parameter value of matrix_pricer will suffice

	
	cout << "\n1.  Resetting and Setting up test parameters ... \n";
	// Clear vector for option prices; reset american option to type "C";
	cout << "\n2.  Clearing vector to store option prices ... \n";
	amer_option.toggle();
	amer_call_option_prices.clear(); amer_put_option_prices.clear();

	// create a map for testing parameter "S"
	// option_measures.clear();				// option measures vector store

	// Create parameter matrix map: a map of individual string test parameter identifiers, with 
	// a vector of double that includes the test parameter values to be adjusted during the test
	cout << "\n3.  Creating test parameters map container:\n";
	
	// create map<string, vector<double>> to store input parameters 
	map<string, vector<double>> params
	{
		{ "S", { 110.0, 85.0, 125.0, 1.0 } },
		{ "K", { 100.0, 80.0, 120.0, 1.0 } },
		//{ "T", { 0.5, 0.25, 0.75, 0.05 } },	T not used in price formula for American Options
		{ "r", { 0.1, 0.05, 0.15, 0.01 } },
		{ "sig", { 0.1, 0.05, 0.5, 0.05 } }
	};


	// Call matrix_pricer() to calculate option prices for various values of stock price S, with other
	// parameters, K, T, sig, r, b, option type, and underlying asset held constant
	// matrix_pricer_fn() takes a map<string, map<string, double>>, a vector of double, a test parameter
	// string, a step size double, an option type string, and an underlying security string  
	cout << "\n4.  Calling matrix pricer function to calculate option prices based on\ntest parameter: "
		<< test_param << ", in the range: " << param_start << " to " << param_end << endl << endl;
	
	// The matrix_pricer_by_fn() definition includes a call to the vector_pricer_by_fn() function
	cout << "\nCalling matrix pricer function to calculate option prices, deltas and gammas "
		<< "\nbased on test parameter: " << test_param << " ... \n";
	//for (auto name_ptr : fn_name_ptr)
	//{
		//matrix_pricer_by_fn(params_map, option_measures, name_ptr.second, name_ptr.first, 
			//option_type, underlying_security);
	//}
	//amer_option.SetS(105.0);
	cout << endl << endl;
	amer_option.Print();
	cout << endl << endl;
	map<string, vector<double>> price_measures;

	// test each option parameter across a range of values
	// get Call option prices for amer_option
	matrix_pricer_by_fn0(amer_option, params, price_measures, p_price_fn["Price"],
		p_setter_fn, "Price");

	cout << endl;
	// display elements of option_measures map
	display_measures(price_measures, option_type);

	// get Put option prices for amer_option
	amer_option.toggle();
	matrix_pricer_by_fn0(amer_option, params, price_measures, p_price_fn["Price"],
		p_setter_fn, "Price");
	cout << endl;
	// display elements of option_measures map
	display_measures(price_measures, option_type);


	/*for (auto it = price_measures.begin(); it != price_measures.end(); ++it)
	{
		if (option_type == "C")
		{
			cout << "\nCall option measure " << it->first << " values are:\n";
			for (auto val : it->second)
				cout << val << endl;
		}
		else
		{
			cout << "\nPut option measure " << it->first << " values are:\n";
			for (auto val : it->second)
				cout << val << endl;
		}
	}*/
	/*
	}
	catch (EuropeanOptionException& error_msg)	// catch OptionExceptions
	{
		cout << error_msg.GetMessage() << endl << endl;
	}
	catch (...)	// catch all
	{
		cout << "unknown exception caught..." << endl << endl;
	}
	*/
	cout << endl << endl;


	//cout << "\nSetting up test parameters ... \n";
	//string test_param = "S", option_type = "C", underlying_security = "Index";
	//double param_start = 110.0, param_end = 125.0, step_size = 1.0;
	//map<string, double> test_params_am{ {"T", 1.0}, { "K", 100.0 }, { "sig", 0.1 },
	//	{ "r", 0.1 }, { "S", param_start } };
	//double b_adjust = 0.08;

	////// Create Call type EuropeanOption object
	//cout << "\nCreating AmericanOption ... \n";
	//AmericanOption amer_option(test_params_am, option_type, underlying_security, b_adjust);
	//

	//// Implement the above formulae for gamma for call and put future option pricing using the 
	//// data set: K = 100, S = 105, T = 0.5, r = 0.1, b = 0 and sig = 0.36. (exact delta call = 0.5946, delta put = -0.3566).
	//map<string, double> test_params_eu{ {"T", 0.5}, { "K", 100.0 }, { "sig", 0.36 },
	//	{ "r", 0.1 }, { "S", 105 } };
	//underlying_security = "Future";
	//EuropeanOption euro_option(test_params_eu, option_type, underlying_security);

	//cout << "\namer_option call option price: " << amer_option.Price() << endl;
	//amer_option.toggle();
	//cout << "\namer_option put option price: " << amer_option.Price() << endl;
	//amer_option.toggle();
	//
	//cout << "\neuro_option call option price: " << euro_option.Delta() << endl;
	//euro_option.toggle();
	//cout << "\neuro_option put option price: " << euro_option.Delta() << endl;
	//euro_option.toggle();

	//AmericanOption* ptr_am = &amer_option;
	//cout << endl;
	//ptr_am->Print();

	//EuropeanOption* ptr_eu = &euro_option;
	//cout << endl;
	//ptr_eu->Print();

	//// euro pointer to amer option
	//EuropeanOption* ptr_eu_am = &amer_option;
	//cout << endl;
	//ptr_eu_am->Price();

	//// functors
	//vector<string> fn_name {"Delta", "Gamma", "Price" };
	//map<string, EuroMemFn> fn_name_ptr{ {"Price", &EuropeanOption::Price},
	//	{"Delta", &EuropeanOption::Delta}, {"Gamma", &EuropeanOption::Gamma} };

	////typedef void (EuropeanOption::* EuroSetFn)(double);
	//map<string, EuroSetFn> fn_set_ptr 
	//{ {"SetS", &EuropeanOption::SetS}, {"SetK", &EuropeanOption::SetK}, {"SetT", &EuropeanOption::SetT},
	//	{"SetR", &EuropeanOption::SetR}, {"SetSig", &EuropeanOption::SetSig}, {"SetB", &EuropeanOption::SetB},
	//};

	//cout << "\neuro_option.Price(), S = 110: " << std::invoke(fn_name_ptr["Price"], euro_option, 110);

	//std::invoke(fn_set_ptr["SetS"], euro_option, 150);

	//cout << endl << endl;
	//cout << "euro_option with setS(150):\n";
	//euro_option.Print();

	//cout << endl << endl;

	//// typedef double (EuropeanOption::* EuroMemFn)(double) const;		// for EuropeanOption
	////typedef double (AmericanOption::* AmerMemFn)(double) const;		// for AmericanOption
	////double (AmericanOption::* EurotoAmerFn)(double) const = &AmericanOption::Price;		// for AmericanOption

	////map<string, EuroSetFn> fn_name_ptr{ {"Price", &EuropeanOption::Price},
	//	//{"Delta", &EuropeanOption::Delta}, {"Gamma", &EuropeanOption::Gamma} };

	////void (EuropeanOption::* EuroSetFn)(double) = &EuropeanOption::SetS;		// for AmericanOption




	//map<string, vector<double>> option_measures;
	//// get prices for a monotonically increasing range of S values
	//prices_fn(amer_option, option_measures, fn_name_ptr[fn_name[2]], fn_name[2], test_param, 
	//	param_start, param_end, step_size);
	//
	//for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
	//	{
	//		if (option_type == "C")
	//		{
	//			cout << "\nCall option measure " << it->first << endl;
	//				for (auto price : it->second)
	//				cout << "\t" << price << endl;
	//		}
	//		else
	//		{
	//			cout << "\nPut option measure " << it->first << endl;
	//			for (auto price : it->second)
	//				cout << "\t" << price << endl;
	//		}
	//	}

	//// get deltas, gammas, and prices for monotonically increasing S
	//option_measures.clear();	// clear out map
	//// loop over the string vector of member function names and call prices_fn for each function
	//for (auto name : fn_name)
	//{
	//	// get values for delta for a monotonically increasing range of S values
	//	prices_fn(amer_option, option_measures, fn_name_ptr[name], name, test_param, param_start, 
	//		param_end, step_size);
	//}
	//

	//// display deltas, gammas, and prices for range of S
	//cout << "\nTest parameter:\t" << test_param
	//	<< "\nRange start:\t" << param_start
	//	<< "\nRange end:\t" << param_end
	//	<< "\nStep size:\t" << step_size
	//	<< "\nOption type:\t" << option_type << endl;

	//for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
	//{
	//	if (option_type == "C")
	//	{
	//		cout << "\nCall option measure " << it->first << endl;
	//		for (auto price : it->second)
	//			cout << "\t" << price << endl;
	//	}
	//	else
	//	{
	//		cout << "\nPut option measure " << it->first << endl;
	//		for (auto price : it->second)
	//			cout << "\t" << price << endl;
	//	}
	//}



	// typedef double (EuropeanOption::* EuroMemFn)(double) const;		// for EuropeanOption
	//typedef double (AmericanOption::* AmerMemFn)(double) const;		// for AmericanOption
	//double (AmericanOption::* EurotoAmerFn)(double) const = &EuropeanOption::Price;		// for AmericanOption

	//vector_pricer(test_params_map, option_prices, test_param, param_end, step_size,
			//option_type, underlying_security);
	//prices(amer_option, option_prices, test_param, param_start, param_end, step_size);

	// display elements of prices vector
	//for (auto it = option_prices.begin(); it != option_prices.end(); ++it)
	//{
		//if (option_type == "C") cout << "American call option prices: " << (*it) << endl;
		//else cout << "American put option prices: " << (*it) << endl;
	//}

	//cout << endl << endl;



	cout << endl << endl;



	cout << endl << endl;

	

	return 0;
}
