// Main.cpp
// Level2.5_Ex3: Creating Array Class
//
// Test program for the Point, Line and Circle classes 
// Include "Point.h", "Line.h", and "Circle.h" header files
//
// Point tests as follows:
// · Ask the user for the x - and y - coordinates
// · Create a Point object using the default constructor
// · Set the coordinates entered by the user using the setter functions
// · Print the description of the Point returned by the ToString() function
// · Print the point coordinates using the get functions
//
// Line tests as follows:
// · Create a Line object using the default constructor
// · Set the coordinates using the setter functions
//   : use the coordinates of the points created already
// · Print the description of the point returned by the ToString() function
// · Print the Line points using the get functions
// · Print the length of the Line
// · Create a Line object using the constructor
// · Print the description of the Line returned by the ToString() function
// · Print the Line points using the get functions
// · Print the length of the Line
//
// Circle tests as follows:
// · Create a Circle object using the default constructor
// · Set the coordinates using the setter functions
//   : use the coordinates of one of the points created already
// · Print the description of the Circle returned by the ToString() function
// · Print the Circle radius and centre point using the get functions
// · Print the diameter, circumference and area of the Circle
// · Create a Circle object using the constructor
// · Print the description of the Circle returned by the ToString() function
// · Print the Circle radius and centre point using the get functions
// · Print the diameter, circumference and area of the Circle
//
// user_input() function declaration to get user input for geometric values
// we use pass by reference to allow the function to change the variable values directly
// the string references are const to make them read-only
// Arguments:
// geom_value		-	reference to relevant coordinate value
// geom_id			-	read-only string reference to the id of the point
//						used to identify the point in the text output to the screen for the user 
// geom_description	-	read-only string reference to the relevant coordinate axis
//						used to identify the axis in the text output to the screen for the user 
// Argument names updated to reflect more generic terms to include a variety of geometric objects
//
// bool return value is used to intercept user entered Ctrl-Z to quit
//

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <string>			// for string operations
#include <iomanip>			// set fixed and precision for cout/cin
#include <cmath>			// for PI
#include "Point.h"			// Point class declaration
#include "Line.h"			// Line class declaration
#include "Circle.h"			// Circle class declaration
#include "Array.h"			// Array class declaration

using namespace std;

// declaration for user_input() function
// const qualifier to make both input strings read-only
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);
bool user_input_array(unsigned int& array_size);


int main(void)
{
	const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	const string y_coord{ "y-coordinate" };
	const string  radius{ "radius" };

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values
	unsigned int arr_size{ 0 };					// array size should be positive only
	
	
	cout << "\n"
		<< "|====================================|\n"
		<< "|           ARRAY Class:             |\n"
		<< "|====================================|\n\n";

	// create array: use default constructor
	Array A_default;

	// print A_default
	arr_size = A_default.Size();		// set arr_size with size of A_default
	cout << "Array, A_default, created from default constructor has " 
		<< arr_size << " elements:\n";
	for (unsigned int i = 0; i < arr_size; i++)
		cout << "element[" << i << "]: " << A_default[i] << endl;

	// assign new Points to Array created from default constructor, and print array
	cout << "\n\nAssigning Points to A_default\nElements in the Array:\n";
	for (unsigned int i = 0; i < arr_size; i++)
	{
		// create Points via Point constructor; use Array overloaded [] operator
		A_default[i] = Point{ 1.7 * i, 3.6 * i };
		cout << "element[" << i << "]: " << A_default[i] << endl;
	}


	// create array: use constructor
	// get and set arr_size from user
	cout << "\n\nCreating Array with constructor\n\n";
	if (!(user_input_array(arr_size))) { return 0; }	// user entered Ctrl-Z to quit
	cout << "user entered: " << arr_size << endl << endl;

	Array A_constructor{ arr_size };

	// populate and print A_constructor
	cout << "\nArray, A_constructor, created with constructor has "
		<< arr_size << " elements:\n";
	for (unsigned int i = 0; i < arr_size; i++)
	{
		A_constructor[i] = Point{ 2.2 * i, 1.5 * i };
		cout << "element[" << i << "]: " << A_constructor[i] << endl;
	}


	// create array: use copy constructor and copy A_constructor
	Array A_copy(A_constructor);
	
	// print copy constructor array
	arr_size = A_copy.Size();
	cout << "\n\nArray, A_copy, is a copy of A_constructor\nElements in Array:\n";
	for (unsigned int i = 0; i < arr_size; i++)
		cout << "element[" << i << "]: " << A_copy[i] << endl;


	// create new Array with default constructor
	//Array A_def1;
	// assign A-default to A_def1: using the overloaded operator=()
	//A_def1 = A_default;

	// print A_def1 constructor array
	//arr_size = A_def1.Size();
	//cout << "\n\nArray, A_def1, was assigned A_default\nElements in Array:\n";
	//for (unsigned int i = 0; i < arr_size; i++)
	//	cout << "element[" << i << "]: " << A_def1[i] << endl;

	//cout << endl;
	//A_def1 = A_def1;
	//cout << endl;

	// self assign Array a to iself
	//cout << "\n\nSelf assignment of A_copy:\n";
	//A_copy = A_copy;
	

	// use [] operator to set new Point for 2nd element of A_copy
	cout << "\nSet 2nd element of A_copy to Point(5, 3.3)\n";
	Point P0 { 5, 3.3 };
	A_copy[1] = P0;

	// print Array
	// cout << "\n\nPoint at 2nd element of A_copy: " << A_copy[1] << endl << endl;
	cout << "\n\nA_copy has elements:\n";
	arr_size = A_copy.Size();
	for (unsigned int i = 0; i < arr_size; i++)
		cout << "element[" << i << "]: " << A_copy[i] << endl;

	return 0;
}
