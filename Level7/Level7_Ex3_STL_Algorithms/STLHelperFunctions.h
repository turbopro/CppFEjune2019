/* STLHelperFunctions.h
Level7_Ex3: Overview of the Standard Template Library - STL Algorithms

header file for the STL Helper Functions class

Our Templated Array class has three private data members:
· a dynamic array of templated TArray objects
· an integer for the size of the array
· and a static int for the size of the default constructor

We will make the templatised Array glass as generic as posible so
we may use it as a general purpose containers for several types of
objects: e.g., numeric objects, string objects, other array objects

The array will have:

· Default constructor (allocate 10 elements; store value as static data member)
· Constructor
· Copy constructor
· Destructor
· Size method
· Assignment operator
· Getter method
· Setter method
· Static Getter/Setter methods for the static data member

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
			return (value < 35 ? true : false);
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
			LessThan& operator=(const LessThan& Other);			// overloaded assignment operator: Shape& operator=(const Shape& Other)
			bool operator()(double entry) const;				// overloaded operator()()			
		};

		// initialise static data member
		//double LessThan::default_val = 35.0;

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
			return (entry < threshold ? true : false);
		}
		
	}
}

#endif // STLHELPERFUNCTIONS_H_INCLUDED
