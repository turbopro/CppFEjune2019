// Level1.8_Ex1
//
// C program that prints the contents of a struct called Article. 
// An Article has the following characteristics:​
// - Article number
// - Quantity
// - Description(20 characters)
//
// The test program must create an Article of which the contents 
// are assigned at initialization level.
//
// Printing the Article is done with a Print() function.This 
// function gets the address of the structure as a parameter.
//
// Tip: Suppose that p is the pointer to the structure. It will 
// allow the fields to be printed by (*p).fieldname or 
// p->fieldname.
//

#include <stdio.h>
#include "Structs.h"

int main(void)
{
	// create an article 
	Article art1 =
	{
		1239, 54, "Man Bites Dog!"
	};

	Print(&art1);		// pass the address of 'art1' to Print
	
	return 0;
}

