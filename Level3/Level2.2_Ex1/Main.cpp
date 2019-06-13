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

#include <iostream>
#include <limits>
#include "Point.h"

using namespace std;

int main(void)
{
	
		
	// get user input for x, y coordinates
	double x;
	// loop until valid user input
	//do
	//cout << "Please enter x coordinate value: ";	
	/*
	while ( 1 )
	{
		if (cin.eof())
		{
			cin.clear();
			std::cout << "Exiting.  Bye..." << endl;
			exit(0);
		}
		else if (!(cin >> x) || cin.peek() != '\n')
		{
			cout << "Invalid entry: you must enter a valid number" << endl;
			cin.clear();		// clear error flag for next input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
			continue;
		}
		else
		{
			break;
		}
	} //while (1);
	
	//double y = 10.5;
	*/
	while (cout << "Please enter x coordinate value: " && !(cin >> x) || cin.peek() != '\n')
	{
		cout << "Invalid entry: you must enter a valid number" << endl;
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}

	double y;
	while (cout << "Please enter y coordinate value: " && !(cin >> y) || cin.peek() != '\n')
	{
		cout << "Invalid entry: you must enter a valid number" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	

	// create Point object with default constructor
	Point p0;

	// set x, y coordinates with user input values
	p0.SetX(x);
	p0.SetY(y);
	
	// print Point object description using ToString() member function 
	cout << "\np0: " << p0.ToString() << endl;

	// print Point object's x, y coordinates via get functions 
	cout << "\npo.x = " << p0.GetX() << endl;
	cout << "po.y = " << p0.GetY() << endl;

	return 0;
}