/* Point.cpp
Level3.5_Ex3: Polymorphism: Virtual Destructors

Source file that implements the Point class declared in the 
Point.h header file.

constructor uses the colon initialiser
default constructor also uses the colon initlaiser
copy constructor same as above
destructor is also verbose

All Getter/Setter functions have been inlined within Point.h
 
The ToString() function converts the double values of the data members 
to strings
We use a std::stringstream object, and the standard stream operators 
(as with iostream) to create the string.  This requires the “sstream” 
header file. We also use the str() function to retrieve the string 
from the string buffer.  
The return format for ToString(): “Point(1.5, 3.9)”

The overloaded Distance() function makes use of the Pythagoras theorem to 
calculate the distance between the point and the origin, and, the distance
between two points

the Point class is part of the Turbopro::CAD namespace

*/

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function in Distance()
#include "Point.h"			// Point class declaration

namespace Turbopro
{
	namespace CAD
	{
		// constructor using colon syntax initialiser
		Point::Point(double x_coord, double y_coord) : Shape{}, m_x{ x_coord }, m_y{ y_coord }
		{
			//std::cout << "POINT: param constructor\n";
		}

		// single argument constructor using colon syntax initialiser
		// this constructor is used as an implicit conversion operator
		Point::Point(double uni_coord) : Shape{}, m_x{ uni_coord }, m_y{ uni_coord } {}

		// default constructor
		Point::Point() : Shape{}, m_x { 0 }, m_y{ 0 } {}

		// copy constructor
		Point::Point(const Point& Other) : Shape{ Other } , m_x { Other.m_x }, m_y{ Other.m_y } {}

		// Destructor
		Point::~Point()
		{
			std::cout << "Deleting: " << this->ToString() << " ..." << std::endl;
		}

		// ToString()
		std::string Point::ToString() const
		{
			// get string representation of base Shape object
			std::string s = Shape::ToString();

			// create stream objects for conversion of data members
			std::ostringstream m_x_conv, m_y_conv;
			m_x_conv << m_x;
			m_y_conv << m_y;

			// get str values for data members
			std::string str_m_x = m_x_conv.str();
			std::string str_m_y = m_y_conv.str();

			// return string with format: "Point(x, y)"
			return ("Point" + s + " => Point(" + str_m_x + ", " + str_m_y + ")");
		}

		// Distance() point from origin
		double Point::Distance() const
		{
			return std::sqrt(m_x * m_x + m_y * m_y);
		}

		// Distance() between two points
		double Point::Distance(const Point& Other) const
		{
			return std::sqrt((Other.m_x - m_x) * (Other.m_x - m_x) +
				(Other.m_y - m_y) * (Other.m_y - m_y));
		}

		// assignment operator: check for self assignment
		Point& Point::operator=(const Point& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				Shape::operator=(Other);
				m_x = Other.m_x;
				m_y = Other.m_y;
				//std::cout << "POINT: assigned\n";
				return *this;
			}
		}

		// scale the point by factor n, and assign
		Point& Point::operator*=(double n)
		{
			m_x *= n;
			m_y *= n;
			return *this;
		}

		// overloaded ostream operator <<
		std::ostream& operator<<(std::ostream& os, const Point& p)
		{
			return os << "Point(" << p.m_x << ", " << p.m_y << ")";
		}
	}
}