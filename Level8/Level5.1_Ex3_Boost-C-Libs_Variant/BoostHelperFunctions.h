/* STLHelperFunctions.h
Level5.1_Ex3: Boost C++ Libraries - Variant

header file for the Boost C++ Helper Functions class

Includes:

-	Smart Pointers: shared_ptr
		The boost::shared_ptr<T> class stores a pointer and will delete 
		the object automatically when nobody is referencing the object 
		anymore. Thus instead of creating an array of Shape* we can 
		create an array with boost::shared_ptr<Shape> and the deletion 
		of the shapes will be done automatically.
-	Tuple
		Boost tuples can be used to store different kinds of data as 
		one entity. It can be used if we need to combine data without 
		the need to create a separate class.
-	Variant
		In contrast to tuple, a boost::variant stores one value that 
		can be of one of the specified types. It is thus similar to 
		a C union but it is type-safe.

*/

#ifndef BOOSTHELPERFUNCTIONS_H_INCLUDED
#define BOOSTHELPERFUNCTIONS_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "User_input.h"
#include <iostream>

// Boost C Libraries Header Files
#include <boost/shared_ptr.hpp>			// for Shared Pointer: shared_ptr 
#include <boost/tuple/tuple.hpp>		// for Tuple
#include <boost/tuple/tuple_io.hpp>		// for Tuple Input/Output operators
#include <boost/variant.hpp>			// for variant

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// using std namespace 
		using std::cout;
		using std::cin;
		using std::endl;

		// using Turbopro namespace
		using Turbopro::CAD::Point;
		using Turbopro::CAD::Line;
		using Turbopro::CAD::Circle;
		
		// is_less_than()
		// print tuple declaration
		// create typedef for Person tuple with name, age, and height
		typedef boost::tuple<std::string, int, float> Person;
		void print_tuple(const Person& P);

		// function to return a variant
		// create typedef for variant with either of shape: Point, Line, Circle
		typedef boost::variant<Point, Line, Circle> ShapeType;
		ShapeType& choose_shape();

		// print tuple definition
		void print_tuple(const Person& P)
		{
			cout << "Name: " << P.get<0>()
				<< ", Age: " << P.get<1>() << " years, "
				<< "Height: " << P.get<2>() << " m" << endl;
		}

		ShapeType& choose_shape()
		{
			using Turbopro::CAD::Circle;
			using Turbopro::CAD::Line;
			using Turbopro::CAD::Point;

			ShapeType chosen;			// create variant ShapeType
			char choice;				// create char for user input
			cout << "Please choose the type of shape to be created:"
				<< "\nC for Circle\nL for Line\nP for Point\n";
			cin >> choice;

			
			switch (choice)				// choose shape
			{
			case 'C':
			case 'c':
			{
				//Circle c0; chosen = c0;	// create default Circle
				//double coord_val;
				// get user input for Circle coordinates
				double x{ 0.0 }, y{ 0.0 }, radius{ 0.0 };
				if (user_input_geom(x, "c0", "CentrePoint: x_coordinate") &&
					user_input_geom(y, "c0", "CentrePoint: y_coordinate") &&
					user_input_geom(radius, "c0", "radius"))
				{
					Circle c0(radius, Point(x, y));
					chosen = c0;
				}
				else { Circle c0; chosen = c0; }	// if user quit, set default Circle
				
				break;
			}

			case 'L':
			case 'l':
			{
				//Line l0; chosen = l0;
				// get user input for Line coordinates
				double s_x{ 0.0 }, s_y{ 0.0 }, e_x{ 0.0 }, e_y{ 0.0 };
				if (user_input_geom(s_x, "l0", "StartPoint: x_coordinate") &&
					user_input_geom(s_y, "l0", "StartPoint: y_coordinate") &&
					user_input_geom(e_x, "l0", "EndPoint: x_coordinate") &&
					user_input_geom(e_y, "l0", "EndPoint: y_coordinate"))
				{
					Line l0(Point(s_x, s_y), Point(e_x, e_y));
					chosen = l0;
				}
				else { Line l0; chosen = l0; }	// if user quit, set default Line

				break;
			}

			case 'P':
			case 'p':
			{
				//Point p0; chosen = p0;
				// get user input for Point coordinates
				double x{ 0.0 }, y{ 0.0 };
				if (user_input_geom(x, "p0", "x_coordinate") &&
					user_input_geom(y, "p0", "y_coordinate"))
				{
					Point p0(x, y);
					chosen = p0;
				}
				else { Point p0; chosen = p0; }	// if user quit, set default Point

				break;
			}

			case 'Q':
			case 'q':
				return chosen;

			default:
				Point p0;
				chosen = p0;
			}

			return chosen;
		}

		
		class VariantVisitor	:	public boost::static_visitor<void>
		{
		private:
			double m_dx;			// offset x value
			double m_dy;			// offset y value

		public:
			VariantVisitor() : m_dx(0.5), m_dy(0.5) {}			// default constructor
			VariantVisitor(double dx, double dy)				// constructor
				: m_dx(dx), m_dy(dy) {}
			VariantVisitor(const VariantVisitor& Other)			// copy constructor
				: m_dx(Other.m_dx), m_dy(Other.m_dy) {}
			~VariantVisitor() {}								// destructor
			void operator() (Point& p) const;					// Point mover	
			void operator() (Line& l) const;					// Line mover
			void operator() (Circle& c) const;					// Circle mover
		};

		// Point mover definition
		void VariantVisitor::operator() (Point& p) const
			{ p.X(p.X() + m_dx); p.Y(p.Y() + m_dy); }
		
		// Line mover definition
		void VariantVisitor::operator() (Line& l) const
		{ 
			l.StartPoint(l.StartPoint() + Point(m_dx, m_dy)); 
			l.EndPoint(l.EndPoint() + Point(m_dx, m_dy));			
		}
		
		// Circle mover definition
		void VariantVisitor::operator() (Circle& c) const
			{ c.CentrePoint(c.CentrePoint() + Point(m_dx, m_dy)); }

	}
}

#endif // BOOSTHELPERFUNCTIONS_H_INCLUDED
