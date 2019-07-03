/* ArrayException.h
Level4.2b_Ex3: Advanced Templates - Point Array (concrete inheritance)

header file for the ArrayException class

Our ArrayException class supports an exception hierarchy with an ArrayException 
base class and an OutOfBoundsException derived class
We implement both exception classes in this header file for simplicity

The ArrayException has an abstract GetMessage() function that returns a std::string
The OutOfBoundsException class has a constructor with an int as argument that 
indicates the erroneous array index and store it in a data member
We override the GetMessage() function and let the implementation return a message 
string saying the given index is out of bounds

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
...

METHODS:
...

public members:
DATA:
...

METHODS:
ArrayException()		-	default constructor
~ArrayException()		-	destructor
GetMessage()			-	abstract method

the ArrayException class is part of the Turbopro::Containers namespace

*/

#ifndef ARRAYEXCEPTION_H_INCLUDED
#define ARRAYEXCEPTION_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// ArrayException class declaration: abstract base class (ABC)
		class ArrayException
		{
		private:
			
		public:
			ArrayException() {};							// do-nothing default constructor
			virtual ~ArrayException() {};					// destructor
			virtual std::string GetMessage() const = 0;		// pure virtual function: returns a string
		};

		// OutOfBoundsException class to handle array indexing errors
		class OutOfBoundsException : public ArrayException
		{
		private:
			int m_error_index;

		public:
			OutOfBoundsException();							// default constructor
			OutOfBoundsException(int error_index);			// constructor
			virtual ~OutOfBoundsException();				// destructor
			virtual std::string GetMessage() const;			// getter method
		};

		// SizeMismatchException class to handle size mismatch between Arrays
		class SizeMismatchException : public ArrayException
		{
		private:
			int m_size_mismatch;

		public:
			SizeMismatchException();						// default constructor
			SizeMismatchException(int size_mismatch);		// constructor
			virtual ~SizeMismatchException();				// destructor
			virtual std::string GetMessage() const;			// getter method
		};
	}
}
#endif // ARRAYEXCEPTION_H_INCLUDED
