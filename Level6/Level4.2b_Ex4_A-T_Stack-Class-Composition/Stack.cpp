/* Stack.cpp
Level4.2b_Ex4: Advanced Templates - Stack Class (composition)

Source file that implements the Stack class declared in the
Stack.h header file.

the Stack class is part of the Turbopro::Container namespace

*/

#ifndef STACK_CPP_INCLUDED
#define STACK_CPP_INCLUDED

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Stack.h"			// Array class declaration
#include "ArrayException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructors delegate construction of storage Array to base class template Array<TArray>
		// constructor
		template <typename TStack>
		Stack<TStack>::Stack(int arr_size) : m_array(Array<TStack>(arr_size)), m_current(0) {}
		
		// default constructor 
		template <typename TStack>
		Stack<TStack>::Stack() : m_array(Array<TStack>()), m_current(0) {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack>
		Stack<TStack>::Stack(const Stack<TStack>& Other) : m_array(Other.m_array), m_current(Other.m_current) {}

		// destructor
		template <typename TStack>
		Stack<TStack>::~Stack() {}

		// pop() an element off the Stack
		template <typename TStack>
		TStack Stack<TStack>::pop()
		{
			TStack ele = m_array[m_current - 1];	// get element: Array handles indexing errors
			--m_current;							// update index: Array indexed ok  

			return ele;
		}

		// push() an element onto the Stack
		template <typename TStack>
		void Stack<TStack>::push(const TStack& ele)
		{
			m_array[m_current] = ele;				// set element: Array handles indexing errors
			++m_current;							// update index: Array indexed ok
		}
		
		// overloaded assignment operator
		template <typename TStack>
		Stack<TStack>& Stack<TStack>::operator=(const Stack<TStack>& Other)
		{		
			if (this == &Other) { return *this; }
			else
			{
				// Array does the ground work
				*this = Other;

				return *this;
			}
		}
	}
}
#endif // STACK_CPP_INCLUDED