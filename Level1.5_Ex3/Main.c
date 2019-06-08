// Main.c
// Level1.5_Ex2
//
// C program that consists of two source-files: Main.c and Print.c
// - Main.c contains the main() function and gives the variable i a value. 
// - Print.c multiplies i by 2 and prints it.
// - Print.c contains the function print() which can be called from main().
//
// Variables:
// - i = integer store for number
// 
// Functions:
// main = main function
// print = function to double an integer and print it
//             

#include <stdio.h>

void print(int number);

int main(void)
{
	int i = 24;

	print(i);

	return 0;
}