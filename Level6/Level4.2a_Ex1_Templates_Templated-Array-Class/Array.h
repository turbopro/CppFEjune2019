/* Array.h
Level4.2a_Ex1: Introduction to Templates - Templated Array Class
 
header file for the Templated Array class

Our Templated Array class has three private data members:
· a dynamic array of templated TArray objects
· an integer for the size of the array
· and an enum for the size of the default constructor

We will transform our Array class to a templatised Array class so that
we may use it as a general purpose containers for several types of
objects: e.g., numeric objects, string objects, other array objects

The array will have:

· Default constructor (allocate 10 elements; store value as static data member)
· Constructor
· Copy constructor
· Destructor
· Size method
· Assignment operator
· Getter method
· Setter method

"   [T]ransform the Array class for points created earlier into a template class:

	In the header file, declare the Array class as a template of type T.
	Replace all references to Point with T.
	Where an array is used as input or output, replace Array by Array<T>.
	In the source file, every function must be declared as a template of type T.
	The functions are now not a member of Array anymore but a member of Array<T>.
	Further replace all references to Point with T.
	Finally where an array is used as input or output, replace Array by Array<T>.
	Don’t forget that the program should now include the source file instead of
	the header file. Therefore, the source file should now also include
	#ifndef/#define/#endif statements.
"

"Add a source - and header file for the Array class to your current project.
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
"

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_data		-	type TArray*
m_arr_size	-	type int
ArraySize	-	type enum

METHODS:
...

public members:
DATA:
...

METHODS:
Array()					-	default constructor
Array(int arr_size)		-	constructor
Array(const Point&)		-	copyconstructor
~Array()				-	destructor
operator=()				-	overloaded assignment operator=
Size()					-	return the size of the array
SetElement()			-	sets an element in the array
GetElement()			-	return an element; return by reference
							(return first element if index out of bounds)
operator[]				-	return a reference so the [] operator reads/writes
							return first element if index is out of bounds

the Array Tempalte class is part of the Turbopro::Containers namespace

*/

#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// Template Array class declaration
		template <typename T>
		class Array
		{
		private:
			T* m_data;
			unsigned int m_arr_size;		// array size should be positive only: set to unsigned int

			enum { ArraySize = 10 };		// size of array for default constructor

		public:
			Array();													// default constructor
			Array(unsigned int arr_size);								// constructor
			Array(const Array<T>& Other);								// copy constructor
			virtual ~Array();											// destructor
			unsigned int Size() const { return m_arr_size; }			// inlined: return the size of the object's array
			void SetElement(const T& p, unsigned int index);			// set a Point element to the array
			T& GetElement(unsigned int index) const;					// return a Point element from the array
			Array<T>& operator=(const Array<T>& Other);					// overloaded assignment operator
			T& operator[](unsigned int index);							// overloaded array indexing operator
			const T& operator[](unsigned int index) const;				// overloaded array indexing operator: const version
		};
	}
}

// include Array.cpp implementation source file for Template class
#ifndef Array_cpp // Must be the same name as in source file #define
#include "Array.cpp"
#endif

#endif // ARRAY_H_INCLUDED
