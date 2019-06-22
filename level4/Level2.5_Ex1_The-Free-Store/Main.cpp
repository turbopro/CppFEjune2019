// Main.cpp
// Level2.5_Ex1: The Free Store: Dynamically Creating Objects
//
// Test program for the Point, Line and Circle classes 
// Include "Point.h", "Line.h", and "Circle.h" header files
//
// Point tests as follows :
// · Ask the user for the x - and y - coordinates
// · Create a Point object on the Heap using the default constructor
// · Set the coordinates entered by the user using the setter functions
// · Print the Point
// · Ask the user for the new x - and y - coordinates
// · Create a Point object on the Heap using the constructor
// · Set the coordinates entered by the user using the setter functions
// · Print the Point
// · Create a Point object on the Heap using the copy constructor
// · Copy the constructor Point
// · Print the point coordinates using the get functions
// · Delete the Points to free the memory on the Heap
// · Create a Point array on the Heap : use user input for array size
// · Set Points on the arrayand print
// · Delete the array to free the memory on the Heap
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
	unsigned int arr_size{ 0 };					// array size should be positive ints only

	cout << "\n"
		<< "|====================================|\n"
		<< "|       POINTS on the Heap:          |\n"
		<< "|====================================|\n\n";

	// get coordinates for first Point object P1
	string geom_id{ "Point 1" };
	// check if user hit Ctrl-Z to quit
	if (!(user_input_geom(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	if (!(user_input_geom(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit

	// create P1 with default constructor on the Heap: use new
	Point* p_P1 = new Point;
	
	// set x, y coordinates with user input values
	p_P1->X(x);
	p_P1->Y(y);
	// print P1
	cout << "(*p_P1) Point by default constructor is: " << *p_P1
		<< "\nDistance from origin: " << fixed << setprecision(2) 
		<< p_P1->Distance() << endl << endl;
	
	// create second Point object P2
	// get user input
	geom_id = "Point 2";
	if (!(user_input_geom(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	if (!(user_input_geom(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit

	// create P2 with constructor on the Heap: use new
	//Point P2{ x, y };
	Point* p_P2 = new Point{ x, y };

	// print P2
	cout << "(*p_P2) Point by constructor is: " << *p_P2
		<< "\nDistance from origin: " << fixed << setprecision(2)
		<< p_P2->Distance() << endl << endl;

	// create P3 with copy constructor on the Heap: use new
	Point* p_P3 = new Point(*p_P2);

	// print P3
	cout << "(*p_P3) Point by copy constructor is: " << *p_P3
		<< "\nDistance from origin: " << fixed << setprecision(2)
		<< p_P3->Distance() << endl << endl;

	// cleanup Heap
	delete p_P1;
	delete p_P2;
	delete p_P3;
	
	// build array of Points using Heap
	// get array size from user
	// If user_input_array returns false, user entered Ctrl-Z to quit
	if (!(user_input_array(arr_size))) { return 0; }
	cout << "user entered: " << arr_size << endl << endl;
	
	// create Point array on the Stack
	// error: arr_size must be set at compile time
	//Point P_arr[arr_size]{ Point(1, 2), Point(3, 4), Point(5, 6), Point(7, 8), Point(9, 10) };
	//double dist_p0 = P_arr[0].Distance();
	//cout << "P_arr[0] distance from origin: " << dist_p0 << endl << endl;

	// create Point array on Heap: use runtime arr_size
	Point* p_PointArray{ new Point[arr_size] };
	// set values for p_PointAarray[0] Point
	p_PointArray[0].X(x);
	p_PointArray[0].Y(y);
	cout << "P_arr[0] Point is: " << p_PointArray[0] << endl << endl;

	// cleanup Heap
	delete[] p_PointArray;

	return 0;
}
