// Level1.3_Ex7.cpp
//
// C program that efficiently multiplies a number by a factor 2 to the power n. 
// The number to multiply and n are variables, which get a value at the start 
// of the program. 
//
// Clue:
//
// 1 shift to the left is the same as multiplying by 2.
// 2 shifts to the left are the same as multiplying by 4.
// 3 shifts to the left are the same as multiplying by 8.
//
// Left shift operator multiplies an integer by a factor of 2 for 
//  each shift left
//

#include <stdio.h>

int main(void)
{
	int number = -128, shift = 5;

	printf("%d * 2^%d = %d\n", number, shift, (number << shift));

	return 0;
}