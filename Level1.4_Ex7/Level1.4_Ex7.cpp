// Level1.4_Ex7
//
// C program that counts how many times each of the numbers 0-4 have been typed. 
// Use a switch-case construction. Use default to count the number of other 
// characters. The input will be halted with ^Z (EOF). EOF means End-of-File and 
// is defined in <stdio.h>. Thus, the constant EOF can be used in a condition 
// (test if EOF has been typed).
// 
// The frequency of number 3 is shown in words.
// E.g.: Number three appears two times.
//
// Only print the frequency when it is smaller than three. If the frequency is 
// three or larger, then print : "The number three appears more than two times."
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
	
	switch (count_3)
	{
		case 0: printf("\nNumber three appears zero times.\n");
			break;
		case 1: printf("\nNumber three appears one time.\n");
			break;
		case 2: printf("\nNumber three appears two times.\n");
			break;
		default: printf("\nNumber three appears more than two times.\n");
	}

	return 0;
}