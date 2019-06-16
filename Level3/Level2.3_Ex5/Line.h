// Line.h
// Level2.3_Ex5
// 
// header file for the Line class
//
// Our Line class has private members startpoint and endpoint
// We include the following public functionality
//	· Default constructor (set start- and end-points to (0, 0)
//	· Constructor with a startpoint and an endpoint
//	· Copy constructor
//	· Destructor
//	· Overloaded getters for the start- and end-point
//	· Overloaded setters for the start- and end-point
//	· A ToString() function that returns a description of the line
//  · A Length() function that returns the length of the line. Note 
//    that you can use the distance function on the embedded Point 
//    objects to calculate the length. This mechanism is called 
//    “delegation”.
//
// Member data variables will be prefixed with 'm_' to signify the variable is a class member
//
// private members:
// DATA:
// m_startpoint	-	type point
// m_endpoint	-	type point
// 
// METHODS:
// ...
//
// public members:
// DATA:
// ...
//
// METHODS:
// Line()						-	default constructor
// Line(Point a, Point b)		-	constructor
// Line(Point Other)			-	copy constructor
// ~Line()						-	destructor
// StartPoint()					-	getter function for startpoint
// EndPoint()					-	getter function for endpoint
// StartPoint(Point p)			-	setter function for startpoint
// EndPoint(Poin p)				-	setter function for endpoint
// ToString()					-	returns a string representation of a Line
// Length()						-	returns the length of the line
//									makes use of the Distance(Point p) function
//

#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// Point class declaration
class Line
{
private:
	Point m_startpoint;
	Point m_endpoint;

public:
	Line();													// default constructor
	Line(const Point& startpoint, const Point& endpoint);	// constructor	
	Line(const Line& Other);								// copy constructor
	~Line();												// destructor
	const Point& StartPoint() const;						// startpoint point getter
	void StartPoint(const Point& newP);						// startpoint point setter
	const Point& EndPoint() const;							// endpoint point getter
	void EndPoint(const Point& newP);						// endpoint point setter
	std::string ToString() const;							// print the Line
	double Length() const;									// length of the line
};

#endif // LINE_H_INCLUDED
