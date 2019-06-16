// Point.cpp
// Level2.3_Ex6
//
// Source file that implements the Point class declared in the 
// Point.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// Getter functions are overloaded functions
// Both return const references to doubles; class members cannot be changed
//
// Setter functions are overloaded functions
// Both have const double arguments; the arguments are read-only 
// and cannot be changed by the function
// 
// The ToString() function converts the double values of the data members 
// to strings
// We use a std::stringstream object, and the standard stream operators 
// (as with iostream) to create the string.  This requires the “sstream” 
// header file. We also use the str() function to retrieve the string 
// from the string buffer.  
// The return format for ToString(): “Point(1.5, 3.9)”
//
// The overloaded Distance() function makes use of the Pythagoras theorem to 
// calculate the distance between the point and the origin, and, the distance
// between two points
//
// Constructors and destructor no longer verbose
//

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function in Distance()
#include "Point.h"			// Point class declaration

// constructor using colon syntax initialiser
Point::Point(double x_coord, double y_coord) : m_x{ x_coord }, m_y{ y_coord }
{
}

// default constructor using colon syntax initialiser
Point::Point() : m_x{ 0 }, m_y{ 0 }
{
}

// copy constructor using colon syntax initialiser
Point::Point(const Point& Other) : m_x{ Other.m_x }, m_y{ Other.m_y }
{
}

// (verbose) Destructor definition
Point::~Point()
{
}

// X() definition for x getter
const double& Point::X() const
{
	return m_x;
}

// Y() definition for y getter 
const double& Point::Y() const
{
	return m_y;
}

// X() definition for x setter
void Point::X(const double& newX)
{
	m_x = newX;
}

// Y() definition for y setter
void Point::Y(const double& newY)
{
	m_y = newY;
}

// ToString() definition
std::string Point::ToString() const
{
	// create stream objects for conversion
	// input Point object's x & y coordinates
	std::ostringstream m_x_conv, m_y_conv;
	m_x_conv << m_x;
	m_y_conv << m_y;

	// get str values for data members
	std::string str_m_x = m_x_conv.str();
	std::string str_m_y = m_y_conv.str();

	// return string with format: "Point(x, y)"
	return ("Point(" + str_m_x + ", " + str_m_y + ")");
}

// Distance() definition with no arguments
// formula: sqrt((Point.x)^2 + (Point.y)^2)
double Point::Distance() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}

// Distance() definition between two points
// formula: sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
double Point::Distance(const Point& p) const
{
	return std::sqrt((p.m_x - m_x) * (p.m_x - m_x) + (p.m_y - m_y) * (p.m_y - m_y));
}
