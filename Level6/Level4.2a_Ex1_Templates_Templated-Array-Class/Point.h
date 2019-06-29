/* Point.h
Level4.2a_Ex1: Introduction to Templates - Templated Array Class
 
header file for the Point class

Our Point class is now derived from the Shape class
Point class has private members for the x- and y-coordinates

We include the following public functionality (see Figure 1 in this project's image folder):
 · Default constructor
 · Destructor
 · Getter functions for the x - and y - coordinates(GetX() and GetY() functions)
 · Settter functions for the x - and y - coordinates(SetX() and SetY() functions)
 · A ToString() that returns a string description of the point.
 · Use the std::string class as return type
 · Distance() functions for distance from the origin, and, distance between two points
 · Operator+() for addition of the points using '+'
 · Operator*() for scaling of the points using '*'
 · Operator-() for negation of the coordinates
 · Operator=() for the assignment operator '='
 · Operator*=() for scaling and assigning
 · Operator==() compare the points for equality
 ·

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_x	-	x coordinate (type double)
m_y	-	y coordinate (type double)
 
METHODS:
...

public members:
DATA:
...

METHODS:
Point()					-	default constructor
Point(double x, double y)-	constructor
Point(double Other)		-	copy constructor
~Point()				-	destructor
X()						-	getter function for m_x	:	return type double
Y()						-	getter function for m_y	:	return type double
X(double x)				-	setter function for m_x	:	no return, void function
Y(double y)				-	setter function for m_y	:	no return, void function
ToString()				-	returns a string representation of a Point object :	return type std::string
Distance()				-	returns the distance between the point and the origin
							formula = sqrt((Point.x)^2 + (Point.y)^2)
Distance(const Point& p)	-	returns the distance between two points
							formula = sqrt((Point1.x - Point2.x)^2 + (Point1.y - Point2.y)^2)

Getter functions should be const functions
Return read-only const double references from getter functions
All getter/setter functions inlined

overloaded operator methods:
operator-()				- // reverse the sign of the point
operator+()				- // add two points
operator*()				- // scale the point by factor n
operator*()				- // multiply n by Point p (friend method)
operator=(r)			- // assignment operator
operator*=()			- // scale the point by factor n
operator==()			- // equality operator
operator<<()			- // ostream operator (friend method)

constructor that accepts one double as an argument. 
The implementation should set both the x- and y-coordinate to this value.

the Point class is part of the Turbopro::CAD namespace

*/

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Shape.h"

//create namespace
namespace Turbopro
{
	namespace CAD
	{
		// Point class declaration
		class Point	:	public Shape			// derived from Turbopro::CAD::Shape
		{
		private:
			double m_x;
			double m_y;

		public:
			Point();										// default constructor
			Point(double x_coord, double y_coord);			// constructor
			explicit Point(double x_coord);					// single argument constructor (explicit)
			Point(const Point& Other);						// copy constructor
			virtual ~Point();										// destructor
			const double& X() const { return m_x; }			// inline x coordinate getter
			void X(const double& newX);						// x coordinate setter
			const double& Y() const { return m_y; }			// inline y coordinate getter
			void Y(const double& newY);						// y coordinate setter
			virtual std::string ToString() const;			// print the Point coordinates
			double Distance() const;						// distance from the origin
			double Distance(const Point& Other) const;		// distance between two points

			// overloaded operator methods
			Point operator-() const;						// reverse the sign of the point
			Point operator+(const Point& Other) const;		// add two points
			Point operator*(double n) const;				// scale the point by factor n
			friend Point operator*(double n, const Point& Other);	// multiply n by Point p
			Point& operator=(const Point& Other);			// assignment operator
			Point& operator*=(double n);					// scale the point by factor n and assign
			bool operator==(const Point& Other) const;		// equality operator
			// ostream operator <<
			friend std::ostream& operator<<(std::ostream& os, const Point& p);

			// override methods
			void Draw() const { std::cout << "Draw a Point\n";}
		};



		inline void Point::X(const double& newX) { m_x = newX; }	// inline x coordinate setter
		inline void Point::Y(const double& newY) { m_y = newY; }	// inline y coordinate setter

		// inlined overloaded operator methods
		// reverse the sign of the point
		inline Point Point::operator-() const { return Point{ -m_x, -m_y }; }

		// add two points
		inline Point Point::operator+(const Point& Other) const 
			{ return Point{ (m_x + Other.m_x), (m_y + Other.m_y) }; }

		// scale the point by factor n
		inline Point Point::operator*(double n) const { return Point{ n * m_x, n * m_y }; }

		// multiply n by Point p (friend function)
		inline Point operator*(double n, const Point& Other) { return Other * n; }

		// equality operator
		inline bool Point::operator==(const Point& Other) const { return (m_x == Other.m_x && m_y == Other.m_y); }
	}
}
#endif // POINT_H_INCLUDED
