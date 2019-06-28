/* Circle.h
Level3.5_Ex5: Polymorphism: Template Method Pattern
 
header file for the Circle class

Our Circle class has private members for its radius. 
We include the following public functionality
 · Default constructor
 · Constructor
 · Copy Constructor
 · Destructor
 · Getter function for the radius
 · Settter function for the radius
 · Member function for Diameter
 · Member function for Area
 · Member function for Circumference
 · A ToString() that returns a string description of the point

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_radius		-	type double
m_centrepoint	-	type Point
 
METHODS:
...

public members:
DATA:
...

METHODS:
Circle()				-	default constructor
Circle(double&,Point&)	-	constructor
Circle(Circle&)			-	copy constructor
~CentrePoint()			-	destructor
Radius()				-	getter/setter overloaded function for m_radius:	return const double reference for getter
CentrePoint()			-	getter/setter overloaded function for m_centrepoint: return const Point reference for getter
ToString()				-	returns a string representation of the Circle object: return type std::string
Diameter()				-	returns the diamter of the circle; formula: diameter = 2 * radius
Circumference()			-	returns the distance around the circle; formula: circumference = 2 * radius * Pi
Area()					-	returns the area of the circle; formula: area = Pi * radius^2

All getter/setter functions inlined

Note 1: M_PI (pi) is available only when _USE_MATH_DEFINES is defined in Circle.cpp and main.cpp, and
        <cmath> library is included in same files
        This may be related to inlining of Diameter(), Circumference() and Area()--see Note 2

Note 2: Diameter(), Circumference() and Area() are all inlined here since these functions are one-liners,
and the formulas for them are not expected to change anytime soon.

operator=()		-	overloaded assignment operator
operator<<()	-	overloaded ostream operator <<

the Circle class is part of the Turbopro::CAD namespace

*/

#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#define _USE_MATH_DEFINES	// for PI

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include <cmath>			// for PI

// create names space
namespace Turbopro
{
	namespace CAD
	{
		// Circle class declaration
		class Circle	:	public Shape			// derived from Turbopro::CAD::Shape
		{
		private:
			double m_radius;
			Point m_centrepoint;

		public:
			Circle();														// default constructor
			Circle(const double& m_radius, const Point& centre);			// constructor
			Circle(const Circle& Other);									// copy constructor
			virtual ~Circle();												// destructor
			const double& Radius() const { return m_radius; }				// inline radius getter
			void Radius(const double& newR);								// radius setter
			const Point& CentrePoint() const { return m_centrepoint; }		// inline centrepoint getter
			void CentrePoint(const Point& newP);							// centrepoint setter
			virtual std::string ToString() const;							// print the Circle radius and coordinates
			double Diameter() const { return 2 * m_radius; }				// inline distance through the centre between two points on the circle
			double Circumference() const { return 2 * M_PI * m_radius; }	// inline distance around the circle
			double Area()const { return M_PI * m_radius * m_radius; }		// inline area of the circle

			// overloaded operator methods
			Circle& operator=(const Circle& Other);							// assignment operator
			friend std::ostream& operator<<(std::ostream& os, const Circle& c);	// ostream operator <<

			// abstract methods
			void Draw() const { std::cout << "Draw a Circle\n"; }
		};

		inline void Circle::Radius(const double& newR) { m_radius = newR; }				// inline radius setter
		inline void Circle::CentrePoint(const Point& newP) { m_centrepoint = newP; }	// inline centrepoint setter
	}
}

#endif // CIRCLE_H_INCLUDED
