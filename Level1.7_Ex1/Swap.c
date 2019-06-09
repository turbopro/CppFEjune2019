// Swap.c
// Level1.7_Ex1
//
// C source file with function Swap(). This function exchanges 
// the value of two variables. For example: if i=123 and j=456, 
// then i=456 and j=123 after the Swap() function has been called. 
// The variables i and j are declared, initialised and printed in 
// the function main(). 
//
// Use pointers as arguments for the Swap()function.
//

#include "Swap.h"

void Swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;	
}

