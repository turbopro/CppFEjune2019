/* Main.cpp
Level3.4_Ex2: Simple Inheritance: Creating Shape Base Class

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
	

	cout << "\n"
		<< "|====================================|\n"
		<< "|              SHAPES                |\n"
		<< "|====================================|\n\n";

	// get coordinates for first Point object P1
	//string geom_id{ "Point 1" };
	// check if user hit Ctrl-Z to quit
	//if (!(user_input_geom(x, geom_id, x_coord))) { return 0; }		// If user_input returns false, 
	//if (!(user_input_geom(y, geom_id, y_coord))) { return 0; }		// user entered Ctrl-Z to quit

	// create P1 with default constructor on the Heap: use new
	Shape S1, S2, S3;

	// get ID
	cout << "Shape S1 ID: " << S1.ID() << endl;
	cout << "Shape S2 ID: " << S2.ID() << endl;
	cout << "Shape S3 ID: " << S3.ID() << endl << endl;

	// print S1
	cout << "S1 has " << S1.ToString() << endl;
	cout << "S2 has " << S2.ToString() << endl;
	cout << "S3 has " << S3.ToString() << endl << endl;

	// assign S3 to S2
	cout << "S2 = S3: " << (S3 = S2).ToString() << endl;
	cout << "S3 has " << S3.ToString() << endl << endl;

	// copy S1 to S3
	Shape S4(S1);
	cout << "S4: " << S4.ToString() << endl << endl;




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
	cout << "deleting Points...\n";
	delete p_P1;
	delete p_P2;
	delete p_P3;

	cout << endl;
	// build array of Points using Heap
	// get array size from user
	// If user_input_array returns false, user entered Ctrl-Z to quit
	if (!(user_input_array(arr_size))) { return 0; }

	// create Point array on Heap: use runtime arr_size
	cout << "Creating Point array on the Heap:\n";
	Point* p_PointArray{ new Point[arr_size] };

	// loop and create Points on the Heap
	// print each point
	for (unsigned int i = 0; i < arr_size; i++)
	{
		p_PointArray[i].X(2.5 * i);
		p_PointArray[i].Y(1.5 * i);
		cout << "Point array[" << i << "]: " << p_PointArray[i] << endl;
	}
	cout << endl;
	// cleanup Heap: delete [] array
	cout << "deleting Point array...\n";
	delete[] p_PointArray;


	// create a 3-element array of pointers to Points on the Heap
	cout << "\nCreating a 3-element array of pointers to Points on the Heap:\n";
	unsigned int p_arr_size = 3;
	Point** pp_parray = new Point * [p_arr_size];

	// loop and create a Point for each pointer on the Heap
	// print each point
	for (unsigned int i = 0; i < p_arr_size; i++)
	{
		pp_parray[i] = new Point{ 1.25 * i, 2.15 * i };		// create Point on the Heap 
		cout << "pointer to Point pointer array[" << i << "]: " << *pp_parray[i] << endl;
	}

	cout << endl;
	// cleanup Heap: delete the points
	for (unsigned int i = 0; i < p_arr_size; i++)
	{
		//cout << "deleting " << *pp_parray[i] << "..." << endl;
		delete pp_parray[i];
	}

	// cleanup Heap: delete [] array
	cout << "deleting 3-element array...\n\n";
	delete[] pp_parray;

	// test euality
	// create points with same coordinates and test equality
	cout << "Create Points Pa and Pb with same coordinates:\n";
	Point Pa{ 1, 1 };
	Point Pb{ 1, 1 };
	cout << "Pa: " << Pa << endl;
	cout << "Pb: " << Pb << endl;
	if (Pa == Pb) {cout << "Pa == Pb\n\n"; }
	else { cout << "Pa != Pb\n\n"; }

	// test self assign
	cout << "Self assigning Pb to itself:\n\n";
	Pb = Pb;

	// assign Pa to Pc
	cout << "assign Pa to new Point Pc\n";
	Point Pc;
	Pc = Pa;
	cout << "Pc: " << Pc << "\n\n";

	// negate Pa
	cout << "Negating Point Pa:\n"
		<< -Pa << "\n\n";

	// add Pa + Pb
	cout << "Pa + Pb = " << (Pa + Pb) << "\n\n";

	// scale Pa by 3
	cout << "scale Pa by 3:\n"
		<< "Pa * 3 = " << (Pa * 3) << "\n\n";

	// multiply 6 by Pc
	cout << "6 * Pc:\n"
		<< "6 * Pc = " << (6 * Pc) << "\n\n";


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
	cout << "Line L2: " << L2 << endl << endl;

	// create a line: use copy constructor 
	cout << "Copy L1 to new Line, L3, using copy constructor:\n";
	Line L3(L1);
	
	// print L3
	cout << "Line L3: " << L3 << endl << endl;


	// assign L2 to new L4
	cout << "Assign L2 to L4:\n";
	Line L4 = L2;

	// print L4
	cout << "Line L4 = L2: " << L4 << endl << endl;

	// assignment operator '=': self assignment check
	cout << "Self assignment: L3 to L3:\n";
	L3 = L3;

	// print L3
	cout << "\nLine L3: " << L3 << endl << endl;



	cout << "\n"
		<< "|========================|\n"
		<< "|      CIRCLES:          |\n"
		<< "|========================|\n\n";

	// get coordinates for Point object Pc1 for Circle object C1
	geom_id = "Circle 1";
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
		<< "\nC1 area = " << C1.Area() << endl << endl;

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
	cout << "Circle C2: " << C2 << endl << endl;

	// assignment operator '=': assign C1 to C3
	cout << "Assign C1 to C3\n";
	Circle C3 = C1;

	// print C3
	cout << "Circle C3 = C1: " << C3 << endl << endl;

	// assignment operator '=': self assignment check
	cout << "Self assignment: C3 to C3:\n";
	C3 = C3;

	// print C3
	cout << "\nCircle C3: " << C3 << endl;


	
	cout << "\n\n"
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
	cout << "\n\nCreating Array with copy constructor\n\n";
	Array A_copy(A_constructor);
	
	// print copy constructor array
	arr_size = A_copy.Size();
	cout << "Array, A_copy, is a copy of A_constructor\nElements in Array:\n";
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

	/*
	//	For exception handling phase
	// create array: use constructor
	// set arr_size as negative
	cout << "\n\nCreating Array with constructor\n\n";
	arr_size = -5;
	Array A_negsize{ arr_size };

	// populate and print A_constructor
	cout << "\nArray, A_constructor, created with constructor has "
		<< arr_size << " elements:\n";
	for (unsigned int i = 0; i < arr_size; i++)
	{
		A_negsize[i] = Point{ 2.2 * i, 1.5 * i };
		cout << "element[" << i << "]: " << A_negsize[i] << endl;
	}
	//
	*/

	return 0;
}
