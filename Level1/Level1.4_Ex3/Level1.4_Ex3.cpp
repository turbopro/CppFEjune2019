// Level1.4_Ex3.cpp
//
// C program that takes text input from the stdin stream (keyboard)
// 
// Output includes number of characters, number of words, and number 
//  of lines entered
//
// We use string manipulation functions from 'string.h' and 'stdio.h'
// Functions:
//  getchar() to read input
//  strtok_s() to count number of words in input text
// 
// strtok_s() uses a pointer to tokenise a string array into words
// use a switch statement
//

#include <stdio.h>
#include <string.h>

int main(void)
{
	const int ArSize = 1000;			// set array size as constant
	char input_text[ArSize] = { '\0' };	// input text string array
	char word_token[ArSize] = { '\0' };	// string array to count words
	int ch, i;							// character reader, string array indexer
	int characters, words, lines;		// counters
	characters = words = lines = i = 0;
	char* p_word = NULL;				// pointer to char to count words
	char* next_token = NULL;

	// get user input
	// user terminates input via Ctrl-Z for Windows, Ctrl-D for Unices
	printf("Please enter text (maximum 1000 characters)\n");
	printf("To quit, 'Enter' then 'Ctrl-Z/Ctrl-D' then 'Enter'\n");

	// parse stdin: exit loop if user enters Ctrl-Z/Ctrl-D or too many characters
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
	// word separators = ' ', '\n', '\t', '\v', '\f', and '\r'
	// copy input_text to word_token: strtok() changes the input string
	strcpy_s(word_token, input_text);
	// identify first word  
	p_word = strtok_s(word_token, " '\n''\t''\v''\f''\r'", &next_token);

	// loop over "word_token"; identify and increment words 
	while (p_word)	// while pointer points to a string
	{
		p_word = strtok_s(NULL, " '\n''\t''\v''\f''\r'", &next_token);
		words++;
	}

	// output statistics
	printf("\nCharacter count: %d\n", characters);
	printf("Word count: %d\n", words);
	printf("Line count: %d\n", lines);

	return 0;
}