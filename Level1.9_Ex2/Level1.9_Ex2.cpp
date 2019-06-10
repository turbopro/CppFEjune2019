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
// For this exercise, input text is output to a file. The file to 
// write to must be specified by the user.
//
// Variables:
//
// input_buffer		-	string to hold line of text input by the user
// output_filename	-	string to hold name of the output file
// ch				-	store for input character
// i				-	array indexer/counter
// p_outfile		-	output file pointer
// mode				-	pointer to string to hold mode for output file access
// err_file_open	-	file open error flag
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BufferSize 100
#define FileNameSize 80

int main(void)
{
	char input_buffer[BufferSize+1];	// allow for terminating '\0'
	int ch;
	int i = 0;
	FILE* p_outfile;
	const char* mode = "w+";
	char output_filename[FileNameSize + 1] = { '\0' };
	errno_t err_file_open;

	// get filename from user
	printf("Please enter the name of the output file\n");
	printf("Maximum characters for the filename: %d\n", FileNameSize);
	printf("Ctrl-Shift-A to quit\n");
	
	while ((ch = getchar()) != 1 && i <= FileNameSize)		// Ctrl-Shift-A == 1
	{
		if (ch == '\n')			// if newline, terminate string array, print/save line
		{
			if (strlen(output_filename) == 0)
			{
				printf("\nInvalid entry\n");
				printf("You must enter a filename.\n");
				printf("Maximum characters for the filename % d\n", FileNameSize);
				continue;
			}
			else
			{
				output_filename[i] = '\0';
				printf("Thanks, %s will be used to store input text\n", output_filename);
				i = 0;				// reset i to 0 
			}
		}
		else
		{
			input_buffer[i++] = (char)ch;
		}
	}
	if (i)		// characters input exceed BufferSize
	{
		printf("\nMaximum characters input per line, %d, exceeded\n", BufferSize);
		printf("Exiting...\n");
	}
	//else
		printf("\nDone, bye.\n");

	/*
	while( 1 )
	{
		if (fgets(output_filename, FileNameSize, stdin))
		{
			if (strlen(output_filename) == 0)
			{
				printf("\nInvalid entry\n");
				printf("You must enter a filename.\n");
				printf("Maximum characters for the filename % d\n", FileNameSize);
				continue;
			}
			else
			{
				printf("\nThank you.\n");
				printf("Output file '%s' stored in current folder\n", output_filename);
				break;
			}
		}
		else
		{
			printf("\nInvalid entry: maximum number of characters exceeded\n");
			printf("Exiting...\n");
			exit(1);
		}
	}

	
	while ( !fgets(output_filename, FileNameSize, stdin) )
	{
		if (strlen(output_filename) == 0)
		{
			printf("You must enter a name for the output file\n");
			printf("Maximum number of characters: %d\n", FileNameSize);
		}
	}
	*/
	// check if file opened successfully
	err_file_open = fopen_s(&p_outfile, output_filename, mode);
	if (err_file_open)
	{
		printf("Cannot open output file, %s!\n", output_filename);
		printf("Exiting...\n");
		if (p_outfile) { fclose(p_outfile); }	// if file open, close it
		exit(1);
	}
	else
	{
		printf("Output file '%s' opened successfully in current folder\n", output_filename);
	}

	if (p_outfile)			// confirm file is open and ready for writing
	{
		// get user input
		printf("\nPlease enter some text, line by line\n");
		printf("Hit Enter at the end of the line to display and save text\n");
		printf("Maximum number of characters per line: %d\n", BufferSize);
		printf("Ctrl-Shift-A to quit\n");
		while ((ch = getchar()) != 1 && i <= BufferSize)		// Ctrl-Shift-A == 1
		{
			if (ch == '\n')			// if newline, terminate string array, print/save line
			{
				input_buffer[i] = '\0';
				printf("%s\n", input_buffer);
				fprintf_s(p_outfile, "%s\n", input_buffer);
				i = 0;				// reset i to 0 for next line of input
			}
			else
			{
				input_buffer[i++] = (char)ch;
			}
		}

		if (i)		// characters input exceed BufferSize
		{
			printf("\nMaximum characters input per line, %d, exceeded\n", BufferSize);
			printf("Exiting...\n");
		}
		else
			printf("\nDone, bye.\n");

		fclose(p_outfile);			// close file
	}

	return 0;
}