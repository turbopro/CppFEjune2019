/* String00.h

Header file for String class in C++ Primer Plus 6ED, Pg 652

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

#ifndef STRING00_H_INCLUDED
#define STRING00_H_INCLUDED

#include <iostream>

using std::ostream;
using std::istream;

class String
{
	private:
		char* str;								// pointer to string
		int len;								// length of string
		static int num_strings;					// number of objects
		static const int CINLIM = 80;			// cin input limit

	public:
		// constructors and other methods
		String(const char* s);					// constructor
		String();								// default constructor
		String(const String&);					// copy constructor
		~String();								// destructor

		int length() const { return len; }		// inlined method to return length of the string

		// overloaded operators
		String& operator=(const String&);		// assignment operator for String object
		String& operator=(const char*);			// assignment operator for string
		char& operator[](int i);				// array indexing
		const char& operator[](int i) const;	// array indexing, const version

		// overloaded friend operators
		friend bool operator<(const String& s1,	//	test less than
			const String& s2);
		friend bool operator>(const String& s1,	//	test greater than
			const String& s2);
		friend bool operator==(const String& s1,//	test eual to
			const String& s2);
		friend ostream& operator<<(ostream& os,	//	allow cout
			const String& s);
		friend ostream& operator>>(istream& os,	//	allow cin
			const String& s);

		// static function
		static int HowMany();
};


#endif // STRING00_H_INCLUDED




