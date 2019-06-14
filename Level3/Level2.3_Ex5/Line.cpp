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
	: m_startpoint(startpoint), m_endpoint(endpoint)
{
	//m_startpoint.X(startpoint.X());
	//m_startpoint.Y(startpoint.Y());
	//m_endpoint.X(endpoint.X());
	//m_endpoint.Y(endpoint.Y());

	std::cout << "Waa! Waa! new 'constructor' Line\n";
}

// default constructor using colon syntax initialiser
Line::Line() : m_startpoint(0, 0), m_endpoint(0, 0)
{
	std::cout << "Waa! Waa! new 'default constructor' Line\n";
}

// copy constructor using colon syntax initialiser
Line::Line(const Line& Other) : m_startpoint(Other.m_startpoint), m_endpoint(Other.m_endpoint)
{
	std::cout << "Can you tell I'm a 'copy constructor' Line\n";
}

// (verbose) Destructor definition
Line::~Line()
{
	std::cout << "RIP: " << this->ToString() << std::endl;
}

// StartPoint() definition for startpoint getter
Point Line::StartPoint() const
{
	return m_startpoint;
}

// EndPoint() definition for endpoint getter 
Point Line::EndPoint() const
{
	return m_endpoint;
}

// StartPoint() definition for startpoint setter
void Line::StartPoint(Point newP)
{
	m_startpoint = newP;
}

// EndPoint() definition for endpoint setter
void Line::EndPoint(Point newP)
{
	m_endpoint = newP;
}

// ToString() definition
std::string Line::ToString() const
{
	// create stream objects for conversion
	// input Line object's startpoint & endpoint x & y coordinates
	std::ostringstream m_startpoint_x_conv, m_startpoint_y_conv,
		m_endpoint_x_conv, m_endpoint_y_conv;
	m_startpoint_x_conv << m_startpoint.X();
	m_startpoint_y_conv << m_startpoint.Y();
	m_endpoint_x_conv << m_endpoint.X();
	m_endpoint_y_conv << m_endpoint.Y();

	// get str values for startpoint & endpoint x & y coordinates
	std::string str_m_startpoint_x, str_m_startpoint_y,
		str_m_endpoint_x, str_m_endpoint_y;
	str_m_startpoint_x = m_startpoint_x_conv.str();
	str_m_startpoint_y = m_startpoint_y_conv.str();
	str_m_endpoint_x = m_endpoint_x_conv.str();
	str_m_endpoint_y = m_endpoint_y_conv.str();

	// return string with format: "Point(x, y)"
	return ( "Line: StartPoint(" + str_m_startpoint_x + ", " + str_m_startpoint_y + 
		") -|- EndPoint(" + str_m_endpoint_x + ", " + str_m_endpoint_y + ")" );
}

// Distance() definition with no arguments
// formula: sqrt((Point.x)^2 + (Point.y)^2)
double Line::Length() const
{
	return m_startpoint.Distance(m_endpoint);
}

/*
// Distance() definition between two points
// formula: sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
double Line::Distance(const Line& p) const
{
	return std::sqrt((p.m_x - m_x) * (p.m_x - m_x) + (p.m_y - m_y) * (p.m_y - m_y));
}
*/
