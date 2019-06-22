// Line.cpp
// Level2.4_Ex4: Friends
//
// Source file that implements the Line class declared in the 
// Line.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// All Getter/Setter functions inlined within Line.h
// 
// The ToString() function makes use of the ToString() function of the
// constituent points of the Line
//
// The Length() function makes use of the Point::Distance(const Point&) function 
//

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Line.h"			// Line class declaration

// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint }, m_endpoint{ endpoint } {}

// default constructor
Line::Line() : m_startpoint{ Point{ 0, 0 } }, m_endpoint{ Point{ 0, 0 } } {}

// copy constructor
Line::Line(const Line& Other) : m_startpoint{ Other.m_startpoint }, m_endpoint{ Other.m_endpoint } {}

// Destructor
Line::~Line() {}

// ToString() 
// use Point::ToString() of the Point objects
std::string Line::ToString() const
{
	return ("Line with startpoint: " + m_startpoint.ToString() +
		", and endpoint: " + m_endpoint.ToString());
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
	const Line* p_other = &Other;
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