// Point.h
// Level2.3_Ex7
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
//	· Distance() functions for distance from the origin, and, distance between two points
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
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
// Distance(const Point& p)		-	returns the distance between two points
//								formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
//
// Getter functions should be const functions
// Return read-only const double references from getter functions
// All getter/setter functions inlined
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
	const double& X() const { return m_x; }		// inline x coordinate getter
	void X(const double& newX) { m_x = newX; }	// inline x coordinate setter
	const double& Y() const { return m_y; }		// inline y coordinate getter
	void Y(const double& newY) { m_y = newY; }	// inline y coordinate setter
	std::string ToString() const;				// print the Point coordinates
	double Distance() const;					// distance from the origin
	double Distance(const Point& p) const;		// distance between two points
};

#endif // POINT_H_INCLUDED

