// Main.cpp
// Level2.5_Ex3: Creating Array Class
//
// Test program for the Point, Line and Circle classes 
// Include "Point.h", "Line.h", and "Circle.h" header files
//
// Point tests as follows:
// � Ask the user for the x - and y - coordinates
// � Create a Point object using the default constructor
// � Set the coordinates entered by the user using the setter functions
// � Print the description of the Point returned by the ToString() function
// � Print the point coordinates using the get functions
//
// Line tests as follows:
// � Create a Line object using the default constructor
// � Set the coordinates using the setter functions
//   : use the coordinates of the points created already
// � Print the description of the point returned by the ToString() function
// � Print the Line points using the get functions
// � Print the length of the Line
// � Create a Line object using the constructor
// � Print the description of the Line returned by the ToString() function
// � Print the Line points using the get functions
// � Print the length of the Line
//
// Circle tests as follows:
// � Create a Circle object using the default constructor
// � Set the coordinates using the setter functions
//   : use the coordinates of one of the points created already
// � Print the description of the Circle returned by the ToString() function
// � Print the Circle radius and centre point using the get functions
// � Print the diameter, circumference and area of the Circle
// � Create a Circle object using the constructor
// � Print the description of the Circle returned by the ToString() function
// � Print the Circle radius and centre point using the get functions
// � Print the diameter, circumference and area of the Circle
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

	// cleanup Heap: delete Points
	delete p_P1;
	delete p_P2;
	delete p_P3;
	

	cout << "\n"
		<< "|====================================|\n"
		<< "|           ARRAY Class:             |\n"
		<< "|====================================|\n\n";

	// create array: use default constructor
	Array A_def;

	// print A_def
	cout << "Array from default constructor has elements:\n";
	for (int i = 0; i < sizeof(A_def); i++)		
		cout << "element[" << i << "]: " << A_def.GetElement(i) << endl;
	cout << endl;

	/*
	cout << endl << endl;
	// build array of Points using Heap
	// get array size from user
	// If user_input_array returns false, user entered Ctrl-Z to quit
	if (!(user_input_array(arr_size))) { return 0; }
	cout << "user entered: " << arr_size << endl << endl;

	// create Point array on Heap: use runtime arr_size
	Point* p_PointArray{ new Point[arr_size] };
	
	// loop and create Points on the Heap
	// print each point
	for (int i = 0; i < arr_size; i++)
	{
		p_PointArray[i].X(2.5 * i);
		p_PointArray[i].Y(1.5 * i);
		cout << "Point array[" << i << "]: " << p_PointArray[i] << endl;
	}
	cout << endl;
	// cleanup Heap: delete [] array
	delete[] p_PointArray;

	
	// create a 3-element array of pointers to Points on the Heap
	cout << "\n\nCreating a 3-element array of pointers to Points on the Heap:\n";
	unsigned int p_arr_size = 3;
	Point** pp_parray = new Point* [p_arr_size];
	
	// loop and create a Point for each pointer on the Heap
	// print each point
	for (int i = 0; i < p_arr_size; i++)
	{
		pp_parray[i] = new Point{ 2.5*i, 1.5*i };		// create Point on the Heap 
		cout << "pointer to Point pointer array[" << i << "]: " << *pp_parray[i] << endl;
	}

	cout << endl;
	// cleanup Heap: delete the points
	for (int i = 0; i < p_arr_size; i++)
	{
		//cout << "deleting " << *pp_parray[i] << "..." << endl;
		delete pp_parray[i];
	}
	
	// cleanup Heap: delete [] array
	cout << "deleting 3-element array...\n";
	delete[] pp_parray;	
	*/


	return 0;
}
