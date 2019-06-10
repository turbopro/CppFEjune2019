// Level1.9_Ex1
//
// C program that reads the characters from the keyboard and shows 
// them on screen (the inputted characters should only be displayed 
// when the user hits 'enter', line by line).
//
// When ^A is entered, the program must end properly.Then the 
// following message will appear : “CTRL + A is a correct ending.”
//
// Tip : getchar() readsand putchar() writes the type int.The value 
// of ^A is 1.
//

#include <stdio.h>

#define BUFFER_SIZE 100

int main(void)
{
	char input_buffer[BUFFER_SIZE];
	int ch;
	int i = 0;

	printf("Please enter some text, line by line\n");
	printf("Hit Enter at the end of the line to display the text\n");
	printf("Maximum number of characters per line: %d\n", BUFFER_SIZE);
	printf("Ctrl-A to quit\n");
	while ( (ch = getchar()) != 1 && i < BUFFER_SIZE )		// Ctrl-Shift-A == 1
	{
		if (ch == '\n')			// if newline, terminate string array, print line
		{						
			input_buffer[i] = '\0';
			printf("%s\n", input_buffer);
			i = 0;				// reset i to 0 for the start of input_buffer
			continue;
		}
		else
		{
			input_buffer[i++] = (char)ch;
		}
	}

	if (i)		// characters input exceed BUFFER_SIZE: i = BUFFER_SIZE
	{
		printf("Maximum characters input per line, %d, exceeded\n", BUFFER_SIZE);
		printf("Exiting ...\n");
	}
	else
		printf("Done, bye.\n");

	return 0;
}