/* Main.cpp
Level3.5_Ex2: Polymorphism - Calling Base Class Functionality

Test program for the Point, Line and Circle classes 
Include "Point.h", "Line.h", and "Circle.h" header files

Point tests as follows:
 · Ask the user for the x - and y - coordinates
 · Create a Point object on the Heap using the default constructor
 · Set the coordinates entered by the user using the setter functions
 · Print the Point
 · Ask the user for the new x - and y - coordinates
 · Create a Point object on the Heap using the constructor
 · Set the coordinates entered by the user using the setter functions
 · Print the Point
 · Create a Point object on the Heap using the copy constructor
 · Copy the constructor Point
 · Print the point coordinates using the get functions
 · Delete the Points to free the memory on the Heap
 · Create a Point array on the Heap: use user input for array size
 · Set Points on the array and print
 · Delete the array to free the memory on the Heap
 · Create a 3-element array of pointers to Points on the Heap
 · Set the coordinates for the elements; print the elements
 · Delete the Arrays to free the memory on the Heap

Line tests as follows:
 · Create a Line object using the constructor
 · Print the Line
 · Print the length of the Line
 · Create a Line object using the default constructor
 · Print the Line
 · Create a Line object using the assignment operator
 · Print the Line
 · Test the self assign a Line to itself
 
Circle tests as follows:
 · Create a Circle object using the constructor: get user input for dimensions
 · Print the Circle
 · Create a Circle object using the default constructor: get user input for dimensions
 · Print the Circle
 · Create a Circle object using the assignment operator
 · Print the Circle
 · Test the self assign a Circle to itself

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
 
user_input() function declaration to retrieve user input for geometric values
we use pass by reference to allow the function to change the variable values directly
the string references are const to make them read-only
Arguments:
geom_value		-	reference to relevant coordinate value
geom_id			-	read-only string reference to the id of the point
					used to identify the point in the text output to the screen for the user 
geom_description-	read-only string reference to the relevant coordinate axis
					used to identify the axis in the text output to the screen for the user 
Argument names updated to reflect more generic terms to include a variety of geometric objects

bool return value is used to intercept user entered Ctrl-Z to quit


user_input_array() function retrieves valid user input for the array size, a positive integer
Uses the same mechanics / tools as for user_input_geom()
Arguments:
unsigned int	-	array size should be a positive integer

bool return value is used to intercept user entered Ctrl-Z to quit


using directives and declarations for Turbopro::CAD and Turbopro::Container namespaces

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
#include "Shape.h"			// Shape class declaration

using namespace std;

// declaration for user_input_geom() function
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);

// declaration for user_input_array() function
bool user_input_array(unsigned int& array_size);


int main(void)
{
	using namespace Turbopro::Containers;		// namespace directive
	using namespace Turbopro::CAD;				// namespace directive
	using Turbopro::CAD::Line;					// namespace declaration
	namespace TCad = Turbopro::CAD;				// namespace alias


	const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	const string y_coord{ "y-coordinate" };
	const string  radius{ "radius" };

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values
	unsigned int arr_size{ 0 };					// array size should be positive only
	

	cout << "\nExercise Tests:\n"
		<< "------------------------------\n\n";
	
	Shape s; // Create shape.
	Point p(10, 20); // Create point.
	Line l{ Point(1, 2), Point(3, 4) }; // Create line.

	cout << "s.ToString(): " << s.ToString() << endl; // Print shape.
	cout << "p.ToString(): " << p.ToString() << endl; // Print point.
	cout << "l.ToString(): " << l.ToString() << endl; // Print line

	
	cout << "\nShape s ID: " << s.ID() << endl; // ID of the shape.
	cout << "Yes, Point p ID: " << p.ID() << endl; // ID of the point. Does this work?
	cout << "Yes,  Line l ID: " << l.ID() << endl; // ID of the line. Does this work?

	cout << "\n\nCreate a pointer to a Shape variable, sp:\n";
	Shape* sp; // Create pointer to a shape variable.
	sp = &p; // Point in a shape variable. Possible?
	cout << "Yes, we may assign a Shape Pointer to a Point\n";
	cout << "\nsp->ToString(): " << sp->ToString() << endl; // What is printed?
	cout << "The Point's details with its ID\n";

	// Create and copy Point p to new point.
	cout << "\nCreate a new Point, P2, use default constructor:\n";
	Point p2;
	cout << "Copy p to p2: " << endl;
	p2 = p;
	// Is the ID copied if you do not call the base class assignment in point?
	cout << "\nP2: " << p2 << ", " << p2.ID() << endl;
	cout << "\nNo, the ID is not copied if you do not call the base class assignment\n";

	cout << "\nEnd Exercise Tests:\n"
		<< "------------------------------\n\n";


	
	cout << "\n\n"
		<< "|========================|\n"
		<< "|        LINES:          |\n"
		<< "|========================|\n\n";

	// create a line: use constructor
	cout << "Create Line, L1, using constructor:\n";
	Point P1{ 1, 1 };
	Point P2{ 4, 5 };
	Line L1{ P1, P2 };	
	
	// print L1
	cout << "Line L1: " << L1 << endl
		<< "\nL1 startpoint " << L1.StartPoint()
		<< "\nL1 endpoint " << L1.EndPoint()
		<< "\nL1 length = " << fixed << setprecision(2)
		<< L1.Length() << endl << endl;
	
	// create a line with P1 and P2: use default constructor 
	cout << "Create Line, L2, using default constructor:\n";
	Line L2;
	// set Points with new values for P1 and P2
	P1 = { -3, -4 };
	P2 = { 3, 4 };
	L2.StartPoint(P1);
	L2.EndPoint(P2);
	
	// print L2
	cout << "Line L2: " << L2
		<< "\nas derived from Shape, L2: " << L2.ID() << endl << endl;

	// create a line: use copy constructor 
	cout << "Copy L1 to new Line, L3, using copy constructor:\n";
	Line L3(L1);

	// print L3
	cout << "Line L3: " << L3 << endl << endl;

	
	// assign L2 to new L4
	cout << "Assign L2 to L4:\n";
	Line L4 = L2;

	// print L4
	cout << "Line L4 = L2: " << L4
		<< "\nas derived from Shape, L4: " << L4.ID() << endl << endl;

	// assignment operator '=': self assignment check
	cout << "Self assignment: L3 to L3:\n";
	L3 = L3;

	// print L3
	cout << "\nLine L3: " << L3 << endl << endl;
	cout << "Line L3: " << L3.ToString() << endl << endl;

	

	cout << "\n"
		<< "|========================|\n"
		<< "|      CIRCLES:          |\n"
		<< "|========================|\n\n";

	// get coordinates for Point object Pc1 for Circle object C1
	string geom_id = "Circle 1";
	if (!(user_input_geom(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input_geom(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input_geom(r, geom_id, radius))) { return 0; }

	// create centre point Pc1 for C1
	Point Pc1{ x, y };
	// create Circle C1: use constructor
	cout << "Create Circle, C1, using constructor:\n";
	Circle C1{ r, Pc1 };

	// print C1
	cout << "Circle C1: " << C1 << endl
		<< "\nC1 radius " << std::ios::fixed << setprecision(2) << C1.Radius()
		<< "\nC1 centrepoint " << C1.CentrePoint()
		<< "\nC1 diameter = " << C1.Diameter()
		<< "\nC1 circumference = " << C1.Circumference()
		<< "\nC1 area = " << C1.Area()
		<< "\nas derived from Shape, C1: " << C1.ID() << endl << endl;

	// get coordinates for Point object Pc2 for Circle object C2
	geom_id = "Circle 2";
	if (!(user_input_geom(x, geom_id, x_coord))) { return 0; }		// If user_input returns false,
	if (!(user_input_geom(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit
	if (!(user_input_geom(r, geom_id, radius))) { return 0; }

	// create centre point Pc2 for C2
	Point Pc2{ x, y };
	// create a circle, use default constructor
	cout << "Create Circle, C2, using default constructor:\n";
	Circle C2;
	// set radius, centre point with user input values
	C2.Radius(r);
	C2.CentrePoint(Pc2);

	// print C2
	cout << "Circle C2: " << C2
		<< "\nas derived from Shape, C2: " << C2.ID() << endl << endl;

	// assignment operator '=': assign C1 to C3
	cout << "Assign C1 to C3\n";
	Circle C3 = C1;

	// print C3
	cout << "Circle C3 = C1: " << C3
		<< "\nas derived from Shape, C3: " << C3.ID() << endl << endl;

	// assignment operator '=': self assignment check
	cout << "Self assignment: C3 to C3:\n";
	C3 = C3;

	// print C3
	cout << "\nCircle C3: " << C3
		<< "\n\nCircle 3 to string: " << C3.ToString() << endl;

	
	
	return 0;
}
