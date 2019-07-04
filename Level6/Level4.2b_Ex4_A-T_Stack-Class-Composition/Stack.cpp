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
		// default constructor 
		template <typename TStack, int sz>
		Stack<TStack, sz>::Stack()
			: m_array { Array<TStack>(sz) }, m_index{ 0 }		//{}	// size of array set during runtime
		{
			std::cout << "Stack default constructor\n";
		}

		/*
		// default constructor
		template <typename TStack, int sz>
		Stack<TStack, sz>::Stack()
			: m_array{ Array<TStack>(sz) }, m_index{ 0 }	// {}	// size of array = ArraySize
		{
			std::cout << "Stack default constructor\n";
		}
		*/

		// copy constructor: set m_arr_size, create m_data, deep copy elements
		template <typename TStack, int sz>
		Stack<TStack, sz>::Stack(const Stack<TStack, sz>& Other)
			: m_array { Other.m_array }, m_index { Other.m_index }
		{
			std::cout << "Stack copy constructor\n";
		}

		// destructor
		template <typename TStack, int sz>
		Stack<TStack, sz>::~Stack()
		{
			std::cout << "Deleting Stack...\n";
		}

		// pop() an element offf the Stack
		template <typename TStack, int sz>
		TStack Stack<TStack, sz>::pop(int index)
		{
			
		}

		// push() an element onto the Stack
		template <typename TStack, int sz>
		TStack Stack<TStack, sz>::push(int index)
		{

		}
		
		// overloaded assignment operator
		template <typename TStack, int sz>
		Stack<TStack, sz>& Stack<TStack, sz>::operator=(const Stack<TStack, sz>& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				//Array<TStack>::operator=(Other);
				//for (int i = 0; i < Other.Size(); i++)
				//	this->SetElement(Other[i], i);

				//return *this;

				// delete current array m_data;
				//delete[] m_array;

				// create new m_array with size of Other
				int arr_size = Other.Size();			// set member m_arr_size to size of Other
				m_array = new Array<TStack>(arr_size);	// create new array
				for (int i = 0; i < arr_size; i++)		// deep copy Other's elements
				{
					m_array[i] = Other[i];
				}
				return *this;
			}
		}
		
	}
}
#endif // STACK_CPP_INCLUDED