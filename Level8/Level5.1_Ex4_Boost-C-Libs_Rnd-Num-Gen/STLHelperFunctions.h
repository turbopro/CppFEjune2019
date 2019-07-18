/* STLHelperFunctions.h
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

header file for the STL Helper Functions class

Includes:

-	global function is_less_than() that takes a double value, determines if 
	the value is less than a pre-determined value, and returns a bool: true
	or false
	
	class LessThan stores a data member double threshold value; also includes
	an overloaded operator() function that accepts a double argument as input
	to be compared to the threshold data member, to return a bool: tru or 
	false

	is_less_than() and LessThan are used by count_if algorithm of the STL

-	template function definitions for use with STL containers: List, Vector, Map

	template functions 1 and 2 are the generic functions to sum the elements 
	of the respective containers.  
	
	function 1 calculates the sum with the container as argument  
	function 2 calculates the sum with iterators

	template functions 3 and 4 are specialisations that take care of Map
	containers

	function 3 calculates the sum with the Map container as argument
	function 4 calculates the sum with Map iterators

*/

#ifndef STLHELPERFUNCTIONS_H_INCLUDED
#define STLHELPERFUNCTIONS_H_INCLUDED

#include <string>			// for return std::string in ToString() member function
#include "Point.h"
#include <iostream>

// namespace declaration
namespace Turbopro
{
	namespace Containers
	{
		// is_less_than()
		// function to provide threshold level
		bool is_less_than(double value)
		{
			return value < 35;
		}
		
		// class 
		class LessThan
		{
		private:
			double threshold;			// threshold level
			static const int default_val = 35;

		public:
			LessThan() : threshold{ default_val } {}			// default constructor
			explicit LessThan(double val) : threshold{ val } {}	// constructor
			LessThan(const LessThan& Other)						// copy constructor
				: threshold(Other.threshold) {}
			~LessThan() {}										// destructor
			void SetThreshold(double new_val) { threshold = new_val; }	// setter
			double GetThreshold() const { return threshold; }	// getter
			LessThan& operator=(const LessThan& Other);			// overloaded assignment operator
			bool operator()(double entry) const;				// overloaded operator()()			
		};

		// overloaded operator=()
		LessThan& LessThan::operator=(const LessThan& Other)
		{
			if (this == &Other) { return *this; }
			else
			{
				threshold = Other.threshold;
				return *this;
			}
		}

		// overloaded operator()()
		bool LessThan::operator()(double entry) const
		{
			return entry < threshold;
		}

		
		// ::1::
		// template functions -- generic for List, Vector
		// Sum() definition for List and Vector, with container as argument
		// pass by reference for containers
		template <typename T>
		double Sum(const T& container)
		{
			double acc_sum = 0;				// initialise accumulator

			// set const_iterator, it, to end()
			// decrement it, and check if == begin()
			// dereference it and add to the accumulator
			// repeat until the loop terminates
			//for (auto it = container.end(); it-- != container.begin(); )
			for (typename T::const_iterator it = container.end(); it-- != container.begin(); )
				acc_sum += *it;

			// alternative that takes care of setting correct iterator type, makes good use
			// of rbegin() and rend(), and no need for decrementing
			//for (auto it = container.rbegin(); it != container.rend(); it++)
			//	acc_sum += *it;

			return acc_sum;
		}

		// ::2::
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

		// ::3::
		// template explicit specialisation for Map
		// Sum() definition for Map with container as argument
		template <>
		double Sum(const map<string, double>& container)
		{
			double acc_sum = 0;				// initialise accumulator

			// set const_iterator, it, to end()
			// decrement it, and check if == begin()
			// dereference it and add to the accumulator
			// repeat until the loop terminates
			//for (auto it = container.end(); it-- != container.begin(); )
			for (map<string, double>::const_iterator it = container.end(); it-- != container.begin(); )
				acc_sum += it->second;

			return acc_sum;
		}

		// ::4::
		// template explicit specialisation for Map
		// Sum() definition for Map with iterator range as argument
		template <>
		double Sum(map<string, double>::const_iterator start_it, map<string, double>::const_iterator end_it)
		{
			double acc_sum = 0;			// initialise accumulator

			// set specialisation type it, to start_it
			// use the it member access operator to access the map's double value
			// add the value to the accumulator
			// increment it
			// repeat until the loop terminates
			//for (auto it = start_it; it != end_it; it++)
			for (map<string, double>::const_iterator it = start_it; it != end_it; it++)
				acc_sum += it->second;

			return acc_sum;
		}
	}
}

#endif // STLHELPERFUNCTIONS_H_INCLUDED
