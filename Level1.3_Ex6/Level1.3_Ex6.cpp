// Level1.3_Ex6.cpp -- use shift operator
//
// Shift any integer two places to the right, and, indicate
//  whether logical or arithmetic shift

#include <stdio.h>
#include <limits.h>

int main(void)
{
	int number;
	int result = 0, shift = 2;

	printf("Enter number to be shifted: \n");
	scanf_s("%d", &number);

	result = number >> shift;

	printf("%d shifted two digits to the right = %d\n", number, result);
	if((result < 0 && number < 0) || (result > 0 && number > 0))
		printf("This was an arithmetic shift\n");
	else
		printf("This was a logical shift\n");

	return 0;
}