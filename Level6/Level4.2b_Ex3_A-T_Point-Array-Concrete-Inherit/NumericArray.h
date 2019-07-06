/* NumericArray.h
Level4.2b_Ex3: Advanced Templates - Point Array (concrete inheritance)

header file for the Templated NumericArray class

Our Templated NumericArray class has a private member for a dynamic C array of Point objects
and another private member for an integer for the size of the array
We include the following public functionality
· Default constructor (allocate 10 elements)
· Constructor
· Copy constructor
· Destructor
· Assignment operator

Add a source - and header file for the Array class to your current project.
Add a data member for a dynamic C array of Point objects(Point* m_data).
Add a data member for the size of the array.
Add a default constructor that allocates for example 10 elements.
Add a constructor with a size argument.The implementation should allocate
the number of elements specified by the size input argument.
Add a copy constructor.Keep in mind that just copying the C array pointer
will create an Array object that shares the data with the original Array
object.Thus you need to allocate a new C array with the same size and
copy each element separately.
Add a destructor.It should delete the internal C array.Don’t forget the
square brackets.
Add an assignment operator. Keep in mind you can’t copy only the C array
pointers just as in the case of the copy constructor.
Also don’t forget to delete the old C array and allocate new memory before
copying the elements.This is because C arrays can’t grow.

Further check if the source object is not the same as the this object. If
you don’t check it, then a statement like arr1 = arr1 will go wrong.The
internal C array will then be deleted before it is copied.

Add a Size() function that returns the size of the array.
Add a SetElement() function that sets an element.When the index is out of
bounds, ignore the “set”.We will add better error handling later.
Add a GetElement() function.You can return the element by reference since
the returned element has a longer lifetime than the GetElement() function.
When the index is out of bounds, return the first element.We will add
better error handling later.
You can also add a square bracket operator. Return a reference so the []
operator can be used for both reading and writing elements.When the index
is out of bounds, return the first element.We will add better error
handling later.Point & operator [] (int index);
In the main program, test the Array class.


Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_data		-	type Point*
m_arr_size	-	type int


METHODS:
...

public members:
DATA:
...

METHODS:
Array()					-	default constructor
Array(int arr_size)		-	constructor
Array(const Point&)		-	copyconstructor
~Point()				-	destructor
operator=()				-	overloaded assignment operator=
Size()					-	return the size of the array
SetElement()			-	sets an element in the array
GetElement()			-	return an element; return by reference
							(return first element if index out of bounds)
operator[]				-	return a reference so the [] operator reads/writes
							return first element if index is out of bounds

operator=()				-	overloaded assignment operator
operator<<()			-	overloaded ostream operator <<

the Array class is part of the Turbopro::Containers namespace

*/

#ifndef NUMERICARRAY_H_INCLUDED
#define NUMERICARRAY_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include "Array.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// Template NumericArray class declaration
		template <typename TNum>
		class NumericArray	:	public Array<TNum>
		{
		private:

		public:
			NumericArray();											// default constructor
			NumericArray(int arr_size);								// constructor
			NumericArray(const NumericArray<TNum>& Other);			// copy constructor
			virtual ~NumericArray();								// destructor
			NumericArray<TNum>& operator=(const NumericArray<TNum>& Other);		// overloaded assignment operator
			
			// NumericArray specific methods
			NumericArray<TNum> operator+(const NumericArray<TNum>& Other) const; // add the elements of two NumericArrays
			NumericArray<TNum> operator*(double n) const;						// scale the elements of the NumericArray by factor n
			TNum DotProd(const NumericArray<TNum>& Other) const;				// 
		};
	}
}

// include Array.cpp implementation source file for Template class
#ifndef NumericArray_cpp // Must be the same name as in source file #define
#include "NumericArray.cpp"
#endif

#endif // NUMERICARRAY_H_INCLUDED
