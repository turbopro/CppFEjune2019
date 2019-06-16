// UserInput.cpp
// Level2.3_Ex5
//
// Source file with definition for user_input()
//
// The function takes three (3) aarguments:
// coord_value	-	reference to variable to hold the coordinate value
//					entered by the user 
// point_id		-	the id of the point to be created(used to communicate
//					to the user the id of the Point being created)
// axis			-	the coordinate axis, x or y, being addressed (used to 
//					communicate	this information to the user)
//
// The bool return value is used to indicate to the main function that the user entered 
// Ctrl-Z to quit the programme. The main function then goes through the proper cleanup and 
// closes the programme
// When the user enters Ctrl-Z, then user input is considered incomplete, and bool 'false'
// is returned. If the user enters valid numbers, then the function returns bool 'true'
//

#include <iostream>
#include <limits>			// for user_input() function, used to clear invalid input

using namespace std;

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
