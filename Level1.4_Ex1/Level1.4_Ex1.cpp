// Level1.4_Ex1.cpp 
// C program that takes text input from the stdin stream (keyboard)
// 
// Output includes number of characters, number of words, and number 
//  of lines entered
//
// We use string manipulation functions from 'string.h' and 'stdio.h'
// Functions:
//  getchar() to read input
//  strtok() to count number of words in input text
//  
// For Visual Studio, given that we're testing and this code is not
//  for use in a production environment, we need to disable 
//  secure CRT warning/error for the strtok() function
//  #pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)			// for non-production environment only

int main(void)
{
	const int ArSize = 1000;			// set array size as constant
	char input_text[ArSize] = {'\0'};	// initialise as empty string
	char word_token[ArSize] = {'\0'};	// initialise as empty string
	int ch, i;							// input iterator, string array indexer
	int characters, words, lines;		// counters
	characters = words = lines = i = 0;
	char *p_word = NULL;				// pointer to char to count words

	// get user input
	printf("Please enter text (maximum 1000 characters)\n");
	printf("To quit, 'Enter' then 'Ctrl-Z' then 'Enter'\n");

	// parse stdin: exit loop if user enters Ctrl-Z or too many characters
	// count characters, lines
	// store input text in string array
	while ((ch = getchar()) != EOF && i < ArSize)
	{
		characters++;
		if (ch == '\n') { lines++; }
		input_text[i++] = ch;
	}
	
	// thanks to youtuber, CodeVault --> https://www.youtube.com/watch?v=34DnZ2ewyZo
	// use strtok() to count number of words in "input_text"
	// word separators = ' ', '\n', and '\t'
	// copy input_text to output_text
	strcpy_s(word_token, input_text);
	// identify first word  
	p_word = strtok(word_token, " '\n''\t'");

	// loop over "input_text"; identify and increment words 
	while (p_word != NULL)
	{
		p_word = strtok(NULL, " '\n''\t'");
		words++;
	}

	printf("Character count: %d\n", characters);
	printf("Word count: %d\n", words);
	printf("Line count: %d\n", lines);

	return 0;
}