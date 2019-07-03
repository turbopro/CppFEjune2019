/* Shape.cpp
Level4.2b_Ex3: Advanced Templates - Point Array (concrete inheritance)

Source file that implements the Shape class declared in the
Shape.h header file.

constructor uses the colon initialiser
default constructor also uses the colon initialiser
copy constructor also uses the colon initialiser
destructor

Getter method inlined within Shape.h

The ToString() function returns the ID of the Shape object

The overloaded operator=() allows for Shape a = Shape b syntax, and checks for
self assignment

the Shape class is part of the Turbopro::CAD namespace

*/

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
//#include <string>			// for std::string() function in ToString() member function
#include "Shape.h"			// Shape class declaration
#include <stdlib.h>			// for rand() function

// create namesapce
namespace Turbopro
{
	namespace CAD
	{
		// constructor using colon syntax initialiser
		Shape::Shape(int id_number)	: m_id_number{ id_number } {}

		// default constructor
		Shape::Shape() : m_id_number { rand() } {}

		// copy constructor
		Shape::Shape(const Shape& Other) : m_id_number { Other.m_id_number  } {}

		// Destructor
		Shape::~Shape() {}

		// ToString() 
		std::string Shape::ToString() const
		{
			// create stream objects for conversion of data member
			std::ostringstream m_id_number_conv;
			m_id_number_conv << m_id_number;

			// get str values for data member
			std::string str_m_id_number = m_id_number_conv.str();

			// return string with format: "ID: 123"
			return ("ID: " + str_m_id_number);
		}

		// overloaded operator methods
		// assignment operator
		Shape& Shape::operator=(const Shape& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				m_id_number = Other.m_id_number;
				return *this;
			}
		}

		// Print()
		void Shape::Print() const 
		{
			std::cout << this->ToString() << std::endl;
		}
	}
}
