#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

// Point.h
// Level2.2_Ex1
// 
// header file for the Point class
//
// Our Point class has private members for the x- and y-coordinates. 
// We include the following public functionality (see Figure 1 in this project's image folder):
//	· Default constructor
//	· Destructor
//	· Getter functions for the x - and y - coordinates(GetX() and GetY() functions)
//	· Settter functions for the x - and y - coordinates(SetX() and SetY() functions)
//	· A ToString() that returns a string description of the point.
//    Use the std::string class as return type
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
// Member data variables will be declared float; float provides sufficient precision for academic
//  purposes
//
// private members:
// DATA:
// m_x	-	x coordinate (type float)
// m_y	-	y coordinate (type float)
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
// GetX()	-	getter function for m_x	:	return type float
// GetY()	-	getter function for m_y	:	return type float
// SetX()	-	setter function for m_x	:	no return, void function
// SetY()	-	setter function for m_y	:	no return, void function
// ToString()	-	returns a string representation of a Point object :	return type std::string
//

#include <iostream>
#include <string>

// Point class declaration
class Point
{
	private:
		int m_x;
		int m_y;
	
	public:
		Point();
		~Point();
		float GetX() const;
		float GetY() const;
		void SetX(float newX);
		void SetY(float newY);
		std::string ToString() const;
};

#endif // POINT_H_INCLUDED
