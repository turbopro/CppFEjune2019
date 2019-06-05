// Level1.4_Ex4.cpp 
// C program that takes creates a table of values, Fahrenheit vs Celcius temperatures
//  
// Table should have a header
// Left column shows the temperature in Fahrenheit
// The right column shows the temperature in Celsius
// Initial range for left column: 0 - 300, in steps of 20
// Right column Celsius displays with one digit precision after the decimal point
//  (use “ % 10.1f ” as format specifier).
// 
// The program is maintenance insensitive: start, end, and the step size must be adjustable
// Using a while loop
//
// Formula for Fahrenheit to Celcius: 
//  Celsius = (5 / 9) * (Fahrenheit – 32)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	const float AbsZero = -459.57f;		// set array size as constant
	const int MaxRange = 1000;
	const int minStep = 2;
	int input_check;
	float start = 0, end = 0, step = 0;
	float min_step, max_step;				// character reader, string array indexer
	//float fahrenheit_array[MaxRange];			// counters
	
	// get user input
	// minimum value for lower range is -459.67, absolute zero
	while (1)
	{
		printf("Please enter lower number of the range\n");
		printf("range: %.1f (absolute zero) to %d\n", AbsZero, MaxRange);
		input_check = scanf_s("%f", &start);
		if (input_check == EOF) 
		{
			printf("Exiting...");
			exit(0);
		}
		else if (input_check == 0)
		{
			while (fgetc(stdin) != '\n') // Read until a newline is found
				printf("Invalid entry: value must be a number\n");
			continue;
		}
		else
		{
			if (start < AbsZero || start > MaxRange)
			{
				printf("Invalid entry: value out of range\n");
				continue;
			}
			else
				break;
		}
	}
	
	// maximum value for upper range = 1000
	while (1)
	{
		printf("\nPlease enter upper number of the range\n");
		printf("range: %.1f (absolute zero) to %d\n", AbsZero, MaxRange);
		scanf_s("%f", &end);
		if (end < AbsZero || end > MaxRange)
		{
			printf("Invalid entry: value out of range\n");
			continue;
		}
		else if (end <= start)
		{
			printf("Invalid entry: upper number must be greater than lower number\n");
			continue;
		}
		else
			break;
	}
	
	// step size allows for maximum 1000 steps in lower to upper range
	max_step = (end - start) / minStep;
	min_step = (end - start) / MaxRange;
	while (1)
	{
		printf("Please enter step size\n");
		printf("range: %.1f to %.1f\n", max_step, min_step);
		scanf_s("%f", &step);
		if (step < min_step || step > max_step)
		{
			printf("Invalid entry: value out of range\n");
			continue;
		}
		else
			break;
	}
	
	printf("lower num: %.1f\nupper num: %.1f\nstep: %.1f\n", start, end, step);
	
	return 0;
}