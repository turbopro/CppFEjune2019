/* Main.cpp
Level2.5_Ex3: Creating Array Class

Test program for the Point, Line and Circle classes 
Include "Point.h", "Line.h", and "Circle.h" header files

 Array tests as follows:
 · Create an Array object using the default constructor
 · Set the Point objects using the operator[]() indexing method
   : use a loop with an index multiplier to create Point object coordinates
 · Print the Array
 · Create another Array with the constructor
   : get user input for the array size
   : use a loop with an index multiplier to create Point object coordinates
 · Print the Array
 · Create another Array with the copy constructor
   : copy the constructor Array
 · Print the Array
 · Self assign the copy constructor Array
 · Get an element from the copy constructor Array using a valid index
 · Get an element from the copy constructor Array using an invalid index
 · Set an element to the copy constructor Array using a valid index
 · Set an element to the copy constructor Array using an invalid index
 · Assign the constructor Array to the copy constructor Array

user_input() function declaration to get user input for geometric values
we use pass by reference to allow the function to change the variable values directly
the string references are const to make them read-only
Arguments:
geom_value		-	reference to relevant coordinate value
geom_id			-	read-only string reference to the id of the point
						used to identify the point in the text output to the screen for the user 
geom_description	-	read-only string reference to the relevant coordinate axis
						used to identify the axis in the text output to the screen for the user 
Argument names updated to reflect more generic terms to include a variety of geometric objects

bool return value is used to intercept user entered Ctrl-Z to quit

user_input_array() function retrieves valid user input for the array size, a positive integer
Uses the same mechanics / tools as for user_input_geom()
Arguments:
unsigned int - array size should be a positive integer

bool return value is used to intercept user entered Ctrl - Z to quit

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
	cout << "user entered: " << arr_size << endl;

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


	// self assign Array a to iself
	cout << "\n\nSelf assignment of A_copy:\n";
	A_copy = A_copy;
	
	cout << "\n\nnon-const Point& Array::operator[]()\n"
		<< "get an element from the array using a valid index (0, ..., 2)\n"
		<< "\nA_copy[2]: " << A_copy[2] << endl << endl;

	cout << "\nnon-const Point& Array::operator[]()\n"
		<< "get an element from the array using an invalid index (>2)\n"
		<< "\nA_copy[5]: \n";
	cout << A_copy[5] << endl << endl;

	
	cout << "\nnon-const Point& Array::operator[]()\n"
		<< "set an element to the array using a valid index (0, ..., 2)\n"
		<< "A_copy[1] = P0;			(P0 = Point(5, 3.3)\n";
	Point P0{ 5, 3.3 };
	A_copy[1] = P0;
	// print Array
	cout << "\nA_copy[1]: " << A_copy[1] << endl << endl;

	cout << "\nnon-const Point& Array::operator[]()\n"
		<< "set an element to the array using an invalid index (>2)\n"
		<< "A_copy[5] = P0;			(P0 = Point(5, 3.3)\n";
	A_copy[5] = P0;
	// print Array
	cout << "\n\nA_copy has elements:\n";
	arr_size = A_copy.Size();
	for (unsigned int i = 0; i < arr_size; i++)
		cout << "element[" << i << "]: " << A_copy[i] << endl;

	// unwanted side effect of Point& Array::operator[](unsigned int) function during a
	// setter indexing operation
	cout << "\nnon-const Point & Array::operator[](unsigned int) produces the unwanted\n"
		<< "side effect of assigning the Point to the Array element 0 when the index\n"
		<< "is out of range\n"
		<< "Array element 0 should remain unchanged if the index is out of range\n"
		<< "for a setter indexing operation\n";

	// const Point& Array::operator(unsigned int) const function
	cout << "\n\nassign A_constructor to A_copy\n"
		<< "this assignment makes use of the const Point& operator[]() const function\n"
		<< "to protect the const Other& object in the Array& operator=(const Array&)\n"
		<< "assignment function:\n"
		<< "A_copy = A_constructor;\n";
	A_copy = A_constructor;

	return 0;
}
