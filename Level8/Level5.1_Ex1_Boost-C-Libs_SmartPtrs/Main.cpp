/* Main.cpp
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

Test program for the STL -- built upon the previous work done thus far

 STL tests as follows:
  Containers
· Create a list of doubles and add some data.
· Use the front() and back() functions to access the first and last element.
· Create a vector of doubles and add some data. Then use the index operator 
  to access some elements. Also make the vector grow.
· Create a map that maps strings to doubles. Fill the map and access 
  elements using the square bracket operator.

  Iterators

  Using iterators you can iterate a STL container without knowing which 
  container it is. In this exercise you create a function that calculates 
  the sum of a container with doubles.

· Create a template function called Sum() that accepts the template
  argument T as input and returns a double. The template argument will 
  be a container.
· In the implementation get an iterator (T::const_iterator) for the end.
· Then create a loop that iterates the container T and adds all values. 
· Finally return the sum.
· In the main program, call the Sum() function for the different container 
  from the previous exercise.

The overloaded Sum() function created calculates the sum of the complete container.

Additionally, create a Sum() function that calculates the sum of all values 
between two passed-in iterators. The function should use the template 
argument for the iterator type and accept two iterators, the 'start' - 
and 'end' iterator. The summation should include the value pointed to by 
the start iterator and exclude the value pointed to by the end iterator.

STL already contains many algorithms that work with containers. Use the count_if 
algorithm to count the number of elements smaller than a certain number. The 
count_if function accepts a functor. Thus pass it a global function that checks 
the double input is smaller than a certain value.

Replace the global checking function, by a function object. This is a class that 
overload the round bracket operator that in this case has the same signature and 
functionality as the global function you created previously. Only in this case 
the value to check for should not be a ‘literal’ value, but taken from a data 
member that was set in the constructor of the function object.

*/

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <typeinfo>
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
#include <list>				// for map
#include <map>				// for list
#include <iterator>			// for iter
#include <algorithm>		// for count_if
#include <numeric>			// std::accumulate
#include "STLHelperFunctions.h"	// STL helper functions
#include <boost/shared_ptr.hpp>	// Boost C Library Shared Pointer header file

using namespace std;

// declaration for user_input_geom() function
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);

// declaration for user_input_array() function
bool user_input_array(unsigned int& array_size);


// template functions -- generic for List, Vector
// Sum() definition for List and Vector, with container as argument
// pass by reference for containers
template <typename T>
double Sum(const T& container);

// Sum() definition for List and Vector, with iterator range argument
// pass by value for iterators
template <typename T>
double Sum(const typename T start_it, const typename T end_it);

// template explicit specialisation for Map
// Sum() definition for Map with container as argument
template <>
double Sum(const map<string, double>& container);

