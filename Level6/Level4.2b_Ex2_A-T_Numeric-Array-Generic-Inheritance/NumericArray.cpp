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
		// initialise static data member ArraySize to default size = 10
		//template <typename TNum>
		//int NumericArray<TNum>::ArraySize = 10;

		// static data member ArraySize set method definition: check for size value
		//template <typename TNum>
		//void NumericArray<TNum>::DefaultSize(int size)
		//{
			// if size is negative, throw exception
			//if (size < 0) { throw Containers::OutOfBoundsException(size); }

			//NumericArray<TNum>::ArraySize = size;
		//}

		// constructor 
		template <typename TNum>
		NumericArray<TNum>::NumericArray(int arr_size)
			//: Array<TNum>{ arr_size }, m_data{ new TNum[arr_size] }, m_arr_size{ arr_size } {}	// size of array set during runtime
			: Array<TNum>{ arr_size } {}

		// default constructor
		template <typename TNum>
		NumericArray<TNum>::NumericArray()
			//: Array<TNum>{}, m_data{ new TNum[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = ArraySize
			: Array<TNum>{} {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TNum>
		NumericArray<TNum>::NumericArray(const NumericArray<TNum>& Other) 
			//: Array<TNum>{ Other }, m_arr_size{ Other.Size() }, m_data{ new TNum[m_arr_size] }
			: Array<TNum>{ Other }
		{
			//for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
			for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename TNum>
		NumericArray<TNum>::~NumericArray() 
		{ 
			std::cout << "Deleting NumericArray...\n";
			//delete[] this->m_data; 
		}

		// add the elements of two NumericArrays
		template <typename TNum>
		NumericArray<TNum> NumericArray<TNum>::operator+(const NumericArray<TNum>& Other) const
		{
			//return Point{ (m_x + Other.m_x), (m_y + Other.m_y) };
			//if (m_arr_size != Other.m_arr_size)
			if (this->Size() != Other.Size())
			{
				// if NumericArrays are not the same size, throw exception
				throw Containers::OutOfBoundsException(Other.Size());
			}

			//NumericArray<TNum> res{ m_arr_size };
			NumericArray<TNum> res{ Other.Size() };
			for (int i = 0; i < Other.Size(); i++)
			{
				//res.SetElement((this->GetElement(i) + Other.GetElement(i)), i);
				res.SetElement(((*this)[i] + Other[i]), i);
			}
				
			return res;
		}
		
		// scale the elements of the NumericArray by factor n
		template <typename TNum>
		NumericArray<TNum> NumericArray<TNum>::operator*(double n) const
		{
			NumericArray<TNum> res{ this->Size() };
			for (int i = 0; i < this->Size(); i++)
				res.SetElement(((*this)[i] * n), i);
				//res.m_data[i] = m_data[i] * n;

			return res;
		}


		/*
		// SetElement() method
		template <typename TNum>
		void NumericArray<TNum>::SetElement(const TNum& p, int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			m_data[index] = p;
		}

		// GetElement() method
		template <typename TNum>
		TNum& NumericArray<TNum>::GetElement(int index) const
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return m_data[index];
		}
		*/
		// overloaded assignment operator
		template <typename TNum>
		NumericArray<TNum>& NumericArray<TNum>::operator=(const NumericArray<TNum>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				NumericArray<TNum> res{ Other.Size() };
				for (int i = 0; i < Other.Size(); i++)
					res.SetElement(Other[i], i);
				//res.m_data[i] = m_data[i] * n;
				for (int i = 0; i < Other.Size(); i++)
					std::cout << "res[" << i << "]: " << res[i] << std::endl;

				return res;
				
				/*
				//std::cout << "here: m_data[0]: " << this->m_data[1]
					//<< "\nOther[0]: " << Other[1] << std::endl;
				// delete current array m_data;
				//delete[] Array<TArray>:: ;

				// create new m_data with size of Other
				(*this).m_arr_size = Other.Size();		// set member m_arr_size to size of Other
				(*this).m_data = new TNum[Other.Size()];			// create new array
				for (int i = 0; i < Other.Size(); i++)	// deep copy Other's elements
				{
					//m_data[i] = Other[i];
					std::cout << "before this->m_data[" << i << "]: " << this->GetElement(i)
						<< "\nbefore Other[" << i << "]: " << Other[i] << std::endl;
					(*this).SetElement(Other[i], i);
					std::cout << "after this->m_data[" << i << "]: " << this->Getelement(i)
						<< "\nsfter Other[" << i << "]: " << Other[i] << std::endl;
				}
				//std::cout << "\njust before return: this->m_data[1]: " << m_data[1] << std::endl;
				return *this;
				*/
			}
		}

		/*
		// overloaded array indexing operator: read/write version
		template <typename TNum>
		TNum& NumericArray<TNum>::operator[](int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return this->GetElement(index);
		}


		// overloaded array indexing operator: const version
		template <typename TNum>
		const TNum& NumericArray<TNum>::operator[](int index) const
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return m_data[index];
		}
		*/
	}
}
#endif // NUMERICARRAY_CPP_INCLUDED
