/* User_input.h
Level5.1_Ex3: Boost C++ Libraries - Variant

Header file with definition for user_input()

user_input():

The function takes three (3) arguments:
geom_value			-	Reference to a variable to hold the value entered by the user 
geom_id				-	The id of the point to be created
						used to communicate to the user the id of the Point being created
geom_description	-	The description of the value to be entered by the user
						used to communicate	this information to the user
Argument names updated to reflect more generic terms to include a variety of geometric objects

The bool return value is used to indicate to the main function that the user entered 
Ctrl-Z to quit the programme. The main function then goes through the proper cleanup and 
closes the programme
When the user enters Ctrl-Z, then user input is considered incomplete, and bool 'false'
is returned. If the user enters valid numbers, then the function returns bool 'true'

bool return value is used to intercept user entered Ctrl-Z to quit


user_input_array():

The function retrieves valid user input for the array size, a positive integer
Uses the same mechanics / tools as for user_input_geom()
Arguments:
unsigned int	-	array size should be a positive integer

*/

#ifndef USER_INPUT_H_INCLUDED
#define USER_INPUT_H_INCLUDED

#include <iostream>
#include <limits>			// used to clear invalid input

using namespace std;

// declaration for user_input_geom() function
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);

// declaration for user_input_array() function
bool user_input_array(unsigned int& array_size);

// definition for user_input_geom()
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description)
{
	// loop until valid user input, or, quit if Ctrl-Z entered
	while ((cout << "Enter " << geom_description << " value for " << geom_id << " (Ctrl-Z to quit): ")
		&& !(cin >> geom_value) || cin.peek() != '\n')
	{
		if (cin.eof())		// user entered Ctrl-Z to quit
		{
			cout << "\nExiting. Bye...\n";
			return false;	// user_input() did not complete, return false
		}
		cout << "Invalid entry: you must enter a valid number\n\n";
		cin.clear();		// clear error flag for next input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear the rest of line entry
	}
	return true;
}

// definition for user_input_array()
bool user_input_array(unsigned int& array_size)
{
	int temp_input;			// temporary store for user input: user input may be negative 
	while ( 1 )				// loop until user enters valid entry
	{
		cout << "Enter positive integer value for the size of the array (Ctrl-Z to quit): "; 
		if (cin >> temp_input && temp_input >= 0 && cin.get() == '\n')	// valid input
		{
			array_size = temp_input;	// set array_size to valid entry
			return true;
		}
		else if (cin.eof())		// user entered Ctrl-Z to quit
		{
			cout << "\nExiting. Bye...\n";
			return false;
		}
		else   // invalid entry: clear input, prompt user for valid input
		{
			cout << "Invalid entry: array size requires a positive integer value\n\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return false;
}
#endif // USER_INPUT_H_INCLUDED
