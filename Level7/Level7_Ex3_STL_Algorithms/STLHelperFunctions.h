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
		bool is_less_than(double value)
		{
			return value < 35;
		}
		
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
	}
}

#endif // STLHELPERFUNCTIONS_H_INCLUDED
