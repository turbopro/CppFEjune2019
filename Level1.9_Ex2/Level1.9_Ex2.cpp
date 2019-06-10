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
	char output_filename[FileNameSize + 1] = { '\0' }; // set filename to empty text
	errno_t err_file_open;

	while ( 1 )	// loop until we get valid filename from user
	{
		printf("Please enter a name for the output file\n");
		printf("Maximum characters: %d\n", FileNameSize);
		printf("Ctrl-Shift-A to quit\n");
		while ((ch = getchar()) != 1 && i <= FileNameSize)		// Ctrl-Shift-A == 1
		{
			if (ch == '\n')			// if newline, process input text
			{
				output_filename[i] = '\0';		// terminate filename
				i = 0;							// reset i to 0 for next line input

				if (strlen(output_filename) == 0)	// if user did not enter a name
				{
					printf("Invalid entry: you must enter a valid filename.\n");
					printf("Maximum characters: %d\n", FileNameSize);
					printf("Ctrl-Shift-A to quit\n");
					continue;
				}
				else { break; }
			}
			else { output_filename[i++] = (char)ch; }
		}

		if (i > FileNameSize)	// if too many characters entered
		{
			printf("\nInvalid entry: Filename too long\n");
			printf("Maximum characters: %d\n\n", FileNameSize);
			// reset the input buffer to accept new line input
			while ((ch = getchar()) != '\n' && ch != EOF) { }	// clear input buffer
			output_filename[0] = '\0';			// reset output_filename
			i = 0;		// reset indexer for new input
			continue;
		}
		else if (strlen(output_filename) == 0)	// if user hit Ctrl-Shift-A to quit
		{
			printf("\nGoodbye...\n");
			exit(0);
		}
		else { break; }
	}
	
	// open output file for writing; check if file opened successfully
	err_file_open = fopen_s(&p_outfile, output_filename, mode);
	if (err_file_open)
	{
		printf("\nCannot open output file, %s!\n", output_filename);
		printf("Exiting...\n");
		exit(1);
	}
	else
	{
		printf("\nOutput file '%s' opened successfully in current folder\n", output_filename);
	}

	// if file handle is open and ready for writing
	if (p_outfile)			
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
		
		if ( i )		// characters input exceed BufferSize
		{
			printf("\nInvalid entry: Too many characters entered.\n");
			printf("Maximum characters per line, %d, exceeded\n", BufferSize);
			printf("Exiting...\n");
		}
		else { printf("\nGoodbye.\n"); }		// user entered Ctrl-Shift-A

		fclose(p_outfile);			// close file
	}

	return 0;
}