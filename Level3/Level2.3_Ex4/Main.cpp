// Main.cpp
// Level2.3_Ex4
//
// Test program for the Point class. Include "Point.h"
// Tests as follows:
// � Ask the user for the x - and y - coordinates
// � Create a Point object using the default constructor
// � Set the coordinates entered by the user using the setter functions.
// � Print the description of the point returned by the ToString() function.
// � Print the point coordinates using the get functions.
//
// user_input() function to get user input for coordinate values
// we use pass by reference to allow the function to change the coordinate values directly
// the string references, however, are const to make them read-only
// Arguments:
// coord_value	-	reference to relevant coordinate value
// point_id		-	read-only string reference to the id of the point
//                  used to identify the point in the text output to the screen for the user 
// axis			-	read-only string reference to the relevant coordinate axis
//                  used to identify the axis in the text output to the screen for the user 
//
// The bool return value is used to indicate to the main function that the user entered 
// Ctrl-Z to quit the programme. The main function then goes through the proper cleanup and 
// closes the programme
// When the user enters Ctrl-Z, then user input is considered incomplete, and bool 'false'
// is returned. If the user enters valid numbers, then the function returns bool 'true'
//

#include <iostream>
#include <limits>			// for user_input() function, used to clear invalid input
#include <string>			// for string operations
#include <iomanip>			// set fixed and precision for cout/cin
#include "Point.h"			// Point class declaration

using namespace std;

// declaration for user_input() function
// const qualifier to make both input strings read-only
bool user_input(double& coord_val, const string& point_id, const string& axis);

int main(void)
{
	const string x_axis{ "x" };		// for user input: set axis value for coordinate
	const string y_axis{ "y" };

	double x{ 0.0 }, y{ 0.0 };		// declare/initialise coordinates
	// get coordinates for first Point, P1
	string point_id{ "P1" };
	if (!(user_input(x, point_id, x_axis))) { return 0; }		// If user_input returns false, 
	if (!(user_input(y, point_id, y_axis))) { return 0; }		// user entered Ctrl-Z to quit

	// create P1 object with default constructor
	Point P1;

	// set x, y coordinates with user input values
	P1.X(x);
	P1.Y(y);

	// print P1 object description using ToString() member function 
	cout << "\nP1 is: " << P1.ToString() << endl;

	// print P1 object's x, y coordinates via get functions 
	cout << "\nP1 x-coordinate = " << P1.X() << endl;
	cout << "P1 y-coordinate = " << P1.Y() << endl << endl;

	// create second Point, P2
	point_id = "P2";
	if (!(user_input(x, point_id, x_axis))) { return 0; }		// If user_input returns false, 
	if (!(user_input(y, point_id, y_axis))) { return 0; }		// user entered Ctrl-Z to quit
	
	Point P2{ x, y };		// use constructor
	
	// print P2
	cout << "\nP2 is: " << P2.ToString() << endl;
	cout << "\nP2 x-coordinate = " << P2.X() << endl;
	cout << "P2 y-coordinate = " << P2.Y() << endl;

	// distance betwwen point P1 and the origin (use Disance() with no arguments)
	cout << "\nDistance between P1 and the origin: " << fixed << setprecision(2) // two decimal places
		<< P1.Distance() << endl;

	// distance betwwen point P2 and the origin (use Disance() with no arguments)
	cout << "Distance between P2 and the origin: " << fixed << setprecision(2)
		<< P2.Distance() << endl;

	// distance betwwen point P1 and the P2 	
	cout << "\nDistance between P1 and P2: " << fixed << setprecision(2)
		<< P1.Distance(P2) << endl << endl;

	// create const Point object
	const Point Pc{ 1.5, 3.9 };

	// assign new x coordinate to Pc
	// Pc.X(0.3);	->	Will not compile: "no instance of overloaded function Point::X matches the
	//					argument list and object (the object has type qualifiers that prevent a match)"
	//					We should not be able to change the value of a const object

	// print the x coordinate value for Pc
	cout << "\nPc x-coordinate = " << Pc.X() << endl << endl;

	return 0;
}

bool user_input(double& coord_value, const string& point_id, const string& axis)
{
	// loop until valid user input, or, quit if Ctrl-Z entered
	while ((cout << "Enter " << axis << "-coordinate value for " << point_id << " (Ctrl-Z to quit): ")
		&& !(cin >> coord_value) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit
		{
			cout << "\nExiting. Bye...\n";
			return false;	// user_input() did not complete, return false
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}
	return true;			// user_input() completed successfully, return true
}
