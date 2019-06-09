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

#include <stdio.h>
#include "Swap.h"

int main(void)
{
	int x = 10, y = 20;

	printf("Original values x: %d, and y: %d\n", x, y);
	Swap(&x, &y);
	printf("\nAfter Swap() applied, x: %d, and y: %d\n", x, y);

	return 0;
}