// UserInput.cpp
// Level2.3_Ex6
//
// Source file with definition for user_input()
//
// The function takes three (3) aarguments:
// geom_value			-	Reference to a variable to hold the value entered by the user 
// geom_id				-	The id of the point to be created
//							used to communicate to the user the id of the Point being created
// geom_description		-	The description of the value to be entered by the user
//							used to communicate	this information to the user
//
// The bool return value is used to indicate to the main function that the user entered 
// Ctrl-Z to quit the programme. The main function then goes through the proper cleanup and 
// closes the programme
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
		if (cin.eof())		// user entered Ctrl-Z to quit
		{
			cout << "\nExiting. Bye...\n";
			return true;
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear the rest of line entry
	}

	return false;
}
