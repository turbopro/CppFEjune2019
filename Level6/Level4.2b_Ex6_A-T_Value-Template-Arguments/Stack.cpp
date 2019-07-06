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
		// default constructor 
		template <typename TStack, int sz>
		Stack<TStack, sz>::Stack() : m_array { Array<TStack>(sz) }, m_current{ 0 } {}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack, int sz>
		Stack<TStack, sz>::Stack(const Stack<TStack, sz>& Other)
			: m_array { Other.m_array }, m_current { Other.m_current } {}

		// destructor
		template <typename TStack, int sz>
		Stack<TStack, sz>::~Stack() {}

		// pop() an element offf the Stack
		template <typename TStack, int sz>
		TStack Stack<TStack, sz>::pop()
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
		template <typename TStack, int sz>
		void Stack<TStack, sz>::push(const TStack& ele)
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
		template <typename TStack, int sz>
		Stack<TStack, sz>& Stack<TStack, sz>::operator=(const Stack<TStack, sz>& Other)
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