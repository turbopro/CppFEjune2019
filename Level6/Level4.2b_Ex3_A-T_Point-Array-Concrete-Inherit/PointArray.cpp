/* PointArray.cpp
Level4.2b_Ex3: Advanced Templates - Point Array(concrete inheritance)

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
		PointArray<Point>::PointArray(int arr_size)
			//: Array<TNum>{ arr_size }, m_data{ new TNum[arr_size] }, m_arr_size{ arr_size } {}	// size of array set during runtime
			: Array<Point>{ arr_size }
		{ 
			std::cout << "NumericArray constructor\n"; 
		}

		// default constructor
		template <typename Point>
		PointArray<Point>::PointArray()
			//: Array<TNum>{}, m_data{ new TNum[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = ArraySize
			: Array<Point>() 
		{
			std::cout << "NumericArray default constructor\n";
		}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename Point>
		PointArray<Point>::PointArray(const PointArray<Point>& Other)
			//: Array<TNum>{ Other }, m_arr_size{ Other.Size() }, m_data{ new TNum[m_arr_size] }
			: Array<Point>{ Other.Size() }
		{
			std::cout << "NumericArray copy constructor\n";
			for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename Point>
		PointArray<Point>::~PointArray()
		{
			//std::cout << "Deleting NumericArray...\n";
		}

		// add the elements of two NumericArrays
		template <typename Point>
		PointArray<Point> PointArray<Point>::operator+(const PointArray<Point>& Other) const
		{
			//if (m_arr_size != Other.m_arr_size)
			if (this->Size() != Other.Size())
			{
				// if NumericArrays are not the same size, throw exception
				throw Containers::SizeMismatchException(this->Size() - Other.Size());
			}

			PointArray<Point> res{ Other.Size() };
			for (int i = 0; i < Other.Size(); i++)
			{
				res[i] = (*this)[i] + Other[i];
			}

			return res;
		}

		// scale the elements of the NumericArray by factor n
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
			double length = 0.0;
			for (int i = 0; i < this->Size(); i++)
				length += (*this)[i].Distance();

			return length;
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