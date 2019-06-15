// Point.h
// Level2.3_Ex6
// 
// header file for the Point class
//
// Our Point class has private members for the x- and y-coordinates. 
// We include the following public functionality
//	· Default constructor
//	· Destructor
//	· Getter functions for the x- and y-coordinates(X() and Y() functions)
//	· Settter functions for the x- and y-coordinates(X() and Y() functions)
//	· A ToString() that returns a string description of the point.
//    Use the std::string class as return type
//	· Distance() functions for distance from the origin, and, distance between two points
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
// Point()			-	default constructor
// Point()			-	constructor
// Point()			-	copy constructor
// ~Point()			-	destructor
// X()				-	getter function for m_x	:	return type double
// Y()				-	getter function for m_y	:	return type double
// X(const double&)	-	setter function for m_x
// Y(const double&)	-	setter function for m_y
// ToString()		-	returns a string representation of a Point object :	return type std::string
// DistanceOrigin()	-	returns the distance between the point and the origin
//                      formula = sqrt((Point.x)^2 + (Point.y)^2)
// Distance(const Point&)	-	returns the distance between two points
//								formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
//

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <string>			// for return std::string in ToString() member function

// Point class declaration
class Point
{
private:
	double m_x;
	double m_y;

public:
	Point();									// default constructor
	Point(double x_coord, double y_coord);		// constructor
	Point(const Point& Other);					// copy constructor
	~Point();									// destructor
	const double& X() const;					// x coordinate getter
	void X(const double& newX);					// x coordinate setter
	const double& Y() const;					// y coordinate getter
	void Y(const double& newY);					// y coordinate setter
	std::string ToString() const;				// print the Point coordinates
	double Distance() const;					// distance from the origin
	double Distance(const Point& p) const;		// distance between two points
};

#endif // POINT_H_INCLUDED
