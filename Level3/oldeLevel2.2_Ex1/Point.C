// Point.C
//
// Source file that implements the Point class declared in the 
// Point.h header file.  
// The string in the ToString() function, requires conversion of 
// the double coordinates to a string.  We use a std::stringstream 
// object, and the standard stream operators (as with iostream) to 
// create the string.  This requires the “sstream” header file. 
// Use the str() function to retrieve the string from the string 
// buffer.  The output can be like : “Point(1.5, 3.9)”
//

#include "Point.h"

// Default constructor definition
Point::Point()
{
	m_x = m_y = 0.0;
}

// Destructor definition
Point::~Point()
{
	std::cout << "Point (" << m_x << ", " << m_y << ") has left the building.\n";
}

// GetX() definition
float Point::GetX() const
{
	return m_x;
}

// GetY() definition
float Point::GetY() const
{
	return m_y;
}

// SetX() definition
void Point::SetX(float newX)
{
	m_x = newX;
}

// SetY() definition
void Point::SetX(float newX)
{
	m_y = newY;
}

// ToString() definition
std::string Point::ToString() const
{
	m_y = newY;
}
