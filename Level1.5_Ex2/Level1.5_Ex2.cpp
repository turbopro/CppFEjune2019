// Level1.5_Ex2.cpp
//
// C program that that prints the factorials of a number.
// 6!(six factorial) is the same as 6 * 5 * 4 * 3 * 2 * 1
//
// Must make use of a recursive function.
//  
// Variables:
// - count_0 thru others = integers to store counts of characters
// - ch = char to store individual input characters

#include <stdio.h>

long int factorial(int input)
{
	if (input >= 1)
		return input * factorial(input - 1);
	else
		return 1;
}

int main(void)
{
	int num = 6;

	printf("\nFactorial of %d = %ld\n", num, factorial(num));

	return 0;
}