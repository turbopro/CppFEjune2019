// Point.h
// Level2.2_Ex1
// 
// header file for the Point class
//
// Our Point class has private members for the x- and y-coordinates. 
// We include the following public functionality (see Figure 1 in this project's image folder):
//	· Default constructor
//	· Destructor
//	· Getter functions for the x- and y-coordinates(GetX() and GetY() functions)
//	· Settter functions for the x- and y-coordinates(SetX() and SetY() functions)
//	· A ToString() that returns a string description of the point.
//    Use the std::string class as return type
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
//
// private members:
// DATA:
// m_x	-	x coordinate (type double)
// m_y	-	y coordinate (type double)
// 
// METHODS:
// ...
//
// public members:
// DATA:
// ...
//
// METHODS:
// Point()	-	default constructor
// ~Point()	-	destructor
// GetX()	-	getter function for m_x	:	return type double
// GetY()	-	getter function for m_y	:	return type double
// SetX()	-	setter function for m_x	:	no return, void function
// SetY()	-	setter function for m_y	:	no return, void function
// ToString()	-	returns a string representation of a Point object :	return type std::string
//

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <string>						// for ToString() function

// Point class declaration
class Point
{
private:
	double m_x;							// data member x coordinate
	double m_y;							// data member y coordinate

public:
	Point();							// default constructor
	~Point();							// destructor
	double GetX() const;				// getter function for x-coordinate
	double GetY() const;				// getter function for y-coordinate
	void SetX(double newX);				// setter function for x-coordinate
	void SetY(double newY);				// setter function for y-coordinate
	std::string ToString() const;		// function to output point coordinates as a string
};

#endif // POINT_H_INCLUDED
