// UserInput.cpp
// Level2.3_Ex6
//
// Source file with definition for user_input()
//
// The function takes three (3) aarguments:
// geom_value			-	reference to variable to hold the coordinate value
//							entered by the user 
// geom_id				-	the id of the point to be created(used to communicate
//							to the user the id of the Point being created)
// geom_description		-	the coordinate axis, x or y, being addressed (used to 
//							communicate	this information to the user)
//
// bool return used to process user entered Ctrl-Z to quit the programme
// if user enters Ctrl-Z, then return to main function to cleanup and close the programme
//

#include <iostream>
#include <limits>			// used to clear invalid input

using namespace std;

bool user_input(double& geom_value, const string& geom_id, const string& geom_description)
{
	// loop until valid user input, or, quit if Ctrl-Z entered
	while ((cout << "Enter " << geom_description << " value for " << geom_id << " (Ctrl-Z to quit): ")
		&& !(cin >> geom_value) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit
		{
			cout << "\nExiting. Bye...\n";
			return true;
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}

	return false;
}
