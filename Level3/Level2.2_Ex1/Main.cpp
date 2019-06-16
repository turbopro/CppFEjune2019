// Main.cpp
// Level2.3_Ex1
//
// Test program for the Point class. Include "Point.h"
// Tests as follows:
// · Ask the user for the x - and y - coordinates
// · Create a Point object using the default constructor
// · Set the coordinates entered by the user using the setter functions.
// · Print the description of the point returned by the ToString() function.
// · Print the point coordinates using the getter functions.
//

#include <iostream>
#include <limits>					// for user input handling
#include "Point.h"

using namespace std;

int main(void)
{
	// get user input for x
	double x = 0.0;
	// while loop that continues until the user makes a valid entry
	// if the user enters Ctrl-Z, the programme is terminated
	// if the user enters an invalid entry, the entry will be cleared, and
	// the user prompted again to enter a valid entry
	while (cout << "Please enter x coordinate value (Ctrl-Z to quit): " && !(cin >> x) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit if user enters Ctrl-Z
		{
			cout << "\nExiting. Bye...\n";
			return 0;
		}
		cout << "Invalid entry: you must enter a valid number\n" << endl;
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}

	// get user input for y; loop until valid user input or quit
	double y = 0.0;
	while (cout << "Please enter y coordinate value (Ctrl-Z to quit): " && !(cin >> y) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit if user enters Ctrl-Z
		{
			cout << "\nExiting. Bye...\n";
			return 0;
		}
		cout << "Invalid entry: you must enter a valid number\n" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	// create Point object with default constructor
	Point P0;

	// set x, y coordinates with user input values
	P0.SetX(x);
	P0.SetY(y);
	
	// print Point object description using ToString() member function 
	cout << "\nP0: " << P0.ToString() << endl;

	// print Point object's x, y coordinates via get functions 
	cout << "\nP0.x = " << P0.GetX() << endl;
	cout << "P0.y = " << P0.GetY() << endl;

	return 0;
}
