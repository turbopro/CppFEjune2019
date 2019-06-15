// Circle.cpp
// Level2.3_Ex6
//
// Source file that implements the Circle class declared in the 
// Circle.h header file.  
// The string in the ToString() function, requires conversion of 
// the double coordinates to a string.  We use a std::stringstream 
// object, and the standard stream operators (as with iostream) to 
// create the string.  This requires the “sstream” header file. 
// Use the str() function to retrieve the string from the string 
// buffer.  
// The retrun format : “Point(1.5, 3.9)”
//

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function, and PI (M_PI)
#include "Point.h"			// Point class declaration
#include "Circle.h"			// Line class declaration


// constructor using colon syntax initialiser
Circle::Circle(const double& radius, const Point& centrepoint)
	: m_radius{ radius }, m_centrepoint{ centrepoint }
{
	//m_radius = radius;
	//m_centrepoint = centrepoint;

	std::cout << "Waa! Waa! new Circle 'constructor'\n";
}

// default constructor using colon syntax initialiser
Circle::Circle() : m_radius(0.0), m_centrepoint(0, 0)
{
	std::cout << "Waa! Waa! new Circle 'default constructor'\n";
}

// copy constructor using colon syntax initialiser
Circle::Circle(const Circle& Other) : m_radius(Other.m_radius), m_centrepoint(Other.m_centrepoint)
{
	std::cout << "Can you tell I'm a Circle 'copy constructor'\n";
}

// (verbose) Destructor definition
Circle::~Circle()
{
	std::cout << "RIP: " << this->ToString() << std::endl;
}

// Radius() definition for radius getter
const double& Circle::Radius() const
{
	return m_radius;
}

// CentrePoint() definition for centrepoint getter 
const Point& Circle::CentrePoint() const
{
	return m_centrepoint;
}

// Radius() definition for radius setter
void Circle::Radius(const double& newR)
{
	m_radius = newR;
}

// CentrePoint() definition for centrepoint setter
void Circle::CentrePoint(const Point& newP)
{
	m_centrepoint = newP;
}

// ToString() definition
// use Point::ToString() to print Point object values
std::string Circle::ToString() const
{
	// create stream objects for conversion
	// input Line object's startpoint & endpoint x & y coordinates
	// create stream objects for conversion
	// input Circle object's radius
	std::ostringstream m_radius_conv;
	m_radius_conv << m_radius;

	// get str value for radius
	std::string str_m_radius;
	str_m_radius = m_radius_conv.str();
	return ("radius: " + str_m_radius +	", and endpoint: " + 
		m_centrepoint.ToString());
}

// Diameter() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Diameter() const
{
	return m_radius * 2;
}

// Area() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Area() const
{
	return M_PI * m_radius * m_radius;
}

// Circumference() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Circumference() const
{
	return 2 * M_PI * m_radius;
}