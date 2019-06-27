/* Line.cpp
Level3.4_Ex2: Simple Inheritance: Creating Shape Base Class

Source file that implements the Line class declared in the 
Line.h header file.

constructor uses the colon initialiser
default constructor also uses the colon initialiser
copy constructor also uses the colon initialiser
destructor

All Getter/Setter functions inlined within Line.h
 
The ToString() function makes use of the ToString() function of the
constituent points of the Line

The Length() function makes use of the Point::Distance(const Point&) function 

The overloaded operator=() allows for Line a = Line b syntax, and checks for
self assignment

The overloaded ostream operator<<() allows for passing the Line object to an
ostream object, which includes cout for displaying the Line object
 
the Line class is part of the Turbopro::CAD namespace

*/

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Line.h"			// Line class declaration

// create namesapce
namespace Turbopro
{
	namespace CAD
	{
		// constructor using colon syntax initialiser
		Line::Line(const Point& startpoint, const Point& endpoint)
			: Shape {}, m_startpoint{ startpoint }, m_endpoint{ endpoint } {}

		// default constructor
		Line::Line() : Shape{}, m_startpoint{ Point{ 0, 0 } }, m_endpoint{ Point{ 0, 0 } } {}

		// copy constructor
		Line::Line(const Line& Other) 
			: Shape{ Other }, m_startpoint{ Other.m_startpoint }, m_endpoint{ Other.m_endpoint } {}

		// Destructor
		Line::~Line() {}

		// ToString() 
		// use Point::ToString() of the Point objects
		std::string Line::ToString() const
		{
			// get string representation of base Shape object
			std::string s = Shape::ToString();

			return ("Line" + s + " => (Start" + m_startpoint.ToString() +
				", End" + m_endpoint.ToString() + ")");
		}

		// Length()
		// use Point::Distance(const Point&) function to calculate line length
		double Line::Length() const
		{
			return m_startpoint.Distance(m_endpoint);
		}

		// overloaded operator methods
		// assignment operator
		Line& Line::operator=(const Line& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				Shape::operator=(Other);
				m_startpoint = Other.m_startpoint;
				m_endpoint = Other.m_endpoint;
				return *this;
			}
		}

		// overloaded ostream operator <<
		std::ostream& operator<<(std::ostream& os, const Line& l)
		{
			return os << "Line with startpoint: " << l.m_startpoint
				<< ", and endpoint: " << l.m_endpoint;
		}
	}
}