// template explicit specialisation for Map
// Sum() definition for Map with iterator range as argument
template <>
double Sum(map<string, double>::const_iterator start_it, map<string, double>::const_iterator end_it);


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
		<< "|               SmartPtrs                |\n"
		<< "|========================================|\n";


	// Typedef for a shared pointer to shape and
	// a typedef for an array with shapes stored as shared pointers.
	typedef boost::shared_ptr<Point> PointPtr;
	typedef Array<PointPtr> ptArray;

	ptArray sptr_parr0(5);
	
	cout << "size of sptr_parr0: " << sptr_parr0.Size() << endl;
	cout << "type of sptr_parr0: " << typeid(sptr_parr0).name() << endl
		<< "sptr_parr0[0]: " << typeid(sptr_parr0[0]).name() << endl << endl;
	
	cout << "\nset sptr_parr0[0] values: ";
	sptr_parr0[0]->Print();
	//sptr_parr0[0]->Y(5);
		
	//cout << "\n\nsptr_parr0[0]: " << sptr_parr0[0]->ToString() << endl << endl;	

	/*
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|       STL: List, Vector, and Map       |\n"
		<< "|========================================|\n";

	// list:
	cout << "Create list of doubles: my_grades\n";
	list<double> my_grades = { 96, 92, 92, 95, 95, 80 };
	//print my_grades: use range-based for loop
	cout << "\nmy_grades:\n";
	for (auto grade : my_grades) { cout << grade << endl; }

	// print week 1 grade
	cout << "\nWeek1 grade: " << my_grades.front() << endl;

	// print last week's grade
	cout << "\nMost recent week's grade: " << my_grades.back() << endl;

	// total of scores
	cout << "\ntotal of all scores: "
		<< std::accumulate(my_grades.begin(), my_grades.end(), 0) << endl;

	// mean of scores
	cout << "\nAverage of all scores: "
		<< fixed << setprecision(2)			// output format to two decimal places
		<< (std::accumulate(my_grades.begin(), my_grades.end(), 0.0)) / my_grades.size() << endl;

	// vector:
	// create vector of doubles
	cout << "\n\nCreate empty vector to hold doubles, v_grades\n";
	int vec_sz = 10;
	vector<double> v_grades;

	// insert pseudo-random values into v_grades
	cout << "\nPopulate v_grades with pseudo-random values\n";
	for (int i = 0; i < vec_sz; i++)
	{
		v_grades.emplace(v_grades.begin(), (rand() % 100));
	}

	// print vector
	cout << "\nv_grades has:\n";
	for (auto grade : v_grades) { cout << grade << endl; }

	// use indexing operator to display values in a range
	cout << "\nv_grades in the range from 3rd to 7th elements:\n";
	for (int lower = 2, upper = 7; lower < upper; lower++)
		cout << v_grades[lower] << endl;

	// create vector of Points
	vector<Point> vpt0;

	// create PointArray, set Points to psuedo-random values 
	cout << "\n\nCreate PointArray and set values\n";
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
	cout << "\n\nSet ostream_iterator to print vector info\n";
	// create iterator output object 
	ostream_iterator<Point, char> out_iter(cout, "\n");

	cout << "\nvpt0 via ostream_iterator output object has:\n";
	copy(vpt0.begin(), vpt0.end(), out_iter);

	// resize vector: double its size
	cout << "\n\nDouble the size of vpt0\n";
	vpt0.resize(6);

	// print vpt0 info
	cout << "\nvpt0 has:\n";
	for (auto pt : vpt0) cout << pt.ToString() << endl;

	cout << "\nvpt0 via iterator has:\n";
	copy(vpt0.begin(), vpt0.end(), out_iter);
	cout << endl;

	// map:
	// create array of strings for keys, array of doubles for data
	const string planets[] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
	double diameters[] = { 4878, 12104, 12756, 6794, 142984, 120536, 51118, 49532 };
	int map_sz = sizeof(planets) / sizeof(planets[0]);

	// create map of planets vs diameters (in Km)
	map<string, double> planet_diameters;

	// populate planet_diameters
	for (int i = 0; i < map_sz; i++)
		planet_diameters.emplace(planets[i], diameters[i]);

	// print planet_diameters
	// format for thousands separator = comma
	locale loc("");
	locale US = cout.imbue(loc);
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

	// print more values using indexing operator: key values used as indices
	cout << "\nThe gas giants have larger diameters:\n";
	for (int i = 4, gas_giants = 8; i < gas_giants; i++)
	{
		cout << planets[i] << ": " << planet_diameters[planets[i]] << " Km" << endl;
	}


	cout << "\n\n\n"
		<< "|========================================|\n"
		<< "|             STL: Iterators             |\n"
		<< "|========================================|\n";

	// calculate sum of container (List) elements using Sum() with container argument
	cout << "\nSum of my_grades (List: Sum() using container argument): "
		<< Sum(my_grades) << endl;

	// calculate sum of container (List) elements using Sum() with iterator arguments
	cout << "\nSum of my_grades (List: Sum() using iterator argument): "
		<< Sum(my_grades.begin(), my_grades.end()) << endl;

	// grow v_grades to include thousands of grades
	cout << "\nResize v_grades to 2000 elements\n";
	v_grades.resize(2000);

	// insert pseudo-random values into v_grades
	cout << "nPopulate v_grades with pseudo-random values\n";
	vec_sz = v_grades.size();
	for (int i = 0; i < vec_sz; i++)
	{
		v_grades.emplace(v_grades.begin(), ((rand() % 100) * 0.73));
	}

	// calculate sum of grades for v_grades (Vector) using Sum() with container argument
	cout << "\nSum of grades in v_grades (Vector: Sum() using container argument): "
		<< fixed << setprecision(2)			// display to two decimal places
		<< Sum(v_grades) << endl;

	// calculate sum of grades for v_grades (Vector) using Sum() with iterator arguments
	vector<double>::iterator it_begin = v_grades.begin();		// get start iterator
	vector<double>::iterator it_end = v_grades.end();			// get end iterator
	cout << "\nSum of grades in v_grades (Vector: Sum() using iterator arguments): "
		<< Sum(it_begin, it_end) << endl;

	// calculate sum of grades for first 200 elements of v_grades
	vector<double>::iterator it_rng_end = next(it_begin, 200);		// get end iterator for range
	cout << "\nSum of grades for first 200 elements from v_grades: "
		<< Sum(it_begin, it_rng_end) << endl;

	// calculate sum of grades for elements 200 thru 400 of v_grades
	vector<double>::iterator it_rng_start = next(it_begin, 199);	// get start iterator for range
	it_rng_end = next(it_begin, 400);								// get end iterator for range
	cout << "\nSum of grades for elements 200 thru 400 from v_grades: "
		<< Sum(it_rng_start, it_rng_end) << endl;

	cout.precision(0);						// reset display to zero decimal places
	// calculate sum of diameters for all planets (Map) using Sum() with container argument
	cout << "\nSum of diameters for all planets (Map: Sum() using container argument): "
		<< Sum(planet_diameters) << " Km" << endl;

	// calculate sum of diameters for all planets (Map) using Sum() with iterator arguments
	map<string, double>::const_iterator it_mbegin = planet_diameters.begin();	// get start iterator for range
	map<string, double>::const_iterator it_mend = planet_diameters.end();		// get end iterator for range

	cout << "\nSum of diameters for all planets (Map: Sum() using iterator arguments): "
		<< Sum<>(it_mbegin, it_mend) << " Km" << endl;

	// calculate sum of diameters for first four planets (listed alphabetically in planet_diameters)
	map<string, double>::const_iterator it_mrng_end = next(it_mbegin, 4);		// get end iterator for range

	cout << "\nSum of diameters for first four planets (alphabetically) in planet_diameters map\n"
		<< "(Map: Sum() using iterator arguments): " << Sum(it_mbegin, it_mrng_end) << " Km" << endl;


	cout << "\n\n\n"
		<< "|========================================|\n"
		<< "|            STL: Algorithms             |\n"
		<< "|========================================|\n";	

	// count the number of elements in v_grades < 35
	cout << "\nNumber of elements in v_grades (Vector) < 35: "
		<< count_if(v_grades.begin(), v_grades.end(), is_less_than) << endl;

	// count the number of elements in v_grades: use LessThan object
	cout << "\nNumber of elements in v_grades (Vector) < 35: using LessThan default object: "
		<< count_if(v_grades.begin(), v_grades.end(), LessThan()) << endl;

	// count the number of elements in v_grades: use LessThan object
	LessThan less_than(45);
	cout << "\nNumber of elements in v_grades (Vector) < " << less_than.GetThreshold()
		<< ": using LessThan constructed object: "
		<< count_if(v_grades.begin(), v_grades.end(), less_than) << endl;

	// count the number of elements in my_grades: use LessThan object
	less_than.SetThreshold(95);
	cout << "\nNumber of elements in my_grades (List) < " << less_than.GetThreshold()
		<< ": using LessThan constructed object: "
		<< count_if(my_grades.begin(), my_grades.end(), less_than) << endl << endl;
	
	*/

	return 0;
}

