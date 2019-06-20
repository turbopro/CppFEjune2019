// Main.cpp
// Level2.4_Ex4: Friends
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

using namespace std;

// declaration for user_input() function
// const qualifier to make both input strings read-only
bool user_input(double& geom_value, const string& geom_id, const string& geom_description);

int main(void)
{
	const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	const string y_coord{ "y-coordinate" };
	const string  radius{ "radius" };

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values

	cout << "\n"
		<< "|========================|\n"
		<< "|       POINTS:          |\n"
		<< "|========================|\n\n";

	// get coordinates for first Point object P1
	string geom_id{ "Point 1" };
	// check if user hit Ctrl-Z to quit
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit

	// create P1 with default constructor
	Point P1;
	// set x, y coordinates with user input values
	P1.X(x);
	P1.Y(y);
	// print P1
	cout << "P1 is: " << P1 << endl << endl;
	
	// create second Point object P2
	// get user input
	geom_id = "Point 2";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit

	// create P2 with constructor
	Point P2{ x, y };

	// print P2
	cout << "P2 is: " << P2 << endl << endl;

	// overloaded operators for the Point class
	// assignment operator '='
	cout << "\n\nassignment operator '='\n\n";
	Point P3 = P1;
	// print P3
	cout << "P3 = P1: " << P3 << endl << endl;

	// assignment operator '=':	self assignment check
	cout << "\n\nassignment operator '=': no self assignment\n\n";
	P3 = P3;
	// print P3
	cout << "\nP3: " << P3 << endl << endl;

	// addition operator '+'
	cout << "\naddition operator '+'\n\n";
	Point P4 = P1 + P2;
	// print P4
	cout << "P4 = P1 + P2: " << P4 << endl;
	
	// P2 + P1
	P4 = P2 + P1;
	// print P4
	cout << "P4 = P2 + P1: " << P4 << endl << endl;
	
	// unary negation operator '-': negate the coordinates of the Point  
	cout << "\nunary operator '-': negates the coordinates of a Point\n\n";
	Point P5 = -P1;
	// print P5
	cout << "P5 = -P1: " << P5 << endl << endl;
	
	// multiplication operator '*': scaling a Point 
	cout << "\nmultiplication operator '*'\: scaling operator: Point * double\n\n";
	Point P6 = P1 * 3;
	// print P6
	cout << "P6 = P1 * 3: " << P6 << endl << endl;

	cout << "\nmultiplication operator '*': scaling operator: double * Point\n\n";
	Point P7 = 4 * P2;
	// print P7
	cout << "P7 = 4 * P2: " << P7 << endl << endl;
	
	// compound multiplication/assignment operator: scale the coordinates, then assign to the Point
	cout << "\ncompound multiplication/assignment operator '*=': scale and assign to point\n\n";
	P7 *= 4;
	// print P4
	cout << "P7 *= 4: " << P7 << endl << endl;
	
	// equality operator '==': compare Point a to Point b for equality
	cout << "\nequality operator '=='\n\n";
	Point P8 = P7;
	cout << "P7: " << P7 << ", " << "P8: " << P8 << endl;
	if (P7 == P8) { cout << "P7 and P8 share the same coordinates\n\n"; }
	else { cout << "P7 and P8 do not share the same coordinates\n\n"; }

	P8 = P6;
	cout << "P7: " << P7 << ", " << "P8: " << P8 << endl;
	if (P7 == P8) { cout << "P7 and P8 share the same coordinates\n\n"; }
	else { cout << "P7 and P8 do not share the same coordinates\n\n"; }
	
	// single argument constructor: implicit conversion operator
	Point p9{ 1.0, 1.0 };
	if (p9 == Point(1.0)) cout << "Equal!" << endl;
	else cout << "Not equal" << endl;



	
	
	cout << "\n\n"
		<< "|========================|\n"
		<< "|        LINES:          |\n"
		<< "|========================|\n\n";

	// create a line with P1 and P2: use constructor
	Line L1{ P1, P2 };

	// print L1
	cout << "Line L1: " << L1 << endl
		<< "\nL1 startpoint " << L1.StartPoint()
		<< "\nL1 endpoint " << L1.EndPoint()
		<< "\nL1 length = " << fixed << setprecision(2) 
		<< L1.Length() << endl << endl;

	// create a line with P1 and P2: use default constructor 
	Line L2;
	// set x, y coordinates with original user input values
	L2.StartPoint(P1);
	L2.EndPoint(P2);

	// print L2
	cout << "Line L2: " << L2 << endl << endl;

	// assign L1 to new L3
	Line L3 = L1;

	// print L3
	cout << "Line L3 = L1): " << L3 << endl << endl;

	// assignment operator '=': self assignment check
	L3 = L3;

	// print L3
	cout << "\nLine L3: " << L3 << endl << endl;

	
	
	cout << "\n\n"
		<< "|========================|\n"
		<< "|      CIRCLES:          |\n"
		<< "|========================|\n\n";

	// get coordinates for Point object Pc1 for Circle object C1
	geom_id = "Circle 1";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input(r, geom_id, radius))) { return 0; }

	// create centre point Pc1 for C1
	Point Pc1{ x, y };
	// create Circle C1: use constructor
	Circle C1{ r, Pc1 };

	// print C1
	cout << "Circle C1: " << C1 << endl
		<< "\nC1 radius " << std::ios::fixed << setprecision(2) <<  C1.Radius()
		<< "\nC1 centrepoint " << C1.CentrePoint()
		<< "\nC1 diameter = " << C1.Diameter()
		<< "\nC1 circumference = " << C1.Circumference()
		<< "\nC1 area = " << C1.Area() << endl << endl;

	// get coordinates for Point object Pc2 for Circle object C2
	geom_id = "Circle 2";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input(r, geom_id, radius))) { return 0; }

	// create centre point Pc2 for C2
	Point Pc2{ x, y };
	// create a circle, use default constructor
	Circle C2;
	// set radius, centre point with user input values
	C2.Radius(r);
	C2.CentrePoint(Pc2);

	// print C2
	cout << "Circle C2: " << C2 << endl << endl;

	// assignment operator '=': assign C1 to C3
	Circle C3 = C1;

	// print C3
	cout << "Circle C3 = C1: " << C3 << endl << endl;
	
	// assignment operator '=': self assignment check
	C3 = C3;

	// print C3
	// print C3
	cout << "Circle C3: " << C3 << endl;
	

	return 0;
}
