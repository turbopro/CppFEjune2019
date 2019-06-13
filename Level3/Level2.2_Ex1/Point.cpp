// Point.C
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

#include <iostream>
#include <sstream>
#include <string>
#include "Point.h"

// Default constructor
Point::Point()
{
	m_x = m_y = 0.0;
}

// (verbose) Destructor definition
Point::~Point()
{
	std::cout << "\nRIP point (" << m_x << ", " << m_y << ")\n";
}

// GetX() definition
double Point::GetX() const
{
	return m_x;
}

// GetY() definition
double Point::GetY() const
{
	return m_y;
}

// SetX() definition
void Point::SetX(double newX)
{
	m_x = newX;
}

// SetY() definition
void Point::SetY(double newY)
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