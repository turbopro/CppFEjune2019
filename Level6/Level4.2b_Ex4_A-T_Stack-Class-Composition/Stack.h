/* Stack.h
Level4.2b_Ex4: Advanced Templates - Stack Class (composition)

header file for the Stack class

Our Stack class is composed of an Array

"In this exercise we will make a Stack class. For the data storage we 
can use the Array class. Deriving from Array is not a good idea because 
there is no relation between Array and Stack. The stack would then 
inherit indexed operations which should not be a functionality of a 
stack. But we can use the Array class as a data member as shown in Figure 4:

	Add a new source and header file for the Stack class to your project.
	Create a template class called Stack. It is not a derived class but 
	it uses an Array as data member. You also need a data member for the 
	current index in the array. Create the regular constructors, destructor 
	and assignment operator. Add a Push() function. It should store the 
	element at the current position in the embedded array. Increment the 
	current position afterwards. There is no need for checking the current 
	index because the array will throw an exception when the stack is full. 
	Make sure the current index is not changed when the Array class threw 
	an exception. Add a Pop() function that decrements the current position 
	and then returns the element at that position. Make sure the current 
	index is not changed when the Array class throws an exception.
	Change the main function to test the stack.

"
We include the following public functionality
· Default constructor (allocate 10 elements)
· Constructor
· Copy constructor
· Destructor
· GetIndex
· Size
· Assignment operator
· Push
· Pop

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:

m_array		-	type Array
m_current	-	type int

METHODS:
...

public members:
DATA:
...

METHODS:
Stack()					-	default constructor
Stack(Array, int)		-	constructor
Stack(const Stack&)		-	copyconstructor
~Stack()				-	destructor
GetSize()				-	get Array Size
SetSize()				-	set Array Size
GetIndex()				-	get Array index
operator=()				-	overloaded assignment operator=
Push()					-	add element to the stack
Pop()					-	remove element from the stack

the Stack class is part of the Turbopro::Containers namespace

*/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include "Array.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// Stack class declaration
		template <typename TStack, int sz>
		class Stack
		{
		private:
			Array<TStack> m_array;
			int m_index;

		public:
			Stack();									// default constructor
			//Stack(const Array<TStack>& arr);			// constructor
			Stack(const Stack& Other);					// copy constructor
			~Stack();									// destructor
			int Size() const { return m_array.Size(); }	// size of Array
			Stack& operator=(const Stack& Other);		// overloaded assignment operator
			int GetIndex() const { return m_index; }	// get Stack index
			//void SetIndex(int index);					// get Stack index
			TStack pop();								// remove element from Stack
			void push(const TStack& ele);				// add element to Stack
		};
	}
}

// include Array.cpp implementation source file for Template class
#ifndef Stack_cpp // Must be the same name as in source file #define
#include "Stack.cpp"
#endif

#endif // STACK_H_INCLUDED
