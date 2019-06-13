// Main.cpp
//
// Test program for the Point class. Include "Point.h"
// Tests as follows:
// · Ask the user for the x - and y - coordinates
// · Create a Point object using the default constructor
// · Set the coordinates entered by the user using the setter functions.
// · Print the description of the point returned by the ToString() function.
// · Print the point coordinates using the get functions.
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

#include <iostream>
#include <limits>			// for user_input() function, used to clear invalid input
#include <string>
#include <iomanip>			// set precision for cout/cin
#include "Point.h"			// Point class declaration

using namespace std;

// declaration for user_input() function
// const qualifier to make both input strings read-only
void user_input(double& coord_val, const string& point_id, const string& axis);

int main(void)
{
	const string x_axis{ "x" };		// for user input: set axis value for coordinate
	const string y_axis{ "y" };

	double x{ 0.0 }, y{ 0.0 };		// declare/initialise coordinates
	// get coordinates for first Point, P1
	string point_id{ "P1" };
	user_input(x, point_id, x_axis);
	user_input(y, point_id, y_axis);

	// create P1 object with default constructor
	Point P1;

	// set x, y coordinates with user input values
	P1.SetX(x);
	P1.SetY(y);

	// print P1 object description using ToString() member function 
	cout << "\nP1 is: " << P1.ToString() << endl;

	// print P1 object's x, y coordinates via get functions 
	cout << "\nP1 x-coordinate = " << P1.GetX() << endl;
	cout << "P1 y-coordinate = " << P1.GetY() << endl << endl;

	// create second Point, P2
	point_id = "P2";
	user_input(x, point_id, x_axis);
	user_input(y, point_id, y_axis);
	Point P2{ x, y };		// use constructor
	// print P2
	cout << "\nP2 is: " << P2.ToString() << endl;
	cout << "\nP2 x-coordinate = " << P2.GetX() << endl;
	cout << "P2 y-coordinate = " << P2.GetY() << endl;

	// distance betwwen point P1 and the origin
	cout << "\nDistance between P1 and the origin: " << fixed << setprecision(2) // two decimal places
		<< P1.DistanceOrigin() << endl;

	// distance betwwen point P2 and the origin
	cout << "Distance between P2 and the origin: " << fixed << setprecision(2)
		<< P2.DistanceOrigin() << endl << endl;

	// save distance betwwen point P1 and the P2 to view death of copy of P2 object after
	// call-by-value to Distance() function
	double point_diff = P1.Distance(P2);	// create P2 copy with copy constructor
	cout << "\nDistance between P1 and P2: " << fixed << setprecision(2)
		<< point_diff << endl;

	return 0;
}

void user_input(double& coord_value, const string& point_id, const string& axis)
{
	// loop until valid user input, or, quit if Ctrl-Z entered
	while ((cout << "Enter " << axis << "-coordinate value for " << point_id << " (Ctrl-Z to quit): ")
		&& !(cin >> coord_value) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit
		{
			cout << "\nExiting. Bye...\n";
			exit(0);
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}
}
