/* Line.h
Level3.5_Ex1: Polymorphism - Polymorphic ToString() Function
 
header file for the Line class

Our Line class has private members for the startpoint and endpoint of the line 
We include the following public functionality
 · Default constructor
 · Constructor
 · Copy constructor
 · Destructor
 · Getter functions for the startpoint and endpoint data members
 · Settter functions for the startpoint and endpointx data members
 · A ToString() that returns a string description of the Line
 · A Length() that returns the length of the Line

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
m_startpoint	-	type point
m_endpoint		-	type point
 
METHODS:
...

public members:
DATA:
...

METHODS:
Line()								-	default constructor
Line(const Point&, const Point&)	-	constructor
Line(const Point&)					-	copyconstructor
~Line()								-	destructor
StartPoint()						-	getter/setter function: return type const Point& for getter
EndPoint()							-	getter/setter function: return type const Point& for getter
ToString()							-	returns a string representation of the Line object:	return type std::string
Length()							-	returns the length of the line

All getter/setter functions inlined

operator=()		-	overloaded assignment operator
operator<<()		-	overloaded ostream operator <<

the Line class is part of the Turbopro::CAD namespace

*/

#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// create namespace
namespace Turbopro
{
	namespace CAD
	{
		// Line class declaration
		class Line	:	public Shape			// derived from Turbopro::CAD::Shape
		{
		private:
			Point m_startpoint;
			Point m_endpoint;

		public:
			Line();															// default constructor
			Line(const Point& startpoint, const Point& endpoint);			// constructor
			Line(const Line& Other);										// copy constructor
			~Line();														// destructor
			const Point& StartPoint() const { return m_startpoint; }		// inline startpoint point getter
			void StartPoint(const Point& newP);								// startpoint point setter
			const Point& EndPoint() const { return m_endpoint; }			// inline endpoint point getter
			void EndPoint(const Point& newP);								// endpoint point setter
			virtual std::string ToString() const;							// print the Point coordinates
			double Length() const;											// length of the line

			// overloaded operator methods
			Line& operator=(const Line& Other);								// assignment operator
			friend std::ostream& operator<<(std::ostream& os, const Line& l);	// ostream operator <<
		};

		inline void Line::StartPoint(const Point& newP) { m_startpoint = newP; }	// inline startpoint point setter
		inline void Line::EndPoint(const Point& newP) { m_endpoint = newP; }		// inline endpoint point setter
	}
}

#endif // LINE_H_INCLUDED

