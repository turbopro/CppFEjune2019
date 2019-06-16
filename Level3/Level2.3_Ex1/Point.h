// Point.h
// Level2.3_Ex1
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
// Point()						-	default constructor
// Point(double x, double y)	-	constructor
// Point(double Other)			-	copy constructor
// ~Point()						-	destructor
// GetX()						-	getter function for m_x	:	return type double
// GetY()						-	getter function for m_y	:	return type double
// SetX()						-	setter function for m_x	:	no return, void function
// SetY()						-	setter function for m_y	:	no return, void function
// ToString()					-	returns a string representation of a Point object :	return type std::string
// DistanceOrigin()				-	returns the distance between the point and the origin
//									formula = sqrt((Point.x)^2 + (Point.y)^2)
// Distance(Point p)			-	returns the distance between two points
//									formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)
//

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <string>

// Point class declaration
class Point
{
private:
	double m_x;
	double m_y;

public:
	Point();								// default constructor
	Point(double x_coord, double y_coord);	// constructor
	Point(const Point& Other);				// copy constructor
	~Point();								// destructor
	double GetX() const;					// getter function for x-coordinate
	double GetY() const;					// getter function for y-coordinate
	void SetX(double newX);					// setter function for x-coordinate
	void SetY(double newY);					// setter function for y-coordinate
	std::string ToString() const;			// function to output point coordinates as a string
	double DistanceOrigin() const;			// distance function that calculates the distance between the origin and point 
	double Distance(Point p) const;			// distance function that calculates the distance between this point and another
};

#endif // POINT_H_INCLUDED
