/* Array.cpp
Level4.2b_Ex2: Advanced Templates - Numeric Array (generic inheritance)

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

Getter and Setter methods check for an out of range index

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
		template <typename TArray>
		int Array<TArray>::ArraySize = 10;

		// static data member ArraySize set method definition: check for size value
		template <typename TArray>
		void Array<TArray>::DefaultSize(int size)
		{
			// if sz is negative, throw exception
			if (size < 0) { throw Containers::OutOfBoundsException(size); }

			Array<TArray>::ArraySize = size;
		}

		// constructor 
		template <typename TArray>
		Array<TArray>::Array(int arr_size)
			: m_data{ new TArray[arr_size] }, m_arr_size{ arr_size } {}	// size of array set during runtime

		// default constructor
		template <typename TArray>
		Array<TArray>::Array()
			: m_data{ new TArray[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = ArraySize

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TArray>
		Array<TArray>::Array(const Array<TArray>& Other) 
			: m_arr_size{ Other.Size() }, m_data{ new TArray[m_arr_size] }
		{
			for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
				(*this)[i] = Other[i];				// calls the const Point& operator[]() const method
		}

		// destructor
		template <typename TArray>
		Array<TArray>::~Array() 
		{ 
			//std::cout << "Deleting Array...\n";
			delete[] m_data; 
		}
		
		// SetElement() method
		template <typename TArray>
		void Array<TArray>::SetElement(const TArray& p, int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			m_data[index] = p;
		}

		// GetElement() method
		template <typename TArray>
		TArray& Array<TArray>::GetElement(int index) const
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return m_data[index];
		}

		// overloaded assignment operator
		template <typename TArray>
		Array<TArray>& Array<TArray>::operator=(const Array<TArray>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				// delete current array m_data;
				delete[] m_data;

				// create new m_data with size of Other
				m_arr_size = Other.Size();				// set member m_arr_size to size of Other
				m_data = new TArray[m_arr_size];				// create new array
				for (int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
				{
					m_data[i] = Other[i];
				}
				return *this;
			}
		}

		// overloaded array indexing operator: read/write version
		template <typename TArray>
		TArray& Array<TArray>::operator[](int index)
		{
			if (index < 0 || index >= m_arr_size)
			{
				// if index out of range, throw exception
				throw Containers::OutOfBoundsException(index);
			}

			return this->GetElement(index);
		}


		// overloaded array indexing operator: const version
		template <typename TArray>
		const TArray& Array<TArray>::operator[](int index) const
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
