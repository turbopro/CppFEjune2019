// UserInput.cpp
// Level2.3_Ex6
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

#include <iostream>
#include <limits>			// for user_input() function, used to clear invalid input

using namespace std;

void user_input(double& coord_value, const string& point_id, const string& axis)
{
	// loop until valid user input, or, quit if Ctrl-Z entered
	while ((cout << "Enter " << axis << "-coordinate value for " << point_id << " (Ctrl-Z to quit): ")
		&& !(cin >> coord_value) || cin.peek() != '\n')
	{
		if (cin.eof())		// quit
		{
			cout << "\nExiting. Bye...\n";
			exit(0);
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear rest of line entry
	}
}
