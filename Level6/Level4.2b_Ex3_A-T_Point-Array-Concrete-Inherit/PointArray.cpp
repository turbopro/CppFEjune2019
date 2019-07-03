/* PointArray.cpp
Level4.2b_Ex3: Advanced Templates - Point Array(concrete inheritance)

Source file that implements the NumericArray Template class declared in the
NumericArray.h header file.

constructor builds a dynamic Array object sized according to unsigned int argument
default constructor builds dynamic Array object with default enum array size value
copy constructor rebuilds the dynamic Array object based on the Other object to be
copied: does a deep copy operations
destructor deletes the Array object

The overloaded operator=() allows for Array a = Array b syntax, and checks for
self assignment

The overloaded ostream operator<<() allows for passing the Array object to an
ostream object, which includes cout for displaying the Array object

The overloaded operator[]() and operator[]() const methods provide the array
indexing operations. operator[]() method has an unintended side effect: it
assigns the Point object during a setter indexing operation when the index is
out of range. operator[]() const allows for setter indexing operations that
includes the assignment of const Array objects (rhs) to non-const Array
objects (lhs): the method prevents the implicit Array object from being
changed, and returns a const reference to the Point object, so that the Point
object also cannot be changed by the method

Getter and Setter methods check for an out of range index

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
			//: Array<TNum>{ arr_size } { std::cout << "NumericArray constructor\n"; }
			: Array<Point>{ arr_size }
		{ 
			std::cout << "NumericArray constructor\n"; 
		}

		// default constructor
		template <typename Point>
		PointArray<Point>::PointArray()
			//: Array<TNum>{}, m_data{ new TNum[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = ArraySize
			//: Array<TNum>()
			: Array<Point>() 
		{
			std::cout << "NumericArray default constructor\n";
		}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename Point>
		PointArray<Point>::PointArray(const PointArray<Point>& Other)
			//: Array<TNum>{ Other }, m_arr_size{ Other.Size() }, m_data{ new TNum[m_arr_size] }
			//: Array<TNum>{ Other.Size() }
			: Array<Point>{ Other.Size() }
		{
			//for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
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
				//scaled_arr.SetElement(((*this)[i] * n), i);
				scaled_arr[i] = (*this)[i] * n;

			return scaled_arr;
		}

		/*
		// DotProduct()
		template <typename Point>
		Point PointArray<Point>::DotProd(const NumericArray<TNum>& Other) const
		{
			//if (m_arr_size != Other.m_arr_size)
			if (this->Size() != Other.Size())
			{
				// if NumericArrays are not the same size, throw exception
				throw Containers::SizeMismatchException(this->Size() - Other.Size());
			}

			TNum dot_prod = 0;
			for (int i = 0; i < Other.Size(); i++)
			{
				dot_prod += (*this)[i] * Other[i];
			}

			return dot_prod;
		}
		*/

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