// template functions -- generic for List, Vector
// Sum() definition for List and Vector, with container as argument
template <typename T>
double Sum(const T& container)
{
	double acc_sum = 0;				// initialise accumulator

	// set const_iterator, it, to end()
	// decrement it, and check if == begin()
	// dereference it and add to the accumulator
	// repeat until the loop terminates
	//for (auto it = container.end(); it-- != container.begin(); )
	for (typename T::const_iterator it = container.end(); it-- != container.begin(); )
		acc_sum += *it;

	// alternative that takes care of setting correct iterator type, makes good use
	// of rbegin() and rend(), and no need for decrementing
	//for (auto it = container.rbegin(); it != container.rend(); it++)
	//	acc_sum += *it;

	return acc_sum;
}


// Sum() definition for List and Vector, with iterator range argument
// pass by value for iterators
template <typename T>
double Sum(const typename T start_it, const typename T end_it)
{
	double acc_sum = 0;			// initialise accumulator

	// set type T iterator, it, to start_it
	// dereference it and add to the accumulator
	// increment it
	// repeat until the loop terminates
	for (T it = start_it; it != end_it; it++)
		acc_sum += *it;

	return acc_sum;
}

// template explicit specialisation for Map
// Sum() definition for Map with container as argument
template <>
double Sum(const map<string, double>& container)
{
	double acc_sum = 0;				// initialise accumulator

	// set const_iterator, it, to end()
	// decrement it, and check if == begin()
	// dereference it and add to the accumulator
	// repeat until the loop terminates
	//for (auto it = container.end(); it-- != container.begin(); )
	for (map<string, double>::const_iterator it = container.end(); it-- != container.begin(); )
		acc_sum += it->second;

	return acc_sum;
}

// template explicit specialisation for Map
// Sum() definition for Map with iterator range as argument
template <>
double Sum(map<string, double>::const_iterator start_it, map<string, double>::const_iterator end_it)
{
	double acc_sum = 0;			// initialise accumulator

	// set specialisation type it, to start_it
	// use the it member access operator to access the map's double value
	// add the value to the accumulator
	// increment it
	// repeat until the loop terminates
	//for (auto it = start_it; it != end_it; it++)
	for (map<string, double>::const_iterator it = start_it; it != end_it; it++)
		acc_sum += it->second;

	return acc_sum;
}
