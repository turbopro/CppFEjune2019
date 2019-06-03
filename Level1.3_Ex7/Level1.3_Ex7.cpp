// Level1.3_Ex7.cpp -- use shift operator as efficient multiplier
//
// Left shift operator multiplies an integer by a factor of 2 for 
//  each shift left

#include <stdio.h>

int main(void)
{
	int number = -128, n = 4;

	printf("%d * 2^%d = %d\n", number, n, (number << 4));

	return 0;
}