// stringLength.c
// Level1.7_Ex2
//
// C program that reads a string with a 30 character maximum. 
// Implement the Length() function. The function Length() must 
// determine the length of the string. Give Length() the 
// address of the array as argument.
//
// Note: your Length() function should be similar to the 
// built-in strlen() function so your job is to mimic that 
// function without using it.
//
// EOF is used in the function main(). This means End-of-File 
// and is discussed later on in this document. In DOS, EOF can 
// be entered by the key combination Ctrl - z(often written 
// as ^Z).  With ^Z(Say : control Z) is meant pressing the 
// control - key and the z - key simultaneously.
//

/* Calculate the length of a string */

#include <stdio.h>

#define MAXLINE 30

// String length declaration
int Length(char str[]);

int main()
{
	char string[MAXLINE + 1]; // Line of maximum 30 chars + \0
	int c; // The input character
	int i = 0; // The counter

	// Print intro text
	printf("Type up to %d chars. Exit with ^Z\n", MAXLINE);

	// Get the characters
	while ((c = getchar()) != EOF && i < MAXLINE)
	{
		// Append entered character to string
		string[i++] = (char)c;
	}
	string[i] = '\0'; // String must be closed with \0

	printf("String length is %d\n", Length(string));

	return 0;
}

int Length(char str[])
{
	int i = 0;			// string indexer
	while (str[i])		// loop until '\0' character 
	{
		i++;
	}

	return i;
}

