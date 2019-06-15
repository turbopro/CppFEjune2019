// Main.cpp
// Level2.3_Ex6
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
	P1.X(x);
	P1.Y(y);

	// print P1 object description using ToString() member function 
	cout << "\n\nP1 is: " << P1.ToString() << endl;

	//print P1 object's x, y coordinates via get functions 
	//cout << "\nP1 x-coordinate = " << P1.X() << endl;
	//cout << "P1 y-coordinate = " << P1.Y() << endl << endl;


	// create second Point, P2
	// get user input
	point_id = "P2";
	user_input(x, point_id, x_axis);
	user_input(y, point_id, y_axis);

	// create Point P2: use constructor
	Point P2{ x, y };

	// print P2
	cout << "\nP2 is: " << P2.ToString() << endl;
	//cout << "\nP2 x-coordinate = " << P2.X() << endl;
	//cout << "P2 y-coordinate = " << P2.Y() << endl;
	/*
	// distance betwwen point P1 and the origin (use Disance() with no arguments)
	cout << "\nDistance between P1 and the origin: " << fixed << setprecision(2) // two decimal places
		<< P1.Distance() << endl;

	// distance betwwen point P2 and the origin (use Disance() with no arguments)
	cout << "Distance between P2 and the origin: " << fixed << setprecision(2)
		<< P2.Distance() << endl << endl;

	// save distance betwwen point P1 and the P2 to view death of copy of P2 object after
	// call-by-reference to Distance() function with one argument 
	double point_diff = P1.Distance(P2);	// create P2 copy with copy constructor
	cout << "\nDistance between P1 and P2: " << fixed << setprecision(2)
		<< point_diff << endl << endl;

	// create const Point object
	const Point Pc{ 1.5, 3.9 };
	// print the x coordinate value for Pc
	cout << "\nPc x-coordinate = " << Pc.X() << endl << endl;
	*/

	// create a line with P1 and P2: use constructor
	Line L1{ P1, P2 };

	// print L1
	cout << "\nLine L1: " << L1.ToString() << endl;
	cout << "\nL1 startpoint " << L1.StartPoint().ToString() << endl;
	cout << "\nL1 endpoint " << L1.EndPoint().ToString() << endl;
	cout << "\nL1 length = " << L1.Length() << endl << endl;

	// create a line with P1 and P2: use default constructor 
	Line L2;
	// set x, y coordinates with original user input values
	L2.StartPoint(P1);
	L2.EndPoint(P2);

	// print L2
	cout << "\nLine L2: " << L2.ToString() << endl;
	cout << "\nL2 startpoint " << L2.StartPoint().ToString() << endl;
	cout << "\nL2 endpoint " << L2.EndPoint().ToString() << endl;
	cout << "\nL2 length = " << L2.Length() << endl << endl;

	// copy L1 to new L3
	Line L3 = L1;

	// print L3
	cout << "\nLine L3: " << L3.ToString() << endl;
	cout << "\nL3 startpoint " << L3.StartPoint().ToString() << endl;
	cout << "\nL3 endpoint " << L3.EndPoint().ToString() << endl;
	cout << "\nL3 length = " << L3.Length() << endl << endl;


	// create a circle, use constructor
	Circle C1{ 5, P1 };

	// print C1
	cout << "\nLine C1: " << C1.ToString() << endl;
	cout << "\nC1 radius " << C1.Radius() << endl;
	cout << "\nC1 endpoint " << C1.CentrePoint().ToString() << endl;
	cout << "\nC1 circumference = " << C1.Circumference() << endl 
		<< "\nC1 diameter = " << C1.Diameter() << endl 
		<< "\nC1 area = " << C1.Area() << endl << endl;

	// create a circle, use default constructor
	Circle C2;

	C2.Radius(5);
	C2.CentrePoint(P2);

	// print C2
	cout << "\nC2: " << C2.ToString() << endl;
	cout << "\nC2 radius " << C2.Radius() << endl;
	cout << "\nC2 endpoint " << C2.CentrePoint().ToString() << endl;
	cout << "\nC2 circumference = " << C2.Circumference() << endl
		<< "\nC2 diameter = " << C2.Diameter() << endl
		<< "\nC2 area = " << C2.Area() << endl << endl;

	return 0;
}


	