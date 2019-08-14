/* EuropeanOptionException.h
Level3.6_Ex2: Exception Handling - Exception Objects

header file for the EuropeanOptionException class

Our EuropeanOptionException class supports an exception hierarchy with an 
EuropeanOptionException base class and an OutOfBoundsException derived class
We implement both exception classes in this header file for simplicity

The EuropeanOptionException has an abstract GetMessage() function that returns a 
std::string 
The InvalidOptionTypeException class has a constructor with an int as argument that
indicates the erroneous array index and store it in a data member
We override the GetMessage() function and let the implementation return a message
string saying the given index is out of bounds

Member data variables will be prefixed with 'm_' to signify the variable is a class member

private members:
DATA:
...

METHODS:
...

public members:
DATA:
...

METHODS:
EuropeanOptionException()		-	default constructor
~EuropeanOptionException()		-	destructor
GetMessage()			-	abstract method


*/

#ifndef EUROPEANOPTIONEXCEPTION_H_INCLUDED
#define EUROPEANOPTIONEXCEPTION_H_INCLUDED

#include <string>			// for return std::string in ToString() member function

// ArrayException class declaration: abstract base class (ABC)
class EuropeanOptionException
{
private:

public:
	EuropeanOptionException() {};					// do-nothing default constructor
	virtual ~EuropeanOptionException() {};			// destructor
	virtual std::string GetMessage() const = 0;		// pure virtual function: returns a string
};

// InvalidOptionTypeException class to handle invalid EuropeanOption type errors
class InvalidOptionTypeException : public EuropeanOptionException
{
private:
	std::string m_error_option;

public:
	InvalidOptionTypeException();							// default constructor
	InvalidOptionTypeException(std::string error_option);	// constructor
	virtual ~InvalidOptionTypeException();					// destructor
	virtual std::string GetMessage() const;					// getter method
};
	
// InvalidUnderlyingException class to handle invalid EuropeanOption underlying security type errors
class InvalidUnderlyingException : public EuropeanOptionException
{
private:
	std::string m_error_underlying;

public:
	InvalidUnderlyingException();							// default constructor
	InvalidUnderlyingException(std::string error_underlying);	// constructor
	virtual ~InvalidUnderlyingException();					// destructor
	virtual std::string GetMessage() const;					// getter method
};

// InvalidParameterValueException class to handle invalid parameter values: T = K = S = sig = 0
class InvalidParameterValueException : public EuropeanOptionException
{
private:
	std::string m_error_param_value;

public:
	InvalidParameterValueException();							// default constructor
	InvalidParameterValueException(std::string error_param_value);	// constructor
	virtual ~InvalidParameterValueException();					// destructor
	virtual std::string GetMessage() const;						// getter method
};

// InvalidValueException class to handle invalid values that may generate errors: in
// particular, divide by zero errors
class InvalidValueException : public EuropeanOptionException
{
private:
	std::string m_error_value;

public:
	InvalidValueException();							// default constructor
	InvalidValueException(std::string error_value);		// constructor
	virtual ~InvalidValueException();					// destructor
	virtual std::string GetMessage() const;				// getter method
};

#endif // EUROPEANOPTIONEXCEPTION_H_INCLUDED

