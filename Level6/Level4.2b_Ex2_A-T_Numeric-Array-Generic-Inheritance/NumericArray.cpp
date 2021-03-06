/* NumericArray.cpp
Level4.2b_Ex2: Advanced Templates - Numeric Array (generic inheritance)

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

#ifndef NUMERICARRAY_CPP_INCLUDED
#define NUMERICARRAY_CPP_INCLUDED

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "NumericArray.h"	// Array class declaration
#include "ArrayException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructor 
		template <typename TNum>
		NumericArray<TNum>::NumericArray(int arr_size) : Array<TNum>{ arr_size } {}

		// default constructor
		template <typename TNum>
		NumericArray<TNum>::NumericArray() : Array<TNum>() {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TNum>
		NumericArray<TNum>::NumericArray(const NumericArray<TNum>& Other) 
			: Array<TNum>{ Other.Size() }
		{
			// deep copy Other's elements
			for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename TNum>
		NumericArray<TNum>::~NumericArray() {}

		// add the elements of two NumericArrays
		template <typename TNum>
		NumericArray<TNum> NumericArray<TNum>::operator+(const NumericArray<TNum>& Other) const
		{
			//if (m_arr_size != Other.m_arr_size)
			if (this->Size() != Other.Size())
			{
				// if NumericArrays are not the same size, throw exception
				throw Containers::SizeMismatchException(Other.Size());
			}

			NumericArray<TNum> res{ Other.Size() };
			for (int i = 0; i < Other.Size(); i++)
			{
				res[i] = (*this)[i] + Other[i];
			}
				
			return res;
		}
		
		// scale the elements of the NumericArray by factor n
		template <typename TNum>
		NumericArray<TNum> NumericArray<TNum>::operator*(double n) const
		{
			NumericArray<TNum> scaled_arr{ this->Size() };
			for (int i = 0; i < this->Size(); i++)
				scaled_arr[i] = (*this)[i] * n;

			return scaled_arr;
		}

		// DotProduct()
		template <typename TNum>
		TNum NumericArray<TNum>::DotProd(const NumericArray<TNum>& Other) const
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

		// overloaded assignment operator
		template <typename TNum>
		NumericArray<TNum>& NumericArray<TNum>::operator=(const NumericArray<TNum>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				Array<TNum>::operator=(Other);
				
				return *this;
			}
		}
	}
}
#endif // NUMERICARRAY_CPP_INCLUDED
