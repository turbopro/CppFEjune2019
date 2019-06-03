// Level1.4_Ex1.cpp -- Program that takes text input from the keybord
// 
// Output includes number of characters, number of words, and the
//  number of lines entered
//
// We use getchar() to read input

#include <stdio.h>

int main(void)
{
	// variables to store details
	char input_text[1000];
	int ch;
	int characters, words, lines, i;
	characters = words = lines = i = 0;

	// Get user input
	printf("Please enter text (maximum 1000 characters)\n");

	while ((ch = getchar()) != EOF && i < 1000)
	{
		characters++;
		input_text[i++] = ch;
		printf("ch: %d\n", ch);
	}

	printf("input_text: %s\n", input_text);
	printf("character count: %d\n", characters);

	return 0;
}