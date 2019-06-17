// Line.cpp
// Level2.4_Ex1: Add operators to the Point class
//
// Source file that implements the Line class declared in the 
// Line.h header file.
//
// constructor uses the colon initialiser, and is verbose
// default constructor also uses the colon initlaiser, and also verbose
// copy constructor same as above
// destructor is also verbose
//
// All Getter/Setter functions inlined within Line.h
// 
// The ToString() function makes use of the ToString() function of the
// constituent points of the Line
//
// The Length() function makes use of the Point::Distance(const Point&) function 
//

#include <string>			// for std::string() function in ToString() member function
#include "Line.h"			// Line class declaration

// 	: m_startpoint{ startpoint.X(), startpoint.Y() }, m_endpoint{ endpoint.X(), endpoint.Y() } {}
// updated after grading; see relevant post in the forum for this HW
// https://quantnet.com/threads/level-3-hw-vernon-woolford.39463/#post-248880
// constructor using colon syntax initialiser
Line::Line(const Point& startpoint, const Point& endpoint)
	: m_startpoint{ startpoint }, m_endpoint{ endpoint } {}

// default constructor
Line::Line() : m_startpoint{ Point{ 0, 0 } }, m_endpoint{ Point{ 0, 0 } } {}

// copy constructor
Line::Line(const Line& Other) : m_startpoint{ Other.m_startpoint }, m_endpoint{ Other.m_endpoint } {}

// Destructor
Line::~Line() {}

// ToString() 
// use Point::ToString() of the Point objects
std::string Line::ToString() const
{
	return ("startpoint: " + m_startpoint.ToString() +
		", and endpoint: " + m_endpoint.ToString());
}

// Length()
// use Point::Distance(const Point&) function to calculate line length
double Line::Length() const
{
	return m_startpoint.Distance(m_endpoint);
}
