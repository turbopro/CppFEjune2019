/* Array.cpp
Level2.5_Ex3: Creating Array Class

Source file that implements the Array class declared in the 
Array.h header file.

constructor uses the colon initialiser
default constructor creates a 10-element array
copy constructor does a deep copy
destructor deletes the dynamic array

 
 
The ToString() function makes use of the ToString() function of the
constituent points of the Line

The Length() function makes use of the Point::Distance(const Point&) function 
*/

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Array.h"			// Array class declaration

// constructor 
Array::Array(unsigned int arr_size)
	: m_data{ new Point[arr_size] }, m_arr_size{ arr_size } {}	// size of array set during runtime

// default constructor
Array::Array()
	: m_data{ new Point[ArraySize] }, m_arr_size{ ArraySize } {}	// size of array = class enum, ArraySize

// copy constructor
Array::Array(const Array& Other)
{
	m_arr_size = Other.Size();
	m_data = new Point[m_arr_size];		// create new array based on size of Other
	for (unsigned int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
		this->SetElement(Other.GetElement(i), i);

	//std::cout << "copy constructor built\n";
}

// destructor
Array::~Array()
{
	delete[] m_data;
}

// SetElement() method
void Array::SetElement(const Point& p, unsigned int index)
{
	//if (index >= 0 && index < m_arr_size)
	if (index < m_arr_size)
	{
		m_data[index] = p;
	}
	else
	{
		std::cout << "Invalid index : " << index << " : is out of range\n"
			<< "Valid range: 0 thru " << (m_arr_size - 1) << " inclusive"
			<< "\n" << p << "not added to the array\n";
	}	
}

// GetElement() method
Point& Array::GetElement(unsigned int index) const
{
	//if (index >= 0 && index < m_arr_size)
	if (index < m_arr_size)
	{
		return m_data[index];
	}
	else
	{
		std::cout << "Invalid index : " << index << " : is out of range\n"
			<< "Valid range: 0 thru " << (m_arr_size - 1) << " inclusive"
			<< "\nFirst element of the array returned\n";

		return m_data[0];
	}
}

// overloaded assignment operator
Array& Array::operator=(const Array& Other)
{
	const Array* p_other = &Other;
	if (this == p_other)
	{
		std::cout << "Attempting to self assign array at memory address: " 
			<< this << " to\n"
			<< "same address: " << p_other << "\n" 
			<< "Self assignment is not allowed\n"
			<< "Assignment aborted\n"
			<< "Array is unchanged\n";
		
		return *this;
	}
	else
	{
		// delete current array m_data;
		delete[] m_data;

		// create new m_data with size of Other
		m_arr_size = Other.Size();				// set member m_arr_size to size of Other
		m_data = new Point[m_arr_size];			// create new array
		for (unsigned int i = 0; i < m_arr_size; i++)	// deep copy Other's elements
		{
			//this->SetElement(Other.GetElement(i), i);
			m_data[i] = Other[i];	// this assignment uses the const Point& operator[]() const
									// function in order to proect the "Other" object from being
									// changed in this function
		}
		return *this;
	}
}

// overloaded array indexing operator: read/write version
Point& Array::operator[](unsigned int index)
{
	//if (index >= 0 && index < m_arr_size)
	if (index < m_arr_size)
	{
		return this->GetElement(index);
	}
	else
	{	
		std::cout << "Invalid index : " << index << " : is out of range\n"
			<< "Valid range: 0 thru " << (m_arr_size - 1) << " inclusive"
			<< "\nFirst element of the array returned\n";

		return this->GetElement(0);
	}
}


// overloaded array indexing operator: const version
const Point& Array::operator[](unsigned int index) const
{	
	// print the name of this function to show when it's called 
	std::cout << "Call to: " << __func__ << std::endl;

	if (index < m_arr_size)
	{
		return m_data[index];
	}
	else
	{
		std::cout << "Invalid index : " << index << " : is out of range\n"
			<< "Valid range: 0 thru " << (m_arr_size - 1) << " inclusive"
			<< "\nFirst element of the array returned\n";

		

		//return m_data[0];
		return (*this)[0];
	}
}


