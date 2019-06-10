// Max2and3.c
// Level1.6_Ex2
//
// C program that create two macros MAX2(x,y) and MAX3(x,y,z). 
// These macros must return the maximum value of the given arguments. 
// Let the macro MAX3 make use of the macro MAX2.
//

#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

int main()
{
	int x = 100, y = 15, z = 500;

	printf("Variable values are\n");
	printf("x:\t%d\ny:\t%d\nz:\t%d\n", x, y, z);
	
	printf("\n\nWhen we run macro MAX2 with arguments x and y, we get:\n");
	if (MAX2(x, y) == x)
		printf("\nx (%d) is greater than y (%d)\n", x, y);
	else
		printf("\ny (%d) is greater than x (%d)\n", y, x);

	printf("\n\nWhen we run macro MAX3 with arguments x, y and z, we get:\n");
	if (MAX3(x, y, z) == x)
		printf("\nx (%d) is greater than y (%d) and z (%d)\n", x, y, z);
	else if (MAX3(x, y, z) == y)
		printf("\ny (%d) is greater than x (%d) and z (%d)\n", y, x, z);
	else
		printf("\nz (%d) is greater than x (%d) and also greater than y (%d)\n", z, x, y);

	return 0;
}