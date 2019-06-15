// Line.h
// Level2.3_Ex7
// 
// header file for the Line class
//
// Our Line class has private members for the startpoint and endpoint of the line 
// We include the following public functionality
//	· Default constructor
//	· Constructor
//	· Copy constructor
//	· Destructor
//	· Getter functions for the startpoint and endpoint data members
//	· Settter functions for the startpoint and endpointx data members
//	· A ToString() that returns a string description of the Line
//	· A Length() that returns the length of the Line
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
// Line()			-	default constructor
// Line(const Point&, const Point&)	-	constructor
// Line(const Point&)				-	copyconstructor
// ~Point()			-	destructor
// StartPoint()		-	getter/setter function for m_startpoint: return type const Point& for getter
// EndPoint()		-	getter/setter function for m_endpoint: return type const Point& for getter
// ToString()		-	returns a string representation of the Line object:	return type std::string
// Length()			-	returns the length of the line
//

#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <iostream>
#include <string>			// for return std::string in ToString() member function
#include "Point.h"

// Point class declaration
class Line
{
private:
	Point m_startpoint;
	Point m_endpoint;

public:
	Line();														// default constructor
	Line(const Point& startpoint, const Point& endpoint);		// constructor
	Line(const Line& Other);									// copy constructor
	~Line();													// destructor
	const Point& StartPoint() const { return m_startpoint; }	// startpoint point getter
	void StartPoint(const Point& newP) { m_startpoint = newP; }	// startpoint point setter
	const Point& EndPoint() const { return m_endpoint; }		// endpoint point getter
	void EndPoint(const Point& newP) { m_endpoint = newP; }		// endpoint point setter
	std::string ToString() const;								// print the Point coordinates
	double Length() const;										// length of the line
};

#endif // LINE_H_INCLUDED

