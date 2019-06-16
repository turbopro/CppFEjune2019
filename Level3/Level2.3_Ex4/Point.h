// Point.h
// Level2.3_Ex4
// 
// header file for the Point class
//
// Our Point class has private members for the x- and y-coordinates. 
// We include the following public functionality
// Add constructor and copy constructor
//	· Default constructor
//	· Constructor
//	· Copy constructor
//	· Destructor
//	· Overloaded getter functions for the x- and y-coordinates (X() and Y() functions)
//	· Overloaded settter functions for the x- and y-coordinates (X(double x) and Y(double y) functions)
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
// Point()					-	default constructor
// Point(double x, double y)-	constructor
// Point(double Other)		-	copy constructor
// ~Point()					-	destructor
// X()						-	getter function for m_x	:	return type double
// Y()						-	getter function for m_y	:	return type double
// X(double x)				-	setter function for m_x	:	no return, void function
// Y(double y)				-	setter function for m_y	:	no return, void function
// ToString()				-	returns a string representation of a Point object :	return type std::string
// Distance()				-	returns the distance between the point and the origin
//								formula = sqrt((Point.x)^2 + (Point.y)^2)
// Distance(const Point& p)	-	returns the distance between two points
//								formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
//
// getter functions should be const functions
// return read-only const double references from getter functions
//

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

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
	void X(double newX);						// x coordinate setter
	const double& Y() const;					// y coordinate getter
	void Y(double newY);						// y coordinate setter
	std::string ToString() const;				// print the Point coordinates
	double Distance() const;					// distance from the origin
	double Distance(const Point& p) const;		// distance between two points
};

#endif // POINT_H_INCLUDED

