// Level1.3_Ex4
//
// C program that uses the fact that 0 (zero) is interpreted as FALSE 
// and non-zero is interpreted as TRUE. The C-program can be made easier 
// to read when this 0 (or non-zero) is assigned to a variable e.g. an 
// int called married. 
//
// Use the ?: operator to print if someone is married or not. 
// We will use a single printf statement
//
// Create and assign 0 or > 0 to an int variable, "greed_is_good"
//
// print to the screen "No" if variable is 0, and "Yes" if otherwise
//

#include <stdio.h>

int main(void)
{
	// we will ask these famous actors a couple questions
	int greed_is_good;
	int smell_of_napalm;
	
	printf("Mr. Gekko, is greed good? '0' for No, '1' for Yes: ");
	scanf_s("%d", &greed_is_good);
	// we use the conditional operator for concision
	printf("%s\n", (greed_is_good ? "Yes, it is indeed!" : "No way, no how!") );

	printf("\nCol Kilgore, do you love the smell of napalm in the morning? '0' for No, '1' for Yes: ");
	scanf_s("%d", &smell_of_napalm);
	printf("%s\n", (smell_of_napalm ? "[Yes]... Smells like, victory." : "No thanks."));

	return 0;
}