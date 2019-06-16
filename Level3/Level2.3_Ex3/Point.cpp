// Point.cpp
// Level2.3_Ex3
//
// Source file that implements the Point class declared in the 
// Point.h header file.  
// The string in the ToString() function, requires conversion of 
// the double coordinates to a string.  We use a std::stringstream 
// object, and the standard stream operators (as with iostream) to 
// create the string.  This requires the “sstream” header file. 
// Use the str() function to retrieve the string from the string 
// buffer.  
// The retrun format : “Point(1.5, 3.9)”
//
// Add constructor and copy constructor
// Also, all constructors and destructor are verbose; they anounce
// their births and deaths
//
// We now use const reference argument for Distance(const Point& p)
//
// Overloading getter/setter functions
//

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function in Distance()
#include "Point.h"			// Point class declaration


// constructor using colon syntax initialiser
Point::Point(double x_coord, double y_coord) : m_x(x_coord), m_y(y_coord)
{
	std::cout << "Waa! Waa! new 'constructor' Point\n";
}

// default constructor using colon syntax initialiser
Point::Point() : m_x(0), m_y(0)
{
	std::cout << "Waa! Waa! new 'default constructor' Point\n";
}

// copy constructor using colon syntax initialiser
Point::Point(const Point& p) : m_x(p.m_x), m_y(p.m_y)
{
	//m_x = p.m_x;
	//m_y = p.m_y;
	std::cout << "Can you tell I'm a 'copy constructor' Point\n";
}

// (verbose) Destructor definition
Point::~Point()
{
	std::cout << "RIP: " << this->ToString() << std::endl;
}

// X() definition for x getter
double Point::X() const
{
	return m_x;
}

// Y() definition for y getter 
double Point::Y() const
{
	return m_y;
}

// X() definition for x setter
void Point::X(double newX)
{
	m_x = newX;
}

// Y() definition for y setter
void Point::Y(double newY)
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

	// get str values for x & y coordinates
	std::string str_m_x, str_m_y;
	str_m_x = m_x_conv.str();
	str_m_y = m_y_conv.str();

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
