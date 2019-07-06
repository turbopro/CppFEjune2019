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
		// constructor
		template <typename TStack>
		Stack<TStack>::Stack(int arr_size)
			: m_array{ Array<TStack>(arr_size) }, m_current{ 0 } {}	// size of array set during runtime
		
		// default constructor 
		template <typename TStack>
		Stack<TStack>::Stack()
			: m_array { Array<TStack>() }, m_current{ 0 } {}		// size of array set during runtime

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack>
		Stack<TStack>::Stack(const Stack<TStack>& Other)
			: m_array { Other.m_array }, m_current { Other.m_current } {}

		// destructor
		template <typename TStack>
		Stack<TStack>::~Stack() {}

		// pop() an element off the Stack
		template <typename TStack>
		TStack Stack<TStack>::pop()
		{
			// if current index is 0 or less, Stack is empty
			// next pop() will generate Array OutOfBoundsException
			if (m_current <= 0)
				m_array.GetElement(m_current - 1);
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
			// if current index is Stack.size() or greater, Stack is full
			// next push() will generate Array OutOfBoundsException
			if (m_current >= this->Size())
				m_array.SetElement(ele, m_current);
			else
			{
				(m_array.SetElement(ele, m_current));	// push
				m_current++;							// update index
			}
		}
		
		// overloaded assignment operator
		template <typename TStack>
		Stack<TStack>& Stack<TStack>::operator=(const Stack<TStack>& Other)
		{		
			if (this == &Other) { return *this; }
			else
			{
				// Array does most of the hard ground work
				m_array = Other.m_array;
				m_current = Other.m_current;

				return *this;
			}
		}
	}
}
#endif // STACK_CPP_INCLUDED