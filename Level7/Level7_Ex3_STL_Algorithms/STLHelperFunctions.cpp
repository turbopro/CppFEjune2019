/* STLHelperFunctions.cpp
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

Source file that implements the STLHelperFunctions class declared in the
STLHelperFunctions.h header file.

the STLHelperFunctions class is part of the Turbopro::Container namespace

*/

#ifndef STLHELPERFUNCTIONS_CPP_INCLUDED
#define STLHELPERFUNCTIONS_CPP_INCLUDED

#include <iostream>
#include <string>				// for std::string() function in ToString() member function
//#include "STLHelperFunctions.h"	// ArrayException class declaration


// STL
#include <vector>			// for vector, copy
#include <list>
#include <map>
#include <iterator>			// for iter
#include <algorithm>
#include <numeric>			// std::accumulate

// create namespace
namespace Turbopro
{
	namespace Containers
	{
		// template functions -- generic for List, Vector
		// Sum() definition for List and Vector, with container as argument
		template <typename T>
		double Sum(const T& container)
		{
			double acc_sum = 0;				// initialise accumulator

			// set const_iterator, it, to end()
			// decrement it, and check if == begin()
			// dereference it and add to the accumulator
			// repeat until the loop terminates
			for (typename T::const_iterator it = container.end(); it-- != container.begin(); )
				acc_sum += *it;

			// alternative that takes care of setting correct iterator type, makes good use
			// of rbegin() and rend(), and no need for decrementing
			//for (auto it = container.rbegin(); it != container.rend(); it++)
			//	acc_sum += *it;

			return acc_sum;
		}


		// Sum() definition for List and Vector, with iterator range argument
		// pass by value for iterators
		template <typename T>
		double Sum(const typename T start_it, const typename T end_it)
		{
			double acc_sum = 0;			// initialise accumulator

			// set type T iterator, it, to start_it
			// dereference it and add to the accumulator
			// increment it
			// repeat until the loop terminates
			for (T it = start_it; it != end_it; it++)
				acc_sum += *it;

			return acc_sum;
		}

		// template explicit specialisation for Map
		// Sum() definition for Map with container as argument
		template <T>
		double Sum(const map<string, double>& container)
		{
			double acc_sum = 0;				// initialise accumulator

			// set const_iterator, it, to end()
			// decrement it, and check if == begin()
			// dereference it and add to the accumulator
			// repeat until the loop terminates
			for (typename map<string, double>::const_iterator it = container.end(); it-- != container.begin(); )
				acc_sum += it->second;

			return acc_sum;
		}

		// template explicit specialisation for Map
		// Sum() definition for Map with iterator range as argument
		template <T>
		double Sum(typename map<string, double>::const_iterator start_it, typename map<string, double>::const_iterator end_it)
		{
			double acc_sum = 0;			// initialise accumulator

			// set specialisation type it, to start_it
			// use the it member access operator to access the map's double value
			// add the value to the accumulator
			// increment it
			// repeat until the loop terminates
			for (map<string, double>::const_iterator it = start_it; it != end_it; it++)
				acc_sum += it->second;

			return acc_sum;
		}		
	}
}
#endif // STLHELPERFUNCTIONS_CPP_INCLUDED