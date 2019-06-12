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
	char input_buffer[BUFFER_SIZE+1];		// line buffer
	int ch;			// character reader
	int i = 0;		// indexer

	printf("Please enter some text, line by line\n");
	printf("Hit Enter at the end of the line to display the text\n");
	printf("Maximum number of characters per line: %d\n", BUFFER_SIZE);
	printf("Ctrl-A to quit\n");
	while ( (ch = getchar()) != 1 && i <= BUFFER_SIZE )		// Ctrl-Shift-A == 1
	{
		if (ch == '\n')			// if newline, terminate string array, print line
		{						
			input_buffer[i] = '\0';
			printf("%s\n", input_buffer);
			i = 0;				// reset indexer to 0 for new line input
			continue;			// loop again for user input for new line
		}
		else	// add 'ch' character to input_buffer; increment indexer (after assignment)
		{
			input_buffer[i++] = (char)ch;
		}
	}

	if (i)		// characters input exceed BUFFER_SIZE: i = BUFFER_SIZE
	{
		printf("\nInvalid input: Too many characters entered\n");
		printf("Maximum characters (%d) per line exceeded\n", BUFFER_SIZE);
		printf("Exiting...\n");
	}
	else   // user entered Ctrl-Shift-A to quit: i = 0
	{
		printf("\nCTRL + A is a correct ending.\n");
		printf("Goodbye.\n");
	}

	return 0;
}