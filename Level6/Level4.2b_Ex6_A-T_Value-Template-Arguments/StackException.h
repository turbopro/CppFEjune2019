/* StackException.h
Level4.2b_Ex5: Advanced Templates - Layering Exceptions

header file for the StackException class

Our StackException class supports an exception hierarchy with a StackException
base class and an StackFullException and StackEmptyException derived class
We implement both exception classes in this header file for simplicity

The StackException has an abstract GetMessage() function that returns a std::string
The StackFullException class has a constructor with an int as argument that
indicates that the Stack is full, so no push() is possible; StackEmptyException has
a constructor with an int that indicates that the Stack is empty, so no pop() is
possible.  Store the int arguments as corresponding data members
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

#ifndef STACKEXCEPTION_H_INCLUDED
#define STACKEXCEPTION_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// StackException class declaration: abstract base class (ABC)
		class StackException
		{
		private:

		public:
			StackException() {};							// do-nothing default constructor
			virtual ~StackException() {};					// destructor
			virtual std::string GetMessage() const = 0;		// pure virtual function: returns a string
		};

		// StackFullException class to handle array indexing errors
		class StackFullException : public StackException
		{
		private:
			int m_stack_full;

		public:
			StackFullException() : m_stack_full{ 0 } {}		// inline default constructor
			StackFullException(int stack_full)				// inline constructor
				: m_stack_full{ stack_full } {}
			virtual ~StackFullException() {}				// inline destructor
			virtual std::string GetMessage() const;			// getter method
		};

		// SizeMismatchException class to handle size mismatch between Arrays
		class StackEmptyException : public StackException
		{
		private:
			int m_stack_empty;

		public:
			StackEmptyException() : m_stack_empty{ 0 } {}	// inline default constructor
			StackEmptyException(int stack_empty)			// inline constructor
				: m_stack_empty{ stack_empty } {}
			virtual ~StackEmptyException() {};				// inline destructor
			virtual std::string GetMessage() const;			// getter method
		};
	}
}
#endif // STACKEXCEPTION_H_INCLUDED

