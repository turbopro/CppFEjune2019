// Level1.5_Ex4
//
// C program that uses a recursive function printnumber() which takes one 
// argument, an integer to be printed. The function prints the number digit 
// by digit by using the putchar() function
//
// Tips: Use the modulo operator (%) to determine the digit to print.
// Use the division operator ( / ) to calculate the argument for the 
// recursive call. Don’t forget to handle negative numbers correctly.
//
// Variables:
// - number = integer store for number
// 
// Functions:
// printnumber = recursive function to print a number digit by digit
// 

#include <stdio.h>

void printnumber(int number);

int main(void)
{
	int number = 246813579;

	printnumber(number);
	putchar('\n');

	return 0;
}

void printnumber(int number)
{
	if (number < 0)
	{
		putchar('-');
		number = -number;
	}
	
	if (number / 10)
		printnumber(number / 10);

	putchar(number % 10 + '0');
}