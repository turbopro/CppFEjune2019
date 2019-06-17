// Line.cpp
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
// Constructors and destructor no longer verbose
//

#include <string>			// for std::string() function in ToString() member function
#include "Line.h"			// Line class declaration

// : m_startpoint{ startpoint.X(), startpoint.Y() }, m_endpoint{ endpoint.X(), endpoint.Y() }
// updated after grading; see relevant post in the forum for this HW
// https://quantnet.com/threads/level-3-hw-vernon-woolford.39463/#post-248880
// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint }, m_endpoint{ endpoint }
{
}

// Line::Line() : m_startpoint(0, 0), m_endpoint(0, 0)
// default constructor using colon syntax initialiser
Line::Line() : m_startpoint( Point{ 0, 0 } ), m_endpoint( Point{ 0, 0 } )
{
}

// copy constructor using colon syntax initialiser
Line::Line(const Line& Other) : m_startpoint(Other.m_startpoint), m_endpoint(Other.m_endpoint)
{
}

// Destructor definition
Line::~Line()
{
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

