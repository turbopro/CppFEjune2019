/* ExactPricingMethods.cpp

Implementation file for ExactPricingMethods.h header file

All functions declared in the header files are defined hereunder

set_batch():	set batch values from option_param and option_param_val vectors 

vec_range():	create vector of doubles: increasing/decreasing monotonically

vector_pricer():	(4-argument version)
Takes as input an option, a vector of doubles to store calculated prices, a function
pointer to member setter functions, and a vector of doubles with input values for 
the test parameter
A test parameter is monotonically increased while other test parameters are held constant
For each step, the call or put price is calculated and stored in the vector<double>

vector_pricer():	(5-argument version)
Takes an additional function pointer to member functions (Price, Gamma, Delta) 
argument

matrix_pricer():
Takes as input a map<string, map<string, double>> of test parameters and a
map<string, vector<double>> to store calculated call and put option prices with a string
identifier
The map<string, map<string, double> container includes the parameter to be tested, the
list of other parameters that are held constant, and, the inital value, the start, the end
value and step size of the test parameter
The relevant vector_pricer() function is called to calculate and store the values/prices
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
}



// vector_pricer()
// Set an indexer to the test parameter's start value, then loop until the end vlue by step size
// For each loop:
//	set the test parameter of the option
//	call the Price() function
//	add the returned c\value to the output vector
//	after the loop completes, reset the test parameter to its inital value
void vector_pricer(EuropeanOption& option, vector<double>& option_prices,
	const EuroSetFn p_setter_fn, const vector<double>& param_vec)
{
	for (double param_idx = param_vec[1]; param_idx <= param_vec[2]; param_idx += param_vec[3])
	{
		std::invoke(p_setter_fn, option, param_idx);		// set option test parameter
		option_prices.push_back(option.Price());		// get option price
	}
	std::invoke(p_setter_fn, option, param_vec[0]);		// reset test parameter
}


// vector_pricer()
// Set an indexer to the test parameter's start value, then loop until the end vlue by step size
// For each loop:
//	set the test parameter of the option
//	call the relevant member function, Delta, Gamma, Price, given by the p_price_fn pointer 
//	add the returned c\value to the output vector
//	after the loop completes, reset the test parameter to its inital value
void vector_pricer(EuropeanOption& option, vector<double>& option_prices,
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


// matrix_pricer()
void matrix_pricer(EuropeanOption& option, const map<string, vector<double>>& params,
	map<string, vector<double>>& option_prices_map, const map <string, EuroSetFn> p_setter_fn)
{
	for (auto it = params.begin(); it != params.end(); ++it)
		vector_pricer(option, option_prices_map[it->first], p_setter_fn.at(it->first),
			it->second);
}


// matrix_pricer()
void matrix_pricer(EuropeanOption& option, const map<string, vector<double>>& params,
	map<string, vector<double>>& prices_map, const EuroPriceFn p_pricer_fn, 
	const map<string, EuroSetFn> p_setter_fn)
{
	for (auto it = params.begin(); it != params.end(); ++it)
		vector_pricer(option, prices_map[it->first], p_setter_fn.at(it->first), 
			p_pricer_fn, it->second);
}


// display prices and/or measures
void display_measures(map<string, vector<double>> option_measures, string option_type)
{
	for (auto it = option_measures.begin(); it != option_measures.end(); ++it)
	{
		if (option_type == "C")
		{
			cout << "\nCall option measure for range of " << it->first << " values are:\n";
			for (auto val : it->second) cout << val << endl;
		}
		else
		{
			cout << "\nPut option measure for range of " << it->first << " values are:\n";
			for (auto val : it->second) cout << val << endl;
		}
	}
}


void display_measures(vector<double> option_measures, string option_type)
{
	cout << "option prices are:\n";
	for (auto measure : option_measures) cout << measure << endl;
}


