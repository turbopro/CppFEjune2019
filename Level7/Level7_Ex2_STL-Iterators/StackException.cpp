/* StackException.cpp
Level7_Ex2: Overview of the Standard Template Library - STL Iterators

Source file that implements the StackException class declared in the
StackException.h header file.

All constructors and the destructor made inline in the StackException.h
class declaration file

The sstream and string libraries are used to convert the data member to
its string representation

The StackException class, StackFullException and StackEmptyException derived
classes are part of the Turbopro::Containers namespace

*/

#include <iostream>
#include <string>				// for std::string() function in ToString() member function
#include <sstream>				// for std::ostringstream() function in GetMessage() method
#include "StackException.h"		// Array class declaration

// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// StackFullException::GetMessage() method
		std::string Containers::StackFullException::GetMessage() const
		{
			return "Error: Stack is full. Push aborted.\n";
		}

		// StackEmptyException::GetMessage() method
		std::string Containers::StackEmptyException::GetMessage() const
		{
			return "Error: Empty Stack. Pop aborted.\n";
		}
	}
}