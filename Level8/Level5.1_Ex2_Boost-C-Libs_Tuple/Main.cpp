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

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators

using namespace std;
using boost::tuple;

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


// print a simple message
void message(const char* s) { cout << s << endl; }
void message(const char* s, const int n) { cout << s << ": " << n << endl; }

// print tuple declaration
// create typedef for Person tuple with name, age, and height
typedef boost::tuple<string, int, float> Person;
void print_tuple(const Person& P);


int main(void)
{
	using namespace Turbopro::Containers;		// namespace directive
	using namespace Turbopro::CAD;				// namespace directive
	using Turbopro::CAD::Line;					// namespace declaration
	namespace TCad = Turbopro::CAD;				// namespace alias


	//const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	//const string y_coord{ "y-coordinate" };
	//const string  radius{ "radius" };

	//double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values
	const int arr_size{ 5 };					// array size should be positive only
	//const int stack_size = 3;


	cout << "\n\n"
		<< "|========================================|\n"
		<< "|                 TUPLE                  |\n"
		<< "|========================================|\n";

	// create Person
	cout << "\nCreate and print your average Jane Doe Person:\n";
	Person JaneDoe(string("Jane Doe"), 24, 1.65);
	print_tuple(JaneDoe);

	// create an array of Persons
	cout << "\nsetup an arrays of names (strings), ages (ints), and heights (floats):\n";
	string  names[] = { "Dorothy", "Hal", "Dave", "Lucy", "Mindy" };
	int      ages[] = { 11, 2, 36, 35, 28 };
	float heights[] = { 1.45, 2.25, 1.78, 1.65, 1.67 };
	Array<Person> peeps(arr_size);
	for (int i = 0; i < peeps.Size(); i++)
	{
		peeps[i].get<0>() = names[i];
		peeps[i].get<1>() = ages[i];
		peeps[i].get<2>() = heights[i];
	}

	// print peeps
	cout << "\nPerson array, peeps, has:\n\n";
	for (int i = 0; i < peeps.Size(); i++)
	{
		print_tuple(peeps[i]);
	}


	// change the name of Lucy to Lucille and Mindy's age to 27
	cout << "\n\nChange peeps[3] name to 'Lucille', and peeps[4] age to 27:\n\n";
	peeps[3].get<0>() = "Lucille";
	peeps[4].get<1>() = 27;
	cout << "Updated peeps[3] has "; print_tuple(peeps[3]);
	cout << "Updated peeps[4] has "; print_tuple(peeps[4]);

	cout << endl;

	/*
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|      shared_ptr and Shape objects      |\n"
		<< "|========================================|\n";


	// Typedef for a shared pointer to shape and
	// a typedef for an array with shapes stored as shared pointers.
	typedef boost::shared_ptr<Shape> ShapePtr;
	typedef Array<ShapePtr> ShapeArray;

	// the below code runs in a try block to create Shape objects via shared_ptrs
	// at the end of the block, we observe the Shape objects, dynamically allocated
	// using shared_ptrs, destructing automagically
	// any Array exceptions should be caught
	try
	{
		// create array of shared pointers to Shape objects
		cout << "\nInside first block:\n\n"
			<< "\nCreate array of shared_ptrs to Shape objects:\n";
		ShapeArray sptr_arr0(arr_size);

		cout << "\nSize of sptr_arr0: " << sptr_arr0.Size() << endl
			<< "Type of sptr_arr0: " << typeid(sptr_arr0).name() << endl
			<< "sptr_arr0[0]: " << typeid(sptr_arr0[0]).name() << endl
			<< "sptr_arr0[0] use_count: " << sptr_arr0[0].use_count() << endl << endl;
		
		// set shared_ptr, ShapePtr, to new dynamically allocated Shape objects
		cout << "\nSet ShapePtr shared_ptrs to new Shape objects:\n";
		sptr_arr0[0] = ShapePtr(new Point(rand() % 10, rand() % 20));
		sptr_arr0[1] = ShapePtr((new Line(Point(rand() % 30, rand() % 10),
			Point(rand() % 50, rand() % 25))));
		sptr_arr0[2] = ShapePtr((new Circle((rand() % 10 * 1.58),
			Point(rand() % 40, rand() % 55))));
		sptr_arr0[2].reset(new Circle((rand() % 10 * 1.58),		// reassign shared_ptr
			Point(rand() % 40, rand() % 55)));
		sptr_arr0[1].reset(new Line(Point(rand() % 30, rand() % 10),	// reassign shared_ptr
			Point(rand() % 50, rand() % 25)));

		// print Shapes
		cout << "\nsptr_arr0 has Shapes:\n";
		for (int i = 0; i < sptr_arr0.Size(); i++)
			sptr_arr0[i]->Print();		

		cout << "\n\nLeaving block\n"
			<< "\nArrays (with built-in destructors) and Shape objects dynamically\n"
			<< "allocated by smart_ptrs will self destruct now:\n\n";
	}
	catch (ArrayException& error_msg) {	cout << error_msg.GetMessage() << endl;	}
	catch (...) { cout << "Unknown exception caught\n" << endl; }

	cout << "\n\n\nmain() terminating... " << endl << endl;

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


// print tuple definition
void print_tuple(const Person& P)
{
	cout << "Name: " << P.get<0>() 
		<< ", Age: " << P.get<1>() << " years, "
		<< "Height: " << P.get<2>() << " m" << endl;
}