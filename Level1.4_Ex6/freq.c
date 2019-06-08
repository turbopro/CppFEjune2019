// freq.c 
// C program that counts how many times each of the numbers 0-4 have been typed. 
// Use a switch-case construction. Use default to count the number of other 
// characters. The input will be halted with ^Z (EOF). EOF means End-of-File and 
// is defined in <stdio.h>. Thus, the constant EOF can be used in a condition 
// (test if EOF has been typed).
// Print the amount of times a certain number has been typed.
//
// Name the program freq.c
//  
// Variables:
// - count_0 thru others = integers to store counts of characters
// - ch = char to store individual input characters

#include <stdio.h>

int main(void)
{
	int count_0 = 0, count_1 = 0, count_2 = 0,
		count_3 = 0, count_4 = 0, others = 0;
	char ch;

	printf("Please enter some text\nCtrl-Z to end input\n");
	while ((ch = getchar()) != EOF)
	{
		switch (ch)
		{
		case '0': count_0++;
			break;
		case '1': count_1++;
			break;
		case '2': count_2++;
			break;
		case '3': count_3++;
			break;
		case '4': count_4++;
			break;
		default: others++;
		}
	}

	printf("zero (0) was typed: %d times\n", count_0);
	printf("one (1) was typed: %d times\n", count_1);
	printf("two (2) was typed: %d times\n", count_2);
	printf("three (3) was typed: %d times\n", count_3);
	printf("four (4) was typed: %d times\n", count_4);
	printf("all other characters were typed: %d times\n", others);


	return 0;
}
