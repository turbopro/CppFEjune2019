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
			: m_array{ Array<TStack>(arr_size) }, m_current{ 0 }		//{}	// size of array set during runtime
		{
			std::cout << "Stack constructor\n";
		}
		
		// default constructor 
		//template <typename TStack>
		template <typename TStack>
		Stack<TStack>::Stack()
			: m_array { Array<TStack>() }, m_current{ 0 }		//{}	// size of array set during runtime
		{
			std::cout << "Stack default constructor\n";
		}

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack>
		Stack<TStack>::Stack(const Stack<TStack>& Other)
			: m_array { Other.m_array }, m_current { Other.m_current }
		{
			std::cout << "Stack copy constructor: Other m_index: " << Other.m_current
				<< ", this m_index: " << m_current << std::endl;
		}

		// destructor
		template <typename TStack>
		Stack<TStack>::~Stack()
		{
			std::cout << "Deleting Stack...\n";
		}

		// pop() an element offf the Stack
		template <typename TStack>
		TStack Stack<TStack>::pop()
		{
			if (m_current <= 0)
				m_array.GetElement(m_current - 1);
			else
			{
				TStack ele = m_array.GetElement(m_current - 1);
				m_current--;
				return ele;
			}
		}

		// push() an element onto the Stack
		template <typename TStack>
		void Stack<TStack>::push(const TStack& ele)
		{
			if (m_current >= this->Size())
				m_array.SetElement(ele, m_current);
			else
			{
				(m_array.SetElement(ele, m_current));
				m_current++;
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