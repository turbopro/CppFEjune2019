/* Stack.cpp
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

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
		// constructors delegate construction of storage Array to base class template Array<TArray>
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

		// pop() an element off the Stack
		template <typename TStack, int sz>
		TStack Stack<TStack, sz>::pop()
		{
			// catch Array OutOfBoundsException, rethrow StackEmptyException to main()
			try
			{
				// get element: Array throws exception for indexing error
				TStack ele = m_array[m_current - 1];
				--m_current;							// update index: Array indexed ok  

				return ele;
			}
			catch (ArrayException& error_msg)			// catch ArrayException
			{
				throw StackEmptyException(m_current);	// throw StackException
			}
		}

		// push() an element onto the Stack
		template <typename TStack, int sz>
		void Stack<TStack, sz>::push(const TStack& ele)
		{
			// catch Array OutOfBoundsException, rethrow StackFullException to main()
			try
			{
				// set element: Array throws exception for indexing error
				m_array[m_current] = ele;
				++m_current;							// update index: Array indexed ok
			}
			catch (ArrayException& error_msg)			// catch ArrayException
			{
				throw StackFullException(m_current);	// throw StackException
			}
		}
		
		// overloaded assignment operator
		template <typename TStack, int sz>
		Stack<TStack, sz>& Stack<TStack, sz>::operator=(const Stack<TStack, sz>& Other)
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