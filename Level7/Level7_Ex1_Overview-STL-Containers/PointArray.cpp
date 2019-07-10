/* PointArray.cpp
Level7_Ex1: Overview of the Standard Template Library - STL Containers

Source file that implements the PointArray Template class declared in the
PointArray.h header file.

the Array class is part of the Turbopro::Container namespace

*/

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "PointArray.h"		// Array class declaration
#include "ArrayException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructors delegate construction to base class Array (Array<Point>)
		// constructor
		PointArray::PointArray(int arr_size) : Array<Point>(arr_size) {}

		// default constructor
		PointArray::PointArray() : Array<Point>() {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		PointArray::PointArray(const PointArray& Other) : Array<Point>{ Other.Size() }
		{
			for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		PointArray::~PointArray() {}

		// add the elements of two PointArrays
		PointArray PointArray::operator+(const PointArray& Other) const
		{
			if (this->Size() != Other.Size())
			{
				// if PointArrays are not the same size, throw exception
				throw Containers::SizeMismatchException(Other.Size());
			}

			// create PointArray to accumulate sum
			PointArray sum_arr{ Other.Size() };
			for (int i = 0; i < Other.Size(); i++)
			{
				sum_arr[i] = (*this)[i] + Other[i];
			}

			return sum_arr;
		}

		// scale the elements of the PointArray by factor n
		PointArray PointArray::operator*(double n) const
		{
			// create PointArray for scaling
			PointArray scaled_arr{ this->Size() };
			for (int i = 0; i < this->Size(); i++)
				scaled_arr[i] = (*this)[i] * n;

			return scaled_arr;
		}

		// Length()
		double PointArray::Length() const
		{
			// loop until 1 less than PointArray size
			// get Points from this and the next elements
			// accumulate lengths with Point.Distance(const Point&)
			double length = 0.0;
			Point p0, p1;
			for (int i = 0; i < (this->Size() - 1); i++)
			{
				p0 = this->GetElement(i);
				p1 = this->GetElement(i + 1);
				length += p0.Distance(p1);
			}

			return length;
		}

		// overloaded assignment operator
		PointArray& PointArray::operator=(const PointArray& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				// copy Other Array<Point> and return
				Array<Point>::operator=(Other);

				return *this;
			}
		}
	}
}
