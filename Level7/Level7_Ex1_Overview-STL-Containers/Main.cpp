/* Main.cpp
Level7_Ex1: Overview of the Standard Template Library - STL Containers

Test program for the STL -- built upon the previous work done thus far

 STL tests as follows:
 · 
 · 
   : use a loop with an index multiplier to create Point object coordinates
 · 
 · 
   : get user input for the array size
   : use a loop with an index multiplier to create Point object coordinates
 · 
 · 
   : copy the constructor Array
 · 
 · 
 · 
 · 
 · 
 · 
 · 
 

*/

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <string>			// for string operations
#include <iomanip>			// set fixed and precision for cout/cin
#include <cmath>			// for PI
#include "Point.h"			// Point class declaration
#include "Line.h"			// Line class declaration
#include "Circle.h"			// Circle class declaration
#include "Array.h"			// Array class declaration
#include "Shape.h"			// Shape class declaration
#include "ArrayException.h"	// ArrayException class declaration
#include "NumericArray.h"	// NumericArray class declaration
#include "PointArray.h"		// PointArray class declaration
#include "Stack.h"			// Stack class declaration
#include "StackException.h"	// StackException class declaration

// STL
#include <vector>			// for vector, copy
#include <list>
#include <map>
#include <iterator>			// for iter
#include <algorithm>
#include <numeric>			// std::accumulate


using namespace std;

// declaration for user_input_geom() function
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);

// declaration for user_input_array() function
bool user_input_array(unsigned int& array_size);

// test vector output
template <typename T>
double Sum(const T container);

int main(void)
{
	using namespace Turbopro::Containers;		// namespace directive
	using namespace Turbopro::CAD;				// namespace directive
	using Turbopro::CAD::Line;					// namespace declaration
	namespace TCad = Turbopro::CAD;				// namespace alias


	const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	const string y_coord{ "y-coordinate" };
	const string  radius{ "radius" };

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values
	int arr_size{ 0 };					// array size should be positive only
	const int stack_size = 3;

	
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|       STL: List, Vector, and Map       |\n"
		<< "|========================================|\n\n";		

	// list:
	cout << "Create list of doubles: my_grades:\n";	
	list<double> my_grades = { 96, 92, 92, 95, 95, 80 };
	//print my_grades: use range-based for loop
	cout << "\nmy_grades:\n";
	for (auto grade : my_grades) { cout << grade << endl; }

	// print week 1 grade
	cout << "\nWeek1 grade: " << my_grades.front() << endl;

	// print last week's grade
	cout << "\nMost recent week's grade: " << my_grades.back() << endl;

	// total of scores
	cout << "\ntotal of all scores:\n";
	cout << std::accumulate(my_grades.begin(), my_grades.end(), 0) << endl;

	// mean of scores
	cout << "\nAverage of all scores:\n";
	cout << fixed << setprecision(2);			// output format to two decimal places
	cout << (std::accumulate(my_grades.begin(), my_grades.end(), 0.0)) / my_grades.size() << endl;

	// vector:
	// create vector of doubles
	cout << "\n\nCreate empty vector to hold doubles, v_grades:\n";
	int vec_sz = 10;
	vector<double> v_grades;

	// insert pseudo-random values into v_grades
	cout << "nPopulate v_grades with pseudo-random values:\n";
	//cout.setf(0, ios::floatfield);
	for (int i = 0; i < vec_sz; i++) 
	{ 
		v_grades.emplace(v_grades.begin(), (rand() % 100));
	}

	// print vector
	cout << "\nv_grades has:\n";
	for (auto grade : v_grades) { cout << grade << endl; }

	// use indexing operator to display values in a range
	cout << "\nv_grades in the range from 3rd to 7th elements:\n";
	for (int i = 2; i < 7; i++) { cout << v_grades[i] << endl; }

	// create vector of Points
	vector<Point> vpt0;
	
	// create PointArray, set Points to psuedo-random values 
	cout << "\nCreate PointArray and set values:\n";
	PointArray parr0(stack_size);
	for (int i = 0; i < stack_size; i++)
	{
		parr0[i] = Point{ 0.5 * (rand() % 10), 1.15 * (rand() % 10) };
	}

	// copy parr0 Points to vpt0
	cout << "\nCopy parr0 Points to vpt0\n";
	vpt0.resize(stack_size);
	copy(&parr0[0], (&parr0[0] + stack_size), vpt0.begin());

	// print vpt0 info
	cout << "\nvpt0 has:\n";
	for (auto pt : vpt0) cout << pt.ToString() << endl;

	// set ostream iterator to print vector info to cout
	cout << "\n\nSet ostream_iterator to print vector info:\n";
	// create iterator output object 
	ostream_iterator<Point, char> out_iter(cout, "\n");

	cout << "\nvpt0 via iterator output object has:\n";
	copy(vpt0.begin(), vpt0.end(), out_iter);

	// resize vector: double its size
	cout << "\nDouble the size of vpt0:\n";
	vpt0.resize(6);

	// print vpt0 info
	cout << "\nvpt0 has:\n";
	for (auto pt : vpt0) cout << pt.ToString() << endl;

	cout << "\nvpt0 via iterator has:\n";
	copy(vpt0.begin(), vpt0.end(), out_iter);
	cout << endl;

	cout << endl;

	// map:
	// create strings for keys, doubles for data
	string planets[] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
	double diameters[] = { 4878, 12104, 12756, 6794, 142984, 120536, 51118, 49532 };
	int ss_size = sizeof(planets) / sizeof(planets[0]);

	// create map of planets vs diameters (in Km)
	map<string, double> planet_diameters;

	// populate planet_diameters
	for (int i = 0; i < ss_size; i++)
		planet_diameters.emplace(planets[i], diameters[i]);

	// print planet_diameters
	// format for comma thousands separator
	locale loc("");
	cout.imbue(loc);
	cout.precision(0);

	cout << "\nMap of planets (listed alphabetically) vs their respective diameters (Km):\n"
		<< "-------------------------------------------------\n" 
		<< "|\tPLANET\t\t|\tDIAMETER (KM)\t|\n" 
		<< "-------------------------------------------------\n";
	for (auto planet : planet_diameters) 
	{ 
		cout << "|\t" << planet.first << "\t\t|\t" << planet.second << "\t\t|" << endl; 
	}
	cout << "-------------------------------------------------\n";

	// print values using indexing operator: key values used as indices
	cout << "\nThe first four inner rocky planets tend to be smaller in diameter:\n";
	for (int i = 0, rocky_planets = 4; i < rocky_planets; i++)
	{
		cout << planets[i] << ": " << planet_diameters[planets[i]] << " Km" << endl;
	}

	cout << endl;

	cout << "\nSum of my_grades: " << Sum(my_grades) << endl;

	cout << endl;

	return 0;
}

// Sum() definition
template <typename T>
double Sum(const T container)
{
	T::const_iterator iter_ele;			// set end iterator
	//iter_end = container.end();
	//T::iterator iter_ele;				// set iterator
	double acc_sum = 0;					// initialise accumulator

	for (iter_ele = container.begin(); iter_ele != container.end(); iter_ele++)
		acc_sum += *iter_ele;

	return acc_sum;
}