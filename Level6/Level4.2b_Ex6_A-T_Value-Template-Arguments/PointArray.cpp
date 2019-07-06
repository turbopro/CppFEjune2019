/* PointArray.cpp
Level4.2b_Ex5: Advanced Templates - Layering Exceptions

Source file that implements the PointArray Template class declared in the
PointArray.h header file.

the Array class is part of the Turbopro::Container namespace

*/

#ifndef POINTARRAY_CPP_INCLUDED
#define POINTARRAY_CPP_INCLUDED

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "PointArray.h"		// Array class declaration
#include "ArrayException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructor 
		template <typename Point>
		PointArray<Point>::PointArray(int arr_size) : Array<Point>{ arr_size } {}

		// default constructor
		template <typename Point>
		PointArray<Point>::PointArray() : Array<Point>() {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename Point>
		PointArray<Point>::PointArray(const PointArray<Point>& Other) : Array<Point>{ Other.Size() }
		{
			for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename Point>
		PointArray<Point>::~PointArray() {}

		// add the elements of two PointArrays
		template <typename Point>
		PointArray<Point> PointArray<Point>::operator+(const PointArray<Point>& Other) const
		{
			//if Arrays sizes are uneual, throw SizeMismatchException
			if (this->Size() != Other.Size())
			{
				throw Containers::SizeMismatchException(this->Size() - Other.Size());
			}

			PointArray<Point> sum_arr{ Other.Size() };
			for (int i = 0; i < Other.Size(); i++)
			{
				sum_arr[i] = (*this)[i] + Other[i];
			}

			return sum_arr;
		}

		// scale the elements of the PointArray by factor n
		template <typename Point>
		PointArray<Point> PointArray<Point>::operator*(double n) const
		{
			PointArray<Point> scaled_arr{ this->Size() };
			for (int i = 0; i < this->Size(); i++)
				scaled_arr[i] = (*this)[i] * n;

			return scaled_arr;
		}

		// Length()
		template <typename Point>
		double PointArray<Point>::Length() const
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
		}

		// overloaded assignment operator
		template <typename Point>
		PointArray<Point>& PointArray<Point>::operator=(const PointArray<Point>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				Array<Point>::operator=(Other);
				for (int i = 0; i < Other.Size(); i++)
					this->SetElement(Other[i], i);

				return *this;
			}
		}
	}
}
#endif // POINTARRAY_CPP_INCLUDED