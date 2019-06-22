/* Circle.cpp
Level2.6_Ex1: Namespaces: CAD and Container Namespaces

Source file that implements the Circle class declared in the 
Circle.h header file.

constructor uses the colon initialiser
default constructor also uses the colon initialiser
copy constructor also uses the colon initialiser
destructor

Getter/Setter functions inlined within Circle.h

The ToString() function converts the radius member to a string, and concatenates this with
the string values output from the ToString() function of the centrepoint member

The Diameter(), Circumference() and Area() functions all inlined within Circle.h

The overloaded operator=() allows for Circle a = Circle b syntax, and checks for
self assignment

The overloaded ostream operator<<() allows for passing the Circle object to an
ostream object, which includes cout for displaying the Circle object

the Circle class is part of the Turbopro::CAD namespace

*/

#define _USE_MATH_DEFINES	// for PI; must be placed here even for inline 
							// functions, Circumference() and Area() in Circle.h

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for M_PI (pi); see comment above for _USE_MATH_DEFINES
#include "Point.h"			// Point class declaration
#include "Circle.h"			// Line class declaration

// create namespace
namespace Turbopro
{
	namespace CAD
	{
		// constructor using colon syntax initialiser
		Circle::Circle(const double& radius, const Point& centrepoint)
			: m_radius{ radius }, m_centrepoint{ centrepoint } {}

		// default constructor
		Circle::Circle() : m_radius{ 0.0 }, m_centrepoint{ Point{ 0, 0 } } {}

		// copy constructor
		Circle::Circle(const Circle& Other)
			: m_radius{ Other.m_radius }, m_centrepoint{ Other.m_centrepoint } {}

		// Destructor definition
		Circle::~Circle() {}

		// ToString() definition
		// use Point::ToString() to print Point object values
		std::string Circle::ToString() const
		{
			// convert Circle object's radius to a string
			std::ostringstream m_radius_conv;
			m_radius_conv << m_radius;
			std::string str_m_radius = m_radius_conv.str();

			return ("Circle with radius: " + str_m_radius +
				", and centrepoint: " + m_centrepoint.ToString());
		}

		// overloaded operator methods
		// assignment operator
		Circle& Circle::operator=(const Circle& Other)
		{
			const Circle* p_other = &Other;
			if (this == p_other)
			{
				std::cout << "Attempting to self assign:\n" << this->ToString()
					<< " at memory address: " << this << " to\n"
					<< Other.ToString() << " at same address: "
					<< p_other << "\n" << "Self assignment is not allowed\n"
					<< "Assignment aborted\n"
					<< this->ToString() << " is unchanged\n";
				return *this;
			}
			else
			{
				m_radius = Other.m_radius;
				m_centrepoint = Other.m_centrepoint;
				return *this;
			}
		}

		// overloaded ostream operator <<
		std::ostream& operator<<(std::ostream& os, const Circle& c)
		{
			return os << "Circle with radius: " << c.m_radius
				<< ", and centrepoint: " << c.m_centrepoint;
		}
	}
}