/* STLHelperFunctions.h
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

header file for the Templated Array class

Our Templated Array class has three private data members:
· a dynamic array of templated TArray objects
· an integer for the size of the array
· and a static int for the size of the default constructor

We will make the templatised Array glass as generic as posible so
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
· Static Getter/Setter methods for the static data member

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
"
Static variables, which are shared between all instances of a class, behave
slightly different with templates. We are going to test this with a static
variable in the Array class that indicates the default array size when using
the default constructor.

	Add a static data member to the Array class indicating the default size.
	Initialise this static in the source file to a value.
	Also add static functions to set and get the default size.
	In the default constructor, use the static default size variable instead
	of a literal value to set the array size.

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
ArraySize	-	type static int

METHODS:
...

public members:
DATA:
...

METHODS:
Array<TArray>()					-	default constructor
Array<TArray>(int arr_size)		-	constructor
Array<TArray>(const Point&)		-	copyconstructor
~Array<TArray>()				-	destructor
operator=()						-	overloaded assignment operator=
Size()							-	return the size of the array
SetElement()					-	sets an element in the array
GetElement()					-	return an element; return by reference
									(return first element if index out of bounds)
operator[]						-	return a reference so the [] operator reads/writes
									return first element if index is out of bounds
DefaultSize()					-	overloaded Getter/Setter for static data member

the Array Tempalte class is part of the Turbopro::Containers namespace

*/

#ifndef STLHELPERFUNCTIONS_H_INCLUDED
#define STLHELPERFUNCTIONS_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// template functions
		// given that container may be large, pass by reference is preferred
		template <typename T>
		double Sum(const T& container)
		{
			double acc_sum = 0;				// initialise accumulator

			// set const_iterator, it, to end()
			// decrement it, and check if == begin()
			// dereference it and add to the accumulator
			// repeat until the loop terminates
			for (typename T::const_iterator it = container.end(); it-- != container.begin(); )
				acc_sum += *it;

			// alternative that takes care of setting correct iterator type, makes good use
			// of rbegin() and rend(), and no need for decrementing
			//for (auto it = container.rbegin(); it != container.rend(); it++)
			//	acc_sum += *it;

			return acc_sum;
		}

		// iterator is like a pointer; so as an argument, may be just as ok to pass by value
		template <typename T>
		double Sum(const typename T start_it, const typename T end_it)
		{
			double acc_sum = 0;			// initialise accumulator

			// set type T iterator, it, to start_it
			// dereference it and add to the accumulator
			// increment it
			// repeat until the loop terminates
			for (T it = start_it; it != end_it; it++)
				acc_sum += *it;

			return acc_sum;
		}
		
		// is_less_than()
		bool is_less_than(double value)
		{
			return (value < 35 ? true : false);
		}
		
		class LessThan
		{
		private:
			double threshold;			// threshold level

		public:
			LessThan() : threshold{ 35 }					// default constructor
			~LessThan() {}									// destructor
			LessThan& operator()(const LessThan& Other);	// overloaded assignment operator: virtual, derived classes to change
			
		};
	}
}

#endif // STLHELPERFUNCTIONS_H_INCLUDED
