// Circle.h
// Level2.3_Ex6
// 
// header file for the Circle class
//
// Our Circle class has private members for its radius. 
// We include the following public functionality
//	· Default constructor
//	· Constructor
//	· Copy Constructor
//	· Destructor
//	· Getter function for the radius
//	· Settter function for the radius
//  · Member function for Diameter
//  · Member function for Area
//  · Member function for Circumference
//	· A ToString() that returns a string description of the point.
//    Use the std::string class as return type
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
//
// private members:
// DATA:
// m_radius			-	type double
// m_centrepoint	-	type Point
// 
// METHODS:
// ...
//
// public members:
// DATA:
// ...
//
// METHODS:
// Circle()			-	default constructor
// Circle(double&,Point&)	-	constructor
// Circle(Circle&)	-	copy constructor
// ~CentrePoint()	-	destructor
// Radius()			-	getter/setter overloaded function for m_radius:	return const double reference for getter
// CentrePoint()	-	getter/setter overloaded function for m_centrepoint: return const Point reference for getter
// ToString()		-	returns a string representation of the Circle object: return type std::string
// Diameter()		-	returns the diamter of the circle
//						formula: diameter = 2 * radius
// Circumference()	-	returns the distance around the circle
//                      formula: circumference = 2 * radius * Pi
// Area()			-	returns the area of the circle
//                      formula: area = Pi * radius^2
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
	std::string ToString() const;				// print the Circle radius and coordinates
	double Diameter() const;					// distance through the centre between two points on the circle
	double Circumference() const;				// distance around the circle
	double Area()const;							// area of the circle
};

#endif // CIRCLE_H_INCLUDED
