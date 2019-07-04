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
· Assignment operator
· Length

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:

METHODS:
...

public members:
DATA:
...

METHODS:
PointArray()					-	default constructor
PointArray(int arr_size)		-	constructor
PointArray(const Point&)		-	copyconstructor
~PointArray()					-	destructor
operator=()						-	overloaded assignment operator=
Length()						-	return the size of the array

the Array class is part of the Turbopro::Containers namespace

*/

#ifndef POINTARRAY_H_INCLUDED
#define POINTARRAY_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include "Array.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// Template PointArray class declaration
		template <typename Point>
		class PointArray : public Array<Point>
		{
		private:
			//Point m_p;
		public:
			PointArray();										// default constructor
			PointArray(int arr_size);							// constructor
			PointArray(const PointArray<Point>& Other);			// copy constructor
			~PointArray();										// destructor

			// overloaded assignment operator
			PointArray<Point>& operator=(const PointArray<Point>& Other);

			// PointArray specific methods
			// total length between the points in the PointArray
			double Length() const;
			// add the Points of two PointArrays
			PointArray<Point> operator+(const PointArray<Point>& Other) const;
			// scale the Points of the PointArray by factor n
			PointArray<Point> operator*(double n) const;
		};
	}
}

// include Array.cpp implementation source file for Template class
#ifndef PointArray_cpp // Must be the same name as in source file #define
#include "PointArray.cpp"
#endif

#endif // POINTARRAY_H_INCLUDED
