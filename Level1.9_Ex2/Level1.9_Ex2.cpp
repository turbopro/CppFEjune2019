// Level1.9_Ex2
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
// For this exercise, output input text to a file. The file to write
// to must be specified by the user.
//

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main(void)
{
	char input_buffer[BUFFER_SIZE];
	int ch;
	int i = 0;
	FILE* p_outfile;
	const char* mode = "w+";
	char output_filename[] = "line_by_line.txt";
	errno_t err0;

	err0 = fopen_s(&p_outfile, output_filename, mode);
	if (err0)
	{
		printf("Cannot open output file, %s!\n", output_filename);
		exit(1);
	}
	else
	{
		printf("Output file, %s, opened successfully\n", output_filename);
	}

	printf("Please enter some text, line by line\n");
	printf("Hit Enter at the end of the line to display the text\n");
	printf("Maximum number of characters per line: %d\n", BUFFER_SIZE);
	printf("Ctrl-A to quit\n");
	while ((ch = getchar()) != 1 && i < BUFFER_SIZE)		// Ctrl-Shift-A == 1
	{
		if (ch == '\n')			// if newline, terminate string array, print line
		{
			input_buffer[i] = '\0';
			printf("%s\n", input_buffer);
			fprintf_s(p_outfile, "%s\n", input_buffer);
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


	fclose(p_outfile);

	return 0;
}