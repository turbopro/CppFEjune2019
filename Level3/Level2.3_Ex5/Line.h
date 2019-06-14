// Line.h
// Level2.3_Ex5
// 
// header file for the Line class
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
// DistanceOrigin()	-	returns the distance between the point and the origin
//                      formula = sqrt((Point.x)^2 + (Point.y)^2)
// Distance(Point p)	-	returns the distance between two points
//							formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
//

#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <iostream>
#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// Point class declaration
class Line
{
private:
	Point m_startpoint;
	Point m_endpoint;

public:
	Line();										// default constructor
	Line(const Point& startpoint,				// constructor
		const Point& endpoint);		
	Line(const Line& Other);					// copy constructor
	~Line();									// destructor
	Point StartPoint() const;					// startpoint point getter
	void StartPoint(Point newP);				// startpoint point setter
	Point EndPoint() const;						// endpoint point getter
	void EndPoint(Point newP);					// endpoint point setter
	std::string ToString() const;				// print the Point coordinates
	double Length() const;						// distance from the origin
};

#endif // LINE_H_INCLUDED
