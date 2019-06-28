/* Shape.h
Level3.4_Ex2: Simple Inheritance: Creating Shape Base Class

header file for the Shape class

Our Shape class will serve as a base class for the CAD shapes

 � Add a data member for an id number of type int.
 � Add a default constructor that initializes the id using a random number.
	You can use the rand() function from the �stdlib.h� header file.
 � Add a copy constructor that copies the id member.
 � Add an assignment operator that copies the id member.
 � Add a ToString() function that returns the id as string e.g. �ID: 123�.
 � Add an ID() function the retrieve the id of the shape.
 � Next the Point and Line classes (and the Circle class if applicable) must derive from Shape.
 � Add the Shape class in the inheritance list of the Point, Line and the Circle class.
 � The constructors of the Point, Line and the Circle class should call the appropriate 
	constructor in the Shape base class.
 � The assignment operator should call the assignment operator of the Shape base class. 
	Otherwise the shape data will not be copied.
 � Finally add code to the main program to test inheritance:

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_id_number		-	type int

METHODS:
...

public members:
DATA:
...

METHODS:
Shape()						-	default constructor
Shape(int)					-	constructor
Shape(const Shape& Other)	-	copyconstructor
~Shape()					-	destructor
ID()						-	getter method for m_id_number
ToString()					-	returns a string representation of the Shapee object

operator=()					-	overloaded assignment operator
//operator<<()				-	overloaded ostream operator <<

the Shape class is part of the Turbopro::CAD namespace

*/

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <string>			// for return std::string in ToString() member function

// create namespace
namespace Turbopro
{
	namespace CAD
	{
		// Shape class declaration:	Base class
		class Shape
		{
		private:
			int m_id_number;

		public:
			Shape();											// default constructor
			Shape(int ID);										// constructor
			Shape(const Shape& Other);							// copy constructor
			~Shape();											// destructor
			int ID() const { return m_id_number; }				// inline Shape ID getter
			std::string ToString() const;						// print the Shape ID ("ID:123")

			// overloaded operator methods
			Shape& operator=(const Shape& Other);				// assignment operator
		};
	}
}

#endif // SHAPE_H_INCLUDED


