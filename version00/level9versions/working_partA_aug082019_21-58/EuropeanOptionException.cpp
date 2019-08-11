/* EuropeanOptionException.cpp
Level3.6_Ex2: Exception Handling - Exception Objects

Source file that implements the ArrayException class declared in the
EuropeanOptionException.h header file.

All constructors and the destructor use the colon syntax initialisation

The sstream and string libraries are used to convert the data member to
its string representation

The EuropeanOptionException and InvalidOptionTypeException classes

*/

#include <iostream>
#include <string>				// for std::string() function in ToString() member function
#include <sstream>				// for std::ostringstream() function in GetMessage() method
#include "EuropeanOptionException.h"

// ***** InvalidOptionTypeException *****
// constructor InvalidOptionTypeException
InvalidOptionTypeException::InvalidOptionTypeException(std::string error_option)
	: m_error_option{ error_option } {}

// default constructor
InvalidOptionTypeException::InvalidOptionTypeException() : m_error_option{ "" } {}

// destructor
InvalidOptionTypeException::~InvalidOptionTypeException() {}

// GetMessage() method
std::string InvalidOptionTypeException::GetMessage()const
{
	return ("\nInvalid option type: - " + m_error_option +
		" -\nOption type must be either of - C - or - P -\n");	
}

// ***** InvalidUnderlyingException *****
// constructor InvalidUnderlyingException
InvalidUnderlyingException::InvalidUnderlyingException(std::string error_underlying)
	: m_error_underlying{ error_underlying } {}

// default constructor
InvalidUnderlyingException::InvalidUnderlyingException() : m_error_underlying{ "" } {}

// destructor
InvalidUnderlyingException::~InvalidUnderlyingException() {}

// GetMessage() method
std::string InvalidUnderlyingException::GetMessage()const
{
	return ("\nInvalid underlying security type: - " + m_error_underlying +
		" -\nValid underlying security types:\n\tStock\n\tIndex\n\tFuture\n\tCurrency\n");
}

// ***** InvalidParameterValueException *****
// constructor InvalidParameterValueException
InvalidParameterValueException::InvalidParameterValueException(std::string error_param_value)
	: m_error_param_value{ error_param_value } {}

// default constructor
InvalidParameterValueException::InvalidParameterValueException() : m_error_param_value{ "" } {}

// destructor
InvalidParameterValueException::~InvalidParameterValueException() {}

// GetMessage() method
std::string InvalidParameterValueException::GetMessage()const
{
	return ("\nInvalid parameter value : - " + m_error_param_value +
		" -\nParameters T, K, S, sig cannot be '0'\n");
}