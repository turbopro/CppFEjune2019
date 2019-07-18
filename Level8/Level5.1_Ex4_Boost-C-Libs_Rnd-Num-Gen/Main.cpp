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
#include "User_input.h"		// User_input header file

// STL
#include <vector>			// for vector, copy
#include <list>				// for map
#include <map>				// for list
#include <iterator>			// for iter
#include <algorithm>		// for count_if
#include <numeric>			// std::accumulate
#include "STLHelperFunctions.h"		// STL helper functions
#include "BoostHelperFunctions.h"	// Boost helper functions

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/variant.hpp>			// for variant
#include <boost/random.hpp>				// for Random Number Generation

using namespace std;
using boost::tuple;

// print a simple message
void message(const char* s) { cout << s << endl; }
void message(const char* s, const int n) { cout << s << ": " << n << endl; }

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
	//const int arr_size{ 3 };					// array size should be positive only
	//const int stack_size = 3;
	
	
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|        RANDOM NUMBER GENERATOR         |\n"
		<< "|========================================|\n";

	// Throwing dice
	// mersenne Twister
	boost::random::mt19937 myRng;

	// Set the seed
	myRng.seed(static_cast<boost::uint32_t> (std::time(0)));

	// Uniform in range[1,6]
	boost::random::uniform_int_distribution<int> six(1, 6);

	// create a map to hold frequency of each outcome
	map<int, long> statistics;				// container to hold outcome and frequencies
	int outcome, outcome_range, unknown = 0;
	outcome = six(myRng);
	outcome_range = 6;

	// generate trials and place in statistics
	int trials;
	cout << "\nEnter the number of trials: ";
	cin >> trials;

	//NumericArray<int> outcomes(outcome_range);
	NumericArray<long> frequencies(outcome_range);
	//long freq1 = 0, freq2 = 0, freq3 = 0;
	//long freq4 = 0, freq5 = 0, freq6 = 0, unknown = 0;

	cout << endl << endl;
	for (int i = 0; i < frequencies.Size(); i++)
	{
		//outcomes[i] = 0;
		frequencies[i] = 0;
		//cout << "outcomes[" << i << "]: " << outcomes[i] << endl;
		//cout << "frequencies[" << i << "]: " << frequencies[i] << endl;
	}

	cout << endl << endl;

	
	// loop and stores outcomes vs frequency
	for (int i = 0; i < trials; i++)
	{
		outcome = six(myRng);		
		switch (outcome)		// switch on outcome
		{
		case 1: ++frequencies[0]; break;
		case 2: ++frequencies[1]; break;
		case 3: ++frequencies[2]; break;
		case 4: ++frequencies[3]; break;
		case 5: ++frequencies[4]; break;
		case 6: ++frequencies[5]; break;

		default: ++unknown;
		}
	}

	for (int i = 0; i < frequencies.Size(); ++i)
	{
		statistics.emplace(i+1, frequencies[i]);
	}

	for (auto stat : statistics)
	{
		cout << "statistics: " << stat.first << " | " << stat.second << endl;
	}
	


	cout << endl;

	/*
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|                VARIANT                 |\n"
		<< "|========================================|\n";

	// create ShapeType
	cout << "\nCreate ShapeType: ";
	ShapeType shape0;
	Point p, p0;
	shape0 = p;
	cout << "\nShape from variant ShapeType, shape0: " << shape0 << endl;

	// get Shape from choose_shape()
	cout << "\n\nGet shape from user choice: use choose_type()\n";
	ShapeType shape1 = choose_shape();

	cout << "\nShape from variant shape1: " << shape1 << endl << endl;
	
	// try to assign shape1 to Line object: catch exception
	cout << "\n\nTry to assign shape1 to a Line object\n"
		<< "Catch exception if shape1 != a Line object\n\n";
	try
	{
		Line l0 = boost::get<Line>(shape1);
	}
	catch (std::exception& error_msg) { cerr << error_msg.what() << endl; }

	cout << endl << endl;

	// create VariantVisitor with x and y offsets
	cout << "\nCreate VariantVisitor with x and y offset\n";
	VariantVisitor moving_visitor0(3.5, -3.5);

	// apply the visitor to move the Shape
	cout << "\nMove the Shape with the boost::apply_visitor()\n";
	boost::apply_visitor(moving_visitor0, shape1);

	cout << "\nNew Point coordinates for Variant Shape: " << shape1 << endl;
	cout << endl;

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
	Array<Person> peeps(sizeof(ages) / sizeof(ages[0]));
	for (int i = 0; i < peeps.Size(); i++)
	{
		peeps[i].get<0>() = names[i];
		peeps[i].get<1>() = ages[i];
		peeps[i].get<2>() = heights[i];
	}

	// print peeps
	cout << "\nPerson array, peeps, has:\n\n";
	for (int i = 0; i < peeps.Size(); i++) { print_tuple(peeps[i]); }


	// change the name of Lucy to Lucille and Mindy's age to 27
	cout << "\n\nChange peeps[3] name to 'Lucille', and peeps[4] age to 27:\n\n";
	peeps[3].get<0>() = "Lucille";
	peeps[1].get<2>() = 2.5;
	cout << "Updated peeps[3] has "; print_tuple(peeps[3]);
	cout << "Updated peeps[1] has "; print_tuple(peeps[1]);

	// incrment the age of all members of the peeps array
	cout << "\n\nIncrement the age for all peeps elements:\n\n";
	for (int i = 0; i < peeps.Size(); i++)
	{
		peeps[i].get<1>()++;
		print_tuple(peeps[i]);
	}
	cout << endl;
	

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
		cout << "\nCreate array of shared_ptrs to Shape objects:\n";
		int arr_size = 3;
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

