// Line.C
// Level2.3_Ex5
//
// Source file that implements the Line class declared in the 
// Line.h header file.  
// The string in the ToString() function, requires conversion of 
// the double coordinates to a string.  We use a std::stringstream 
// object, and the standard stream operators (as with iostream) to 
// create the string.  This requires the “sstream” header file. 
// Use the str() function to retrieve the string from the string 
// buffer.  
// The retrun format : “Point(1.5, 3.9)”
//

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function in Distance()
#include "Point.h"			// Point class declaration
#include "Line.h"			// Line class declaration


// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint }, m_endpoint{ endpoint }
{
	//m_startpoint = startpoint;
	//m_endpoint = endpoint;

	std::cout << "Waa! Waa! new Line 'constructor'\n";
}

// default constructor using colon syntax initialiser
Line::Line() : m_startpoint(0, 0), m_endpoint(0, 0)
{
	std::cout << "Waa! Waa! new Line 'default constructor'\n";
}

// copy constructor using colon syntax initialiser
Line::Line(const Line& Other) : m_startpoint(Other.m_startpoint), m_endpoint(Other.m_endpoint)
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
	// create stream objects for conversion
	// input Line object's startpoint & endpoint x & y coordinates
	return ( "startpoint: " + m_startpoint.ToString() +
		", and endpoint: " + m_endpoint.ToString() );
}

// Length() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Line::Length() const
{
	return m_startpoint.Distance(m_endpoint);
}

