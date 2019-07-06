/* PointArray.h
Level4.2b_Ex4: Advanced Templates - Stack Class (composition)

header file for the PointArray class

Our PointArray class is derived from the Array Class with concrete
inheritance

In this exercise we will create a PointArray which is derived from 
Array with the template argument set to Point.

	Add a new source and header file for the PointArray class to 
	your project.  	Create a regular class called PointArray which 
	is derived from Array. The template argument given to Array is 
	Point.  Since they are not inherited, create proper constructors, 
	destructor and assignment operator and call the base class where 
	appropriate.  Now we can add functionality specific for a point 
	array. For example add a Length() function that returns the 
	total length between the points in the array.  Change the main 
	program to test the point array.
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
		public:
			PointArray();										// default constructor
			PointArray(int arr_size);							// constructor
			PointArray(const PointArray<Point>& Other);			// copy constructor
			~PointArray();										// destructor
			
			// overloaded assignment operator
			PointArray<Point>& operator=(const PointArray<Point>& Other);		

			// PointArray specific methods
			double Length() const;								// total length between the points in the PointArray
			PointArray<Point> operator+(const PointArray<Point>& Other) const;	// add the Points of two PointArrays
			PointArray<Point> operator*(double n) const;		// scale the Points of the PointArray by factor n
		};
	}
}

// include Array.cpp implementation source file for Template class
#ifndef PointArray_cpp // Must be the same name as in source file #define
#include "PointArray.cpp"
#endif

#endif // POINTARRAY_H_INCLUDED
