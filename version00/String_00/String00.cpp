/* String00.h

Source/implementation file for String class in C++ Primer Plus 6ED, Pg 652

Good example of C array and string issues handled in C++ class

i:	C++ nullptr

int* p_x = nullptr;

ii  Methods:

Default constructor
Constructor
Copy Constructor
Destructor

Length()
friend bool operator<()
friend bool operator>()
friend bool operator==()
friend operator>>(istream&, String& st)
char& operator[](int)
const char& operator[](int) const
static int HowMany()

*/

#include <cstring>
#include "String00.h"

using std::cin;
using std::cout;

// initialise static class member
int String::num_strings;

// static method
int String::HowMany()
{
	return num_strings;
}

// class methods
String::String(const char* s)
{
	len = std::strlen(s);
	str = new char[1];
	std::strcpy(str, s);
	num_strings++;
}