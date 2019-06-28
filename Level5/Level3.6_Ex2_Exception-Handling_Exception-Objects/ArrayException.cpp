/* ArrayException.cpp
Level3.6_Ex2: Exception Handling - Exception Objects

Source file that implements the ArrayException class declared in the
ArrayException.h header file.


the ArrayException and OutOfBoundsException classes are part of the 
Turbopro::Container namespace

*/

#include <iostream>
#include <string>				// for std::string() function in ToString() member function
#include "ArrayException.h"		// Array class declaration

// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructor OutOfBoundsException
		OutOfBoundsException::OutOfBoundsException(int error_index) : m_error_index{ error_index } {}

		// default constructor
		OutOfBoundsException::OutOfBoundsException() : m_error_index{ 0 } {}

		// destructor
		OutOfBoundsException::~OutOfBoundsException()
		{
			std::cout << "destructor: OutOfBoundsException\n";
		}
		
		
		// GetMessage() method
		std::string OutOfBoundsException::GetMessage()const
		{
			// convert m_error_index to a string: use std::to_string()
			return ("Invalid index: " + std::to_string(m_error_index) +
				"\nIndex is out of range\n");
		}

	}
}