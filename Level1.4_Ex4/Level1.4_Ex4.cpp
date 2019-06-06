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
//
// Variables:
// - MaxRange = maximum size for the arrays to hold the fahrenheit and celsius arrays
// - minStep = divisor to create maximum number of steps allowed for a particular range
// - fTocRatio = fahrenheit to celsius converter factor
// - start, end = starting and ending fahrenheit temperatures
// - step = step size
// - stepper = aggregate step size used to populate the fahrenheit array
// - p_start, p_end = pointers to relevant floats above
// - p_step, p_end = pointers to relevant floats above
//   pointers used as arguments to set_input function 
// - min_step, max_step = minimum and maximum step sizes
// - fahrenheit_array = array to store fahrenheit temperatures
// - celsius_array = array to store celsius temperatures
// - i, j = array indexers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_input(float* p_input, const char* input_name, 
	float min_step = 0, float max_step = 0);		// function declaration to get user input

int main(void)
{
	const int MaxRange = 1000;					// max size for arrays to hold temps
	const int minStep = 2;						// divisor to generate maximum steps
	const float fT0cRatio = 5.0f / 9.0f;		// fahrenheit to celsius conversion factor
	float start = 0, end = 0, step = 0, stepper = 0;	// floats for temps and steps	
	float *p_start = &start, *p_end = &end, *p_step = &step;	// pointers to floats
	const char *input[3] = { "start", "end", "step" };	// pointer to char arrays 
	float min_step, max_step;
	float fahrenheit_array[MaxRange];			// counters
	float celsius_array[MaxRange];
	int i = 0, j = 0;

	// get user input
	// get start temperature: minimum value is -459.67, absolute zero
	set_input(p_start, input[0]);

	// get end temperature: maximum value is 1000 
	do
	{
		set_input(p_end, input[1]);
		if (end > start)
			break;
		else
			printf("Invalid entry: end number must be greater than start number\n\n");
	} while (1);

	// get step size
	// step size allows for maximum 1000 steps in lower to upper range
	max_step = (end - start) / minStep;
	min_step = (end - start) / MaxRange;
	do
	{
		set_input(p_step, input[2], min_step, max_step);
		if (step > min_step && step < max_step)
			break;
		else
			printf("Invalid entry: step size out of range\n\n");
	} while (1);

	// create arrays of fahrenheit temps
	stepper = start;
	//while ((stepper = start + (i * step)) <= end)
	while (stepper <= end)
	{
		fahrenheit_array[i] = stepper;
		celsius_array[i] = (fahrenheit_array[i] - 32) * fT0cRatio;
		stepper += step;
		i++;
		if (i >= MaxRange) { break; }
	} 
	
	// add upper temperature to fahrenheit_array if not included already
	if (fahrenheit_array[i - 1] != end && i < (MaxRange - 1))
	{
		fahrenheit_array[i] = end;
		celsius_array[i] = (fahrenheit_array[i] - 32) * fT0cRatio;
		i++;
	}
	
	printf("---------------------------------------------\n");
	printf("\tFahrenheit\t|\t   Celsius\t\n");
	printf("---------------------------------------------\n");
	for (j = 0; j < i; j++)
	{
		printf("\t%10.1f\t|\t%10.1f\n", fahrenheit_array[j], celsius_array[j]);
	}
	printf("---------------------------------------------\n");

	return 0;
}

void set_input(float* p_input, const char* input_name, float min_step, float max_step)
{
	const float AbsZero = -459.57f;
	const float MaxRange = 1000.0f;
	const int ArSize = 10;
	char* p_end = NULL;
	char input_buffer[ArSize];

	do
	{
		if (input_name == "step")
		{
			printf("Please enter step size\n");
			printf("range: %.1f to %.1f\n", min_step, max_step);
			printf("Ctrl-Z to quit\n");
		}
		else
		{
			printf("Please enter %s temperature\n", input_name);
			printf("range of values: %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
			printf("Ctrl-Z to quit\n");
		}

		if (fgets(input_buffer, ArSize, stdin))
		{
			*p_input = strtof(input_buffer, &p_end);

			if (*p_end != '\n' || input_buffer[0] == '\n' || p_end == input_buffer)
			{
				//printf("ERROR: \"%s\" is an invalid float!\n", input_buffer);
				printf("ERROR: not a valid float\n\n");
				continue;
			}
			else if (*p_input < AbsZero || *p_input > MaxRange)
			{
				printf("Invalid entry: value out of range\n\n");
				continue;
			}
			else
				break;
		}
		else
		{
			printf("Exiting...\n");
			exit(0);
		}

	} while (1);
}
