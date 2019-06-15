// Circle.cpp
// Level2.3_Ex6
//
// Source file that implements the Circle class declared in the 
// Circle.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// Getter functions are overloaded functions
// Radius() returns const double reference to class member; member value cannot be changed
// CentrePoint() returns const Point reference to class member; member value cannot be changed
//
// Setter functions are overloaded functions
// Radius() has const double reference to double argument; the argument is read-only 
// and cannot be changed by the function
// CentrePoint() has const Point reference to Point argument; the argument is read-only 
// and cannot be changed by the function
//
// The ToString() function converts the radius member to a string, and concatenates this with
// the string values output from the ToString() function of the centrepoint member
//
// The Diameter(), Circumference() and Area() functions effect direct calculations on the
// member variables using constants: the constant M_PI is the C/C++ constant for Pi
//

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function, and M_PI (Pi)
#include "Point.h"			// Point class declaration
#include "Circle.h"			// Line class declaration


// constructor using colon syntax initialiser
Circle::Circle(const double& radius, const Point& centrepoint)
	: m_radius{ radius }, m_centrepoint{ centrepoint.X(), centrepoint.Y() }
{
	std::cout << "Waa! Waa! new Circle 'constructor'\n";
}

// default constructor using colon syntax initialiser
Circle::Circle() : m_radius{ 0.0 }, m_centrepoint{ 0, 0 }
{
	std::cout << "Waa! Waa! new Circle 'default constructor'\n";
}

// copy constructor using colon syntax initialiser
Circle::Circle(const Circle& Other) 
	: m_radius{ Other.m_radius }, m_centrepoint{ Other.m_centrepoint }
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
	// convert Circle object's radius to a string
	std::ostringstream m_radius_conv;
	m_radius_conv << m_radius;
	std::string str_m_radius = m_radius_conv.str();
	return ("radius: " + str_m_radius +	", and endpoint: " + 
		m_centrepoint.ToString());
}

// Diameter() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Diameter() const
{
	return m_radius * 2;
}

// Circumference() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Circumference() const
{
	return 2 * M_PI * m_radius;
}

// Area() definition
// use Point::Distance(const Point&) to calculate length of the Line object
double Circle::Area() const
{
	return M_PI * m_radius * m_radius;
}