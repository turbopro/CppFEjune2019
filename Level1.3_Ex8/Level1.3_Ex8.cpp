// Level1.3_Ex8 -- Assignment operator
//
// display out via comments

#include <stdio.h>

int main(void)
{
	int x = 2;
	int y;
	int z;
								// output
	x *= 3 + 2;
	printf("x=%d\n", x);		// x = 10

	x *= y = z = 4;
	printf("x=%d\n", x);		// x = 40

	x = y == z;
	printf("x=%d\n", x);		// x = 1
	
	return 0;
}