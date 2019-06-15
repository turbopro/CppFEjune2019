// Circle.h
// Level2.3_Ex6
// 
// header file for the Circle class
//
// Our Circle class has private members for its radius. 
// We include the following public functionality (see Figure 1 in this project's image folder):
//	· Default constructor
//	· Destructor
//	· Getter functions for the radius
//	· Settter functions for the radius
//  · Member functions for Diameter
//  · Member functions for Area
//  · Member functions for Circumference
//	· A ToString() that returns a string description of the point.
//    Use the std::string class as return type
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
// Member data variables will be declared float; float provides sufficient precision for academic
//  purposes
//
// private members:
// DATA:
// m_radius	-	radius (type float)
// m_centre	-	centre point (type Point)
// 
// METHODS:
// ...
//
// public members:
// DATA:
// ...
//
// METHODS:
// CentrePoint()	-	default constructor
// ~CentrePoint()	-	destructor
// Radius()			-	getter/setter overloaded function for m_radius:	return type float for getter
// ToString()		-	returns a string representation of a Point object :	return type std::string
// Circumference()	-	returns the distance around the circle
//                      formula = 2 * radius
// Area()			-	returns the area of the circle
//                      formula = PI * radius^2
//

#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include <iostream>
#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// Point class declaration
class Circle
{
private:
	double m_radius;
	Point m_centrepoint;

public:
	Circle();									// default constructor
	Circle(const double& m_radius,				// constructor
		const Point& centre);
	Circle(const Circle& Other);				// copy constructor
	~Circle();									// destructor
	const double& Radius() const;				// radius getter
	void Radius(const double& newR);			// radius setter
	const Point& CentrePoint() const;			// centrepoint getter
	void CentrePoint(const Point& newP);		// centrepoint setter	
	std::string ToString() const;				// print the Point coordinates
	double Diameter() const;					// distance through the centre between two points on the circle
	double Circumference() const;				// distance around the circle
	double Area()const;							// area of the circle
};

#endif // CIRCLE_H_INCLUDED


