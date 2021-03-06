/* Array.cpp
Level4.2b_Ex1: Advanced Templates - Static Variable for Array Default Size

Source file that implements the Array Template class declared in the
Array.h header file.

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

Getter and Setter methods check for an out of range index, and throws an
exception

the Array class is part of the Turbopro::Container namespace

*/

#ifndef ARRAY_CPP_INCLUDED
#define ARRAY_CPP_INCLUDED

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Array.h"			// Array class declaration
#include "ArrayException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// initialise static data member ArraySize to default size = 10
		template <typename T>
		int Array<T>::ArraySize = 10;

		// static data member ArraySize set method definition: check for size value
		template <typename T>
		void Array<T>::DefaultSize(int size)
		{
			// if size is negative, throw exception
			if (size < 0) { throw Containers::OutOfBoundsException(size); }

			Array<T>::ArraySize = size;
		}

		// constructor 
		template <typename T>
		Array<T>::Array(int arr_size)
			: m_data{ new T[arr_size] }, m_arr_size{ arr_size } {}	// size of array set during runtime

		// default constructor
		template <typename T>
		Array<T>::Array()
			: m_data{ new T[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = ArraySize

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename T>
		Array<T>::Array(const Array<T>& Other) : m_arr_size{ Other.Size() }, m_data{ new T[Other.Size()] }
		{
			for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename T>
		Array<T>::~Array() { delete[] m_data; }
		
		// SetElement() method
		template <typename T>
		void Array<T>::SetElement(const T& p, int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			m_data[index] = p;
		}

		// GetElement() method
		template <typename T>
		T& Array<T>::GetElement(int index) const
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return m_data[index];
		}

		// overloaded assignment operator
		template <typename T>
		Array<T>& Array<T>::operator=(const Array<T>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				// delete current array m_data;
				delete[] m_data;

				// create new m_data with size of Other
				m_arr_size = Other.Size();				// set member m_arr_size to size of Other
				m_data = new T[m_arr_size];				// create new array
				for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
				{
					m_data[i] = Other[i];
				}
				return *this;
			}
		}

		// overloaded array indexing operator: read/write version
		template <typename T>
		T& Array<T>::operator[](int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return this->GetElement(index);
		}


		// overloaded array indexing operator: const version
		template <typename T>
		const T& Array<T>::operator[](int index) const
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return m_data[index];
		}
	}
}
#endif // ARRAY_CPP_INCLUDED
