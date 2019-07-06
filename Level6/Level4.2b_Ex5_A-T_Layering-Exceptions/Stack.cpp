/* Stack.cpp
Level4.2b_Ex5: Advanced Templates - Layering Exceptions

Source file that implements the Stack class declared in the
Stack.h header file.

the Stack class is part of the Turbopro::Container namespace

*/

#ifndef STACK_CPP_INCLUDED
#define STACK_CPP_INCLUDED

#include <iostream>
#include <string>			// for std::string() function in ToString() member function
#include "Stack.h"			// Array class declaration
#include "StackException.h"	// ArrayException class declaration


// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// constructor
		template <typename TStack>
		Stack<TStack>::Stack(int arr_size)
			: m_array{ Array<TStack>(arr_size) }, m_current{ 0 } {}

		// default constructor 
		template <typename TStack>
		Stack<TStack>::Stack() : m_array { Array<TStack>() }, m_current{ 0 } {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack>
		Stack<TStack>::Stack(const Stack<TStack>& Other)
			: m_array { Other.m_array }, m_current { Other.m_current } {}

		// destructor
		template <typename TStack>
		Stack<TStack>::~Stack() {}

		// pop() an element offf the Stack
		template <typename TStack>
		TStack Stack<TStack>::pop()
		{
			// if current index is 0 or less, throw StackEmptyException
			if (m_current <= 0)
				throw StackEmptyException(m_current);
			else
			{
				TStack ele = m_array.GetElement(m_current - 1);	// pop
				m_current--;									// update index
				
				return ele;
			}
		}

		// push() an element onto the Stack
		template <typename TStack>
		void Stack<TStack>::push(const TStack& ele)
		{
			// if current index is Stack.Size() or greater, throw StackFullException
			if (m_current >= Size())
				throw StackFullException(m_current);
			else
			{
				m_array.SetElement(ele, m_current);				// push
				m_current++;									// update index
			}
		}
		
		// overloaded assignment operator
		template <typename TStack>
		Stack<TStack>& Stack<TStack>::operator=(const Stack<TStack>& Other)
		{		
			if (this == &Other) { return *this; }
			else
			{
				m_array = Other.m_array;
				m_current = Other.m_current;

				return *this;
			}
		}
	}
}
#endif // STACK_CPP_INCLUDED