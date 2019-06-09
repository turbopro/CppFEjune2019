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

	if (MAX2(x, y) == x)
		printf("x (%d) is greater than y (%d)\n", x, y);
	else
		printf("y (%d) is greater than x (%d)\n", y, x);

	if (MAX3(x, y, z) == x)
		printf("x (%d) is greater than y (%d) and z (%d)\n", x, y, z);
	else if (MAX3(x, y, z) == y)
		printf("y (%d) is greater than x (%d) and z (%d)\n", y, x, z);
	else
		printf("z (%d) is greater than x (%d) and y (%d)\n", z, x, y);

	return 0;
}