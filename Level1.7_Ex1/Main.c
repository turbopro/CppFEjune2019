// Main.c
// Level1.7_Ex1
//
// C program to swap two integers. This main() function 
// calls the Swap() function to effect the swap of the 
// integers. The integers are declared, initialised and 
// printed in this function. 
//
// Use pointers as arguments for the Swap()function.
//
// Include 'Swap.h' for Swap() function definition.
// Source file, 'Swap.c', has the Swap() function definition.
//

#include <stdio.h>
#include "Swap.h"

int main(void)
{
	int x = 10, y = 20;
	
	// for completeness, we create pointers for Swap() function arguments
	int* px = &x;		// declare and assign pointers to integers
	int* py = &y;

	// for concision, as an alternative, we may call Swap() by passing the 
	// address of the integer variables, x and y to the function
	// Swap(&x, &y);

	printf("Original values,\n");
	printf("x:\t%d\ny:\t%d\n", x, y);
	Swap(px, py);			// call function with pointers as arguments
	printf("\nAfter Swap() applied,\n");
	printf("x:\t%d\ny:\t%d\n", x, y);

	return 0;
}