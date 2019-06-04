// Level1.4_Ex1.cpp -- Program that takes text input from the keybord
// 
// Output includes number of characters, number of words, and the
//  number of lines entered
//
// We use string manipulation functions from 'string.h' and 'stdio.h'
// Functions:
//  getchar() to read input
//  strtok() to count number of words in input text
//  
// For Visual Studio, we need to disable secure CRT checking
//  #pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)

int main(void)
{
	// variables to store details
	const int ArSize = 1000;
	char input_text[ArSize] = {'\0'};
	char processing_text[ArSize] = {'\0'};
	int ch;
	int characters, words, lines, i;
	characters = words = lines = i = 0;

	// Get user input
	printf("Please enter text (maximum 1000 characters)\nTo quit, Enter then Ctrl-Z then Enter\n");

	while ((ch = getchar()) != EOF && i < ArSize)
	{
		characters++;
		input_text[i++] = ch;
		//printf("ch: %d\n", ch);
	}
	
	// thanks to youtuber, CodeVault --> https://www.youtube.com/watch?v=34DnZ2ewyZo
	// use strtok() to count number of words in "input_text"
	// word separator = ' '
	// copy input_text to output_text
	strcpy_s(processing_text, input_text);
	// get first word  
	char *word = strtok(processing_text, " '\n''\t'");

	// loop over "input_text"; identify and increment word 
	while (word != NULL)
	{
		word = strtok(NULL, " ");
		words++;
	}

	/*
	while ( fgets(buffer, BufSize, stdin) )
	{
		printf("buffer: %s", buffer);
		strcat_s(input_text, buffer);
		//printf("input text: %s", input_text);

		if (strncmp(buffer, "quit", 4) == 0)
		{
			//printf("Leaving while loop ...");
			break;
		}
		//characters++;
		//input_text[i++] = ch;
		//printf("ch: %d\n", ch);
	}
	*/
	//if (i < 999)
	//	input_text[i + 1] = '\0';
	//characters = strlen(input_text);
	printf("input_text: %s\n", input_text);
	printf("character count: %d\n", characters);
	printf("Number of words: %d\n", words);

	return 0;
}