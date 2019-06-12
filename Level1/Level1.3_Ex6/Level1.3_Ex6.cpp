// Level1.3_Ex6.cpp
// 
// C program that shifts any number two places to the right. 
// Input should be an integer. Output should be the shifted result, 
// as well as output an indication of whether a logical or arithmetic 
// shift is performed (if a 1 or 0 is shifted in at the left side) 
// for the inputted number. 
//
// For more info and example, see Logical shift - Wikipedia
// 

#include <stdio.h>

int main(void)
{
	int number;
	int result = 0, shift = 2;

	printf("Enter number to be shifted: \n");
	scanf_s("%d", &number);

	result = number >> shift;

	printf("\n%d shifted two digits to the right = %d\n", number, result);
	if((result < 0 && number < 0) || (result > 0 && number > 0))
		printf("This was an arithmetic shift\n");
	else
		printf("This was a logical shift\n");

	return 0;
}