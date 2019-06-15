// Line.C
// Level2.3_Ex6
//
// Source file that implements the Line class declared in the 
// Line.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// Getter functions are overloaded functions
// Both return const references to Point objects; class members cannot be changed
//
// Setter functions are overloaded functions
// Both have const references to Point object arguments; the arguments are read-only 
// and cannot be changed by the function
// 
// The ToString() function makes use of the ToString() function of the
// constituent points of the Line
//
// The Length() function makes use of the Point::Distance(const Point&) function 
//

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Point.h"			// Point class declaration
#include "Line.h"			// Line class declaration

// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint.X(), startpoint.Y() }, m_endpoint{ endpoint.X(), endpoint.Y() }
{
	//std::cout << "Waa! Waa! new Line 'constructor'\n";
}

// default constructor using colon syntax initialiser
Line::Line() : m_startpoint(0, 0), m_endpoint(0, 0)
{
	//std::cout << "Waa! Waa! new Line 'default constructor'\n";
}

// copy constructor using colon syntax initialiser
Line::Line(const Line& Other) : m_startpoint(Other.m_startpoint), m_endpoint(Other.m_endpoint)
{
	//std::cout << "Can you tell I'm a Line 'copy constructor'\n";
}

// (verbose) Destructor definition
Line::~Line()
{
	//std::cout << "RIP: " << this->ToString() << std::endl;
}

// StartPoint() getter function definition
const Point& Line::StartPoint() const
{
	return m_startpoint;
}

// EndPoint() getter function definition 
const Point& Line::EndPoint() const
{
	return m_endpoint;
}

// StartPoint() setter function definition
void Line::StartPoint(const Point& newP)
{
	m_startpoint = newP;
}

// EndPoint() setter function definition
void Line::EndPoint(const Point& newP)
{
	m_endpoint = newP;
}

// ToString() definition
// use Point::ToString() of the Point objects
std::string Line::ToString() const
{
	// create stream objects for conversion
	// input Line object's startpoint & endpoint x & y coordinates
	return ("startpoint: " + m_startpoint.ToString() +
		", and endpoint: " + m_endpoint.ToString());
}

// Length() definition
// use Point::Distance(const Point&) function to calculate length
double Line::Length() const
{
	return m_startpoint.Distance(m_endpoint);
}

