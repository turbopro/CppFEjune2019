/* ArrayException.cpp
Level4.2b_Ex4: Advanced Templates - Stack Class (composition)

Source file that implements the ArrayException class declared in the
ArrayException.h header file.

All constructors and the destructor use the colon syntax initialisation

The sstream and string libraries are used to convert the data member to 
its string representation

The ArrayException and OutOfBoundsException classes are part of the 
Turbopro::Containers namespace

*/

#include <iostream>
#include <string>				// for std::string() function in ToString() member function
#include <sstream>				// for std::ostringstream() function in GetMessage() method
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
		OutOfBoundsException::~OutOfBoundsException() {}

		// constructor SizeMismatchException
		SizeMismatchException::SizeMismatchException(int size_mismatch) : m_size_mismatch{ size_mismatch } {}

		// default constructor
		SizeMismatchException::SizeMismatchException() : m_size_mismatch{ 0 } {}

		// destructor
		SizeMismatchException::~SizeMismatchException() {}

		// OutOfBoundsException::GetMessage() method
		std::string OutOfBoundsException::GetMessage() const
		{
			// create stream objects for conversion of data members
			std::ostringstream m_error_index_conv;
			m_error_index_conv << m_error_index;

			// get str values for data members
			std::string str_m_error_index_conv = m_error_index_conv.str();

			return ("Invalid index: " + str_m_error_index_conv +
				"\nIndex is out of range\n");

			// alternative: convert m_error_index to a string using std::to_string()
			//return ("Invalid index: " + std::to_string(m_error_index) +
				//"\nIndex is out of range\n");
		}

		// SizeMismatchException::GetMessage() method
		std::string SizeMismatchException::GetMessage() const
		{
			return "Error: Array Size Mismatch\nArrays must be of same size\n";
		}


	}
}