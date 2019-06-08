// Level1.5_Ex2.cpp
//
// C program that that prints the factorials of a number.
// 6!(six factorial) is the same as 6 * 5 * 4 * 3 * 2 * 1
//
// Must make use of a recursive function.
//  
// Variables:
// - number = integer store for number
// 
// Functions:
// factorial = recursive function to calculate the factorial of an integer
//             

#include <stdio.h>

long int factorial(int number)
{
	if (number >= 1)
		return number * factorial(number - 1);
	else
		return 1;
}

int main(void)
{
	int number = 6;

	printf("\nFactorial of %d = %ld\n", number, factorial(number));

	return 0;
}