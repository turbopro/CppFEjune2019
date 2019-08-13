/* ExactPricingMethods.cpp

Implementation file for ExactPricingMethods.h header file

All functions declared in the header files are defined hereunder

set_batch():	set batch values from option_param and option_param_val vectors 

vec_range():	create vector of doubles: increasing/decreasing monotonically

vector_pricer():
Takes as input a map<string, double> of test parameters and a vector<double> to store
calculated call and put option prices
A test parameter is monotonically increased while other test parameters are held constant
For each step, the call or put price is calculated and stored in the vector<double>

matrix_pricer():
Takes as input a map<string, map<string, double>> of test parameters and a vector<double>
to store calculated call and put option prices
We loop through the map and call the vector_pricer() function that calculates and stores
the prices in the vector<double>

vector_pricer_by_fn():
// Takes as input a map<string, double> of test parameters and a vector<double> to store
// calculated call and put option prices, or, various greeks' measures like Deltas and
// Gammas
// A test parameter is monotonically increased while other test parameters are held constant
// For each step, the relevant member function, Price(), Gamma(), or Delta() is calculated,
// and stored in the vector<double>

matrix_pricer_by_fn():
Takes as input a map<string, map<string, double>> of test parameters and a
map<string, vector<double>> to store calculated call and put option prices with a string
identifier
The map<string, map<string, double> container includes the parameter to be tested, the
list of other parameters that are held constant, and the step size and end value of the
test parameter
The vector_pricer_by_fn() function is called to calculate and store the values/prices
in a vector

*/

#include "EuropeanOption.h"
#include "EuropeanOptionException.h"
//#include "Option.h"
#include "ExactPricingMethods.h"


// set_batch() definition
// set batch values from option_param and option_param_val vectors 
void set_batch(map<string, double>& batch, const vector<string>& option_param,
	const vector<double>& option_param_val)
{
	for (unsigned int i = 0; i < option_param_val.size(); i++)
	{
		batch[option_param[i]] = option_param_val[i];
	}
}


// create vector of doubles: increasing/decreasing monotonically
//vector<double> vec_range(const double& start, const double& end, const int& length)
void vec_range(vector<double>& vec, const double& start, const double& end)
{
	// create a vector of length num
	size_t sz = vec.size();

	// now assign the values to the vector
	for (size_t i = 0; i < sz; i++)
	{
		vec[i] = start + i * ((end - start) / sz);
	}
	//return vec;
}

// vector_pricer()
// Takes as input a map<string, double> of test parameters and a vector<double> to store
// calculated call and put option prices
// A test parameter is monotonically increased while other test parameters are held constant
// For each step, the call or put price is calculated and stored in the vector<double>
//
// Argument list:
// test_params	-	a map<string, double> that contains the option test parameters
// prices		-	a vector of double to store calculated prices
// test_param	-	a string that holds the test parameter's string
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// option_type	-	a string that holds the type of option, "C" = call or "P" = put
// underlying	-	a string that holds the type of underlying security/asset
// b_adjust		-	a double that holds the cost of carry adjustment
//
// Loop over the test parameter from start to end value in step_size steps:
//	For each iteration
//	  Set test_param to the current test value
//	  Get option price from an anonymous EuropeanOption object
//	  Add to output vector  
void vector_pricer(map<string, double>& test_params, vector<double>& prices,
	const string test_param, const double& param_end, const double& step_size,
	const string option_type, const string underlying, const double& b_adjust)
{
	for (double param_idx = test_params.at(test_param); param_idx <= param_end; param_idx += step_size)
	{
		test_params[test_param] = param_idx;
		prices.push_back(EuropeanOption(test_params, option_type, underlying, b_adjust).Price());
	}
}

// matrix_pricer()
// Takes as input a map<string, map<string, double>> of test parameters and a vector<double>
// to store calculated call and put option prices
// We loop through the map and call the vector_pricer() function that calculates and stores
// the prices in the vector<double>
//
// Agument list:
// price_matrix	-	a vector of map<string, map<string, double>> that contains the option
//					test parameters
// prices		-	a vector<double> to store calculated Call or Put option prices
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
// b_adjust		-	a double that holds the cost of carry adjustment
//
// Loop over the test_params map with an iterator
// Call vector_pricer() to calculate and store the option prices
// The map and vector are reference objects whose values are updated during 
// function execution
void matrix_pricer(map<string, map<string, double>>& price_matrix, vector<double>& prices,
	const string option_type, const string underlying, const double& b_adjust)
{
	for (auto it = price_matrix.begin(); it != price_matrix.end(); ++it)
	{
		vector_pricer(it->second, prices, it->first, it->second.at("param_end"),
			it->second.at("step_size"), option_type, underlying, b_adjust);
	}
}


// vector_pricer_by_fn() 
// Takes as input a map<string, double> of test parameters and a map<string, vector<double>>
// to store calculated call and put option prices, or, various greeks' measures like Deltas
// and Gammas
// A test parameter is monotonically increased while other test parameters are held constant
// For each step, the relevant member function, Price(), Gamma(), or Delta() is calculated,
// and stored in the map<string, vector<double>> with the name of the relevant member
// function
//
// Argument list:
// test_params	-	a map<string, double> that contains the option test parameters
// measures		-	a map<string, vector<double>> to store calculated prices/values
// test_param	-	a string that holds the test parameter's string
// param_end	-	a double that holds the value of the end value of the range of 
//					the test parameter
// step_size	-	a double that holds the step size for the test parameter
// fn_ptr		-	a EuropeanOption pointer to member function
//					(allows us to choose the requisite member function for testing)
// fn_name		-	a member function name
//					(to be used as a tag for the output vector of values)
// option_type	-	a string that holds the type of option, "C" = call or "P" = put
// underlying	-	a string that holds the type of underlying security/asset
// b_adjust		-	a double that holds the cost of carry adjustment
//
// option_type, underlying, and b_adjust default to "C" for call options, "Stock" for the
// underlying security/asset, and 0.0 for the adjustment for Stock, respectively
//
// Create a temporary vector of doubles to store calculated prices/values
// Loop over from the test parameter start to end value in step_size steps:
//	In each iteration
//		Get and store values/prices in measures_vec
//		We use std::invoke which takes as arguments the pointer to member function,
//		an anonymous EuropeanOption, and the current test parameter value(the
//		argument to the member function) 
// Add the member function name and vector of calculated prices/values to the prices map
void vector_pricer_by_fn(const map<string, double>& test_params, map<string, vector<double>>& measures,
	const string test_param, const double& param_end, const double& step_size,
	const EuroMemFn fn_ptr, const string fn_name,
	const string option_type, const string underlying, const double& b_adjust)
{
	// Temporary vector for prices/values
	vector<double> measures_vec;

	// Set indexer to the test parameter start value
	// Increment the indexer (test parameter substitute) by step_size
	// Use std::invoke to get value/price from anonymous EuropeanOption object that
	// calls the relevant member function, which takes the indexer as its argument 
	for (double param_idx = test_params.at(test_param); param_idx <= param_end; param_idx += step_size)
	{
		measures_vec.push_back(
			std::invoke(
				fn_ptr,							// pointer to member function 
				EuropeanOption(test_params, option_type, underlying, b_adjust),	// anon EuropeanOption
				param_idx));					// member function argument
	}

	// assign member funtion name and vector of computed prices/values to measure map
	measures[fn_name] = measures_vec;
}

// matrix_pricer_by_fn()
// Takes as input a map<string, map<string, double>> of test parameters and a
// map<string, vector<double>> to store calculated call and put option prices with a string
// identifier
// The map<string, map<string, double> container includes the parameter to be tested as the
// string, with the list of other parameters that are held constant, along with the end 
// value and step size contained in the map<string, double>
// The vector_pricer_by_fn() function is called to calculate and store the values/prices
// in a vector
//
// Argument list:
// price_matrix	-	a map<string, map<string, double>> that contains the option test parameters
// measures		-	a map<string, vector<double>> to store calculated Call or Put option prices
//					in a vector with a string identifier
// fn_ptr		-	a EuropeanOption pointer to member function
//					(allows us to choose the requisite member function for testing)
// fn_name		-	a member function name
//					(to be used as a tag for the output vector of values)
// option_type	-	a string that holds the type of option, "C" = call or "P" = put, 
//					to be calculated
// underlying	-	a string that holds the type of underlying security
// b_adjust		-	a double that holds the cost of carry adjustment
void matrix_pricer_by_fn(
	map<string, map<string, double>>& price_matrix, map<string, vector<double>>& measures,
	const EuroMemFn fn_ptr, const string fn_name, const string option_type,
	const string underlying, const double& b_adjust)
{
	for (auto it = price_matrix.begin(); it != price_matrix.end(); ++it)
	{
		vector_pricer_by_fn(it->second, measures, it->first, it->second.at("param_end"),
			it->second.at("step_size"), fn_ptr, fn_name, option_type, underlying, b_adjust);
	}
}


// testing ****************************
/*
// testing ****************************
// WORKING
// does part A, EuroOption basics
// prices()
void prices(EuropeanOption option, vector<double>& option_prices,
	string test_param, double param_start, double param_end, double step)
{

	for (double param_idx = param_start; param_idx <= param_end; param_idx += step)
	{
		if (test_param == "S") option.SetS(param_idx);
		else if (test_param == "K") option.SetK(param_idx);
		else if (test_param == "T") option.SetT(param_idx);
		else if (test_param == "r") option.SetR(param_idx);
		else if (test_param == "sig") option.SetSig(param_idx);
		else option.SetB(param_idx);

		option_prices.push_back(option.Price());
	}
}


// testing ****************************
// WORKING
// does part A, EuroOption basics
// prices()
//template <typename T>
void prices(EuropeanOption& option, vector<double>& option_prices,
	const string test_param, const double param_start,
	const double param_end, const double step)
{
	// make local copy of option for setting parameter values
	//EuropeanOption local_option(option);
	for (double param_idx = param_start; param_idx <= param_end; param_idx += step)
	{
		if (test_param == "S") option.SetS(param_idx);
		else if (test_param == "K") option.SetK(param_idx);
		else if (test_param == "T") option.SetT(param_idx);
		else if (test_param == "r") option.SetR(param_idx);
		else if (test_param == "sig") option.SetSig(param_idx);
		else option.SetB(param_idx);

		//option_prices.push_back(option.Price());
		option_prices.push_back(option.Price());
	}
}



*/


// testing ****************************
// WORKING
// does part A, EuroOption basics
// prices()
//template <typename T>
void prices(EuropeanOption& option, vector<double>& option_prices, 
	const string test_param, const double param_start, 
	const double param_end, const double step)
{
	// make local copy of option for setting parameter values
	//EuropeanOption local_option(option);
	for (double param_idx = param_start; param_idx <= param_end; param_idx += step)
	{
		if (test_param == "S") option.SetS(param_idx);
		else if (test_param == "K") option.SetK(param_idx);
		else if (test_param == "T") option.SetT(param_idx);
		else if (test_param == "r") option.SetR(param_idx);
		else if (test_param == "sig") option.SetSig(param_idx);
		else option.SetB(param_idx);

		//option_prices.push_back(option.Price());
		option_prices.push_back(option.Price());
	}
}



// testing ****************************
// WORKING
// does part A, EuroOption basics
// prices_setfn()
void prices_setfn(EuropeanOption& option, vector<double>& option_prices,
	EuroSetFn p_setter_fn, const vector<double>& param_vec)
{
	for (double param_idx = param_vec[1]; param_idx <= param_vec[2]; param_idx += param_vec[3])
	{
		std::invoke(p_setter_fn, option, param_idx);		// set option test parameter
		option_prices.push_back(option.Price());		// get option price
	}
	std::invoke(p_setter_fn, option, param_vec[0]);		// reset test parameter
}


// testing ****************************
// WORKING
// does part A, EuroOption basics
// price_set_by_fn()
void pricer_set_by_fn(EuropeanOption& option, vector<double>& option_prices,
	const EuroSetFn p_setter_fn, const EuroPriceFn p_price_fn, const vector<double>& param_vec)
{
	for (double param_idx = param_vec[1]; param_idx <= param_vec[2]; param_idx += param_vec[3])
	{
		std::invoke(p_setter_fn, option, param_idx);		// set option test parameter
		option_prices.push_back(							// get option price
			std::invoke(p_price_fn, option, option.GetS()));		
	}
	std::invoke(p_setter_fn, option, param_vec[0]);			// reset test parameter
}


// testing ****************************
// not yet WORKING
// does part A, EuroOption basics
// matrix_pricer_by_fn()
void matrix_pricer_by_fn0(EuropeanOption& option, map<string, vector<double>>& params,
	map<string, vector<double>>& prices_map, EuroPriceFn p_pricer_fn, 
	map <string, EuroSetFn> p_setter_fn, string fn_name)
{
	for (auto it = params.begin(); it != params.end(); ++it)
		pricer_set_by_fn(option, prices_map[it->first], p_setter_fn[it->first], 
			p_pricer_fn, it->second);
}






// testing ****************************
// WORKING
// does part A, EuroOption basics
// m_prices()
void m_prices(EuropeanOption option, map<string, vector<double>>& params,
	map<string, vector<double>>& prices_map)
{
	for (auto it = params.begin(); it != params.end(); ++it)
		prices(option, prices_map[it->first], it->first, it->second[0], it->second[1], it->second[2]);
}

// testing ****************************
// WORKING
// does part A, EuroOption basics
// prices_fn()
void prices_fn(EuropeanOption& option, map<string, vector<double>>& prices_map, EuroMemFn fn_ptr,
	string fn_name, string test_param, double param_start, double param_end, double step)
{
	// store value of test param
	double test_param_temp;

	// combine funtion name and test parameter
	string fn_param = fn_name + " for " + test_param;

	// lopp over parameter range by size step; set parameter; create option; get price/value;
	// update output map
	for (double param_idx = param_start; param_idx <= param_end; param_idx += step)
	{
		if (test_param == "S") option.SetS(param_idx);
		else if (test_param == "K") option.SetK(param_idx);
		else if (test_param == "T") option.SetT(param_idx);
		else if (test_param == "r") option.SetR(param_idx);
		else if (test_param == "sig") option.SetSig(param_idx);
		else option.SetB(param_idx);

		prices_map[fn_param].push_back(std::invoke(fn_ptr, option, option.GetS()));
	}
	//option.Se
}


// testing ****************************
// -- not yet WORKING
// does part A, EuroOption basics
// m_prices_fn()
void m_prices_fn(EuropeanOption option, map<string, vector<double>>& params,
	map<string, vector<double>>& prices_map, EuroMemFn fn_ptr, string fn_name)
{
	for (auto it = params.begin(); it != params.end(); ++it)
		prices_fn(option, prices_map, fn_ptr, fn_name, 
		it->first, it->second[0], it->second[1], it->second[2]);
}




/*
// v_pricer()
//vector<double> v_pricer(vector<EuropeanOption>& test_option)
void v_pricer(vector<EuropeanOption>& test_option, vector<double>& prices)
{
	//vector<double> option_prices;
	for (auto it = test_option.begin(); it != test_option.end(); ++it)
		prices.push_back(it->Price());

	//return option_prices;
}

// vector<double>& option_prices,



*/


// display prices and/or measures
void display_measures(map<string, vector<double>> option_measures, string option_type)
{
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


void display_measures(vector<double> option_measures)
{
	for (auto measure : option_measures)
		cout << "\npotion values/prices are:\n" << measure << endl;
}