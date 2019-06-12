// Level1.5_Ex1
//
// C program that that calls a function minus(). This function receives two 
// arguments and returns the difference (regular subtraction, not absolute). 
// This difference should be printed on screen.
//  
// Variables:
// - count_0 thru others = integers to store counts of characters
// - ch = char to store individual input characters
//

#include <stdio.h>

float minus(float op1, float op2)
{
	return op1 - op2;
}

int main(void)
{
	float operand1 = 50.0, operand2 = 10, result;
	printf("operand1: %.1f, operand2: %.1f\n", operand1, operand2);

	result = minus(operand1, operand2);
	printf("\n%.1f - %.1f = %.1f\n", operand1, operand2, result);

	return 0;
}