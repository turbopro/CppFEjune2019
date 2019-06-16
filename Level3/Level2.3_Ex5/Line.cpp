// Line.cpp
// Level2.3_Ex5
//
// Source file that implements the Line class declared in the 
// Line.h header file.
//
// We use verbose constructors and destructor for academic purposes
//
// No need anymore for <sstream> or <cmath> libraries; the Point
// class member functions do the hard work for the Line class member
// functions. "Point.h" included already in Line.h
//

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Line.h"			// Line class declaration

// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint.X(), startpoint.Y() }, m_endpoint{ endpoint.X(), endpoint.Y() }
{
	std::cout << "Waa! Waa! new Line 'constructor'\n";
}

// default constructor using colon syntax initialiser
Line::Line() : m_startpoint{ 0, 0 }, m_endpoint{ 0, 0 }
{
	std::cout << "Waa! Waa! new Line 'default constructor'\n";
}

// copy constructor using colon syntax initialiser
Line::Line(const Line& Other) 
	: m_startpoint{ Other.m_startpoint.X(), Other.m_startpoint.Y() }, 
	  m_endpoint{ Other.m_endpoint.X(), Other.m_endpoint.Y() }
{
	std::cout << "Can you tell I'm a Line 'copy constructor'\n";
}

// (verbose) Destructor definition
Line::~Line()
{
	std::cout << "RIP: " << this->ToString() << std::endl;
}

// StartPoint() definition for startpoint getter
const Point& Line::StartPoint() const
{
	return m_startpoint;
}

// EndPoint() definition for endpoint getter 
const Point& Line::EndPoint() const
{
	return m_endpoint;
}

// StartPoint() definition for startpoint setter
void Line::StartPoint(const Point& newP)
{
	m_startpoint = newP;
}

// EndPoint() definition for endpoint setter
void Line::EndPoint(const Point& newP)
{
	m_endpoint = newP;
}

// ToString() definition
// use Point::ToString() to print Point object values
std::string Line::ToString() const
{
	// concatenate string output from Point::ToString() function 
	// of the points of the line
	return ( "startpoint: " + m_startpoint.ToString() +
		", and endpoint: " + m_endpoint.ToString() );
}

// Length() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Line::Length() const
{
	return m_startpoint.Distance(m_endpoint);
}

