// Main.cpp
// Level2.3_Ex6
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
// user_input() function to get user input for coordinate values
// We use pass by reference to allow the function to change the coordinate values directly
// The string references are const to make them read-only
// Arguments:
// geom_value		-	reference to relevant geometric value
// geom_id			-	read-only string reference to the id of the geometric object
//						used to identify the object in the text output to the screen for the user 
// geom_description	-	read-only string reference to the relevant geometric description
//						used to identify the object in the text output to the screen for the user 
// Argument names updated to reflect more generic terms to include a variety of geometric objects
//
// bool return value is used to intercept user entered Ctrl-Z to quit
//

#include <iostream>
#include <string>			// for string operations
#include <iomanip>			// set fixed and precision for cout/cin
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
	const string  radius{ "radius" };			// added for Circle object

	cout << "\n"
		<< "|========================|\n"
		<< "|       POINTS:          |\n"
		<< "|========================|\n\n";

	// declare/initialise variables for x- and y-coordinates
	// will be used as 'geom_value' argument to user_input() function
	double x{ 0.0 }, y{ 0.0 };
	
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
	cout << "P1 is: " << P1.ToString() << endl;
	//print P1 x, y coordinates 
	cout << "\nP1 x-coordinate = " << P1.X() << endl;
	cout << "P1 y-coordinate = " << P1.Y() << endl << endl;

	// create second Point object P2
	// get user input
	geom_id = "Point 2";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	
	// create P2 with constructor
	Point P2{ x, y };

	// print P2
	cout << "P2 is: " << P2.ToString() << endl;
	//print P2 x, y coordinates 
	cout << "\nP2 x-coordinate = " << P2.X() << endl;
	cout << "P2 y-coordinate = " << P2.Y() << endl;
	
	// distance betwwen point P1 and the origin
	cout << "\nDistance between P1 and the origin: " << fixed << setprecision(2)
		<< P1.Distance() << endl;

	// distance betwwen point P2 and the origin
	cout << "Distance between P2 and the origin: " << fixed << setprecision(2)
		<< P2.Distance() << endl;

	// distance betwwen points P1 and P2
	cout << "\nDistance between P1 and P2: " << fixed << setprecision(2)
		<< P1.Distance(P2) << endl << endl;

	cout << "\n\n"
		<< "|========================|\n"
		<< "|        LINES:          |\n"
		<< "|========================|\n\n";

	// create a line with P1 and P2: use constructor
	Line L1{ P1, P2 };

	// print L1
	cout << "Line L1: " << L1.ToString() << endl;
	cout << "\nL1 startpoint " << L1.StartPoint().ToString();
	cout << "\nL1 endpoint " << L1.EndPoint().ToString();
	cout << "\nL1 length = " << L1.Length() << endl << endl;

	// create a line with P1 and P2: use default constructor 
	Line L2;
	// set x, y coordinates with original user input values
	L2.StartPoint(P1);
	L2.EndPoint(P2);

	// print L2
	cout << "Line L2: " << L2.ToString() << endl;
	cout << "\nL2 startpoint " << L2.StartPoint().ToString();
	cout << "\nL2 endpoint " << L2.EndPoint().ToString();
	cout << "\nL2 length = " << L2.Length() << endl << endl;

	// copy L1 to new L3
	Line L3 = L1;

	// print L3
	cout << "Line L3 (copy of L1): " << L3.ToString() << endl;
	cout << "\nL3 startpoint " << L3.StartPoint().ToString();
	cout << "\nL3 endpoint " << L3.EndPoint().ToString();
	cout << "\nL3 length = " << L3.Length() << endl << endl;

	cout << "\n\n"
		<< "|========================|\n"
		<< "|      CIRCLES:          |\n"
		<< "|========================|\n\n";

	// declare/initialise variables for radius
	double r{ 0.0 };
	// get coordinates for Point object Pc1 and radius for Circle object C1
	geom_id = "Circle 1";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input(r, geom_id, radius)))  { return 0; }
	
	// create centre point Pc1 for C1
	Point Pc1{ x, y };
	// create Circle C1: use constructor
	Circle C1{ r, Pc1 };

	// print C1
	cout << "Circle C1: " << C1.ToString() << endl;
	cout << "\nC1 radius " << C1.Radius();
	cout << "\nC1 centrepoint " << C1.CentrePoint().ToString();
	cout << "\nC1 diameter = " << C1.Diameter()  
		<< "\nC1 circumference = " << C1.Circumference()  
		<< "\nC1 area = " << C1.Area() << endl << endl;

	// get coordinates for Point object Pc2 and radius for Circle object C2
	geom_id = "Circle 2";
	if (!(user_input(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input(r, geom_id, radius)))  { return 0; }
	
	// create centre point Pc2 for C2
	Point Pc2{ x, y };
	// create a circle, use default constructor
	Circle C2;
	// set radius, centre point with user input values
	C2.Radius(r);
	C2.CentrePoint(Pc2);

	// print C2
	cout << "Circle C2: " << C2.ToString() << endl;
	cout << "\nC2 radius " << C2.Radius();
	cout << "\nC2 centrepoint " << C2.CentrePoint().ToString();
	cout << "\nC2 diameter = " << C2.Diameter() 
		<< "\nC2 circumference = " << C2.Circumference() 
		<< "\nC2 area = " << C2.Area() << endl << endl;

	// create copy of C1
	Circle C3 = C1;

	// print C3
	cout << "Circle C3(copy of C1): " << C3.ToString() << endl;
	cout << "\nC3 radius " << C3.Radius();
	cout << "\nC3 centrepoint " << C3.CentrePoint().ToString();
	cout << "\nC3 diameter = " << C3.Diameter() 
		<< "\nC3 circumference = " << C3.Circumference()
		<< "\nC3 area = " << C3.Area() << endl << endl;

	return 0;
}
