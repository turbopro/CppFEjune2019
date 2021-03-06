// Point.cpp
// Level2.4_Ex3: Constructors As Conversion Operator
//
// Source file that implements the Point class declared in the 
// Point.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// All Getter/Setter functions have been inlined within Point.h
// 
// The ToString() function converts the double values of the data members 
// to strings
// We use a std::stringstream object, and the standard stream operators 
// (as with iostream) to create the string.  This requires the �sstream� 
// header file. We also use the str() function to retrieve the string 
// from the string buffer.  
// The return format for ToString(): �Point(1.5, 3.9)�
//
// The overloaded Distance() function makes use of the Pythagoras theorem to 
// calculate the distance between the point and the origin, and, the distance
// between two points
//

#include <iostream>
#include <sstream>			// for std::ostringstream() function in ToString() member function
#include <string>			// for std::string() function in ToString() member function
#include <cmath>			// for std::sqrt() function in Distance()
#include "Point.h"			// Point class declaration

// constructor using colon syntax initialiser
Point::Point(double x_coord, double y_coord) : m_x{ x_coord }, m_y{ y_coord } {}

// single argument constructor using colon syntax initialiser
// this constructor is used as an implicit conversion operator
Point::Point(double uni_coord) : m_x{ uni_coord }, m_y{ uni_coord } {}

// default constructor
Point::Point() : m_x{ 0 }, m_y{ 0 } {}

// copy constructor
Point::Point(const Point& Other) : m_x{ Other.m_x }, m_y{ Other.m_y } {}

// Destructor
Point::~Point() {}

// ToString()
std::string Point::ToString() const
{
	// create stream objects for conversion of data members
	std::ostringstream m_x_conv, m_y_conv;
	m_x_conv << m_x;
	m_y_conv << m_y;

	// get str values for data members
	std::string str_m_x = m_x_conv.str();
	std::string str_m_y = m_y_conv.str();

	// return string with format: "Point(x, y)"
	return ("Point(" + str_m_x + ", " + str_m_y + ")");
}

// Distance() point from origin
double Point::Distance() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}

// Distance() between two points
double Point::Distance(const Point& Other) const
{
	return std::sqrt((Other.m_x - m_x) * (Other.m_x - m_x) + 
		(Other.m_y - m_y) * (Other.m_y - m_y));
}

// overloading operators
// reverse the sign of the point
Point Point::operator-() const
{
	return Point{ -m_x, -m_y };
}

// add two points
Point Point::operator+(const Point& Other) const
{
	return Point{ (m_x + Other.m_x), (m_y + Other.m_y) };
}

// scale the point by factor n
Point Point::operator*(double n) const
{
	return Point{ n * m_x, n * m_y };
	//return Point( n * m_x, n * m_y );
}

// multiply n by Point p
Point operator*(double n, const Point& Other)
{
	return Other * n;
}

// assignment operator
// check for self assignment
Point& Point::operator=(const Point& Other)
{
	const Point* p_other = &Other;
	if (this == p_other)
	{
		std::cout << "Attempting to self assign " << this->ToString() 
				<< " at memory address: " << this << " to " 
				<< Other.ToString()	<< " at same address: " 
				<< p_other << "\n" << "Self assignment is not allowed\n"
				<< "Assignment aborted\n"
				<< this->ToString() << " is unchanged\n" ;
		return *this;
	}
	else
	{
		m_x = Other.m_x;
		m_y = Other.m_y;
		return *this;
	}
}

// scale the point by factor n, and assign
Point& Point::operator*=(double n)
{
	m_x *= n;
	m_y *= n;
	return *this;
}

// equality operator
bool Point::operator==(const Point& Other) const
{
	if (m_x == Other.m_x && m_y == Other.m_y) { return true; }
	else { return false; }
}

// overloaded ostream operator <<
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	return os << p.ToString();
}
