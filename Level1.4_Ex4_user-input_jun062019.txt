// Level1.4_Ex4.cpp 
// C program that creates a table of values, Fahrenheit vs Celsius temperatures
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
// Formula for Fahrenheit to Celsius: 
//  Celsius = (5 / 9) * (Fahrenheit – 32)
//
// Variables:
// - MaxRange = maximum size for the arrays to hold the fahrenheit and celsius arrays
// - minStep = divisor to create maximum number of steps allowed for a particular range
// - fTocRatio = fahrenheit to celsius conversion ratio
// - start, end = starting and ending fahrenheit temperatures
// - step = step size
// - stepper = aggregate step size used to populate the fahrenheit array
// - p_start, p_end, p_step = pointers to relevant floats above
//   pointers are used as arguments to the 'get_input' function 
// - min_step, max_step = minimum and maximum step sizes
// - fahrenheit_array = array to store fahrenheit temperatures
// - celsius_array = array to store celsius temperatures
// - i, j = array indexers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_input(float* p_input, const char* input_name, 
	float min_step = 0, float max_step = 0);		// function declaration to get user input

int fill_array(float* fahrenheit_array, float* celsius_array, 
	float* p_stepper, float *end, float *p_step);	// function definition to fill arrays

const int ArSize = 1000;
const float MaxRange = 1000;
const float fT0cRatio = 5.0f / 9.0f;

int main(void)
{
	const int minStep = 2;
	float start = 0, end = 0, step = 0, stepper = 0;
	float *p_start = &start, *p_end = &end, *p_step = &step, *p_stepper = &stepper;
	const char *input[3] = { "start", "end", "step" };
	float min_step, max_step;
	float fahrenheit_array[ArSize];
	float celsius_array[ArSize];
	int array_idx = 0, i = 0;

	// get user input
	// get start temperature: minimum value is -459.67, absolute zero
	get_input(p_start, input[0]);

	// get end temperature: maximum value is 1000 
	do
	{
		printf("\n");
		get_input(p_end, input[1]);
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
		printf("\n");
		get_input(p_step, input[2], min_step, max_step);
		if (step > min_step && step < max_step)
			break;
		else
			printf("Invalid entry: step size out of range\n\n");
	} while (1);

	// create arrays of fahrenheit and celsius temperatures
	stepper = start;		// initialise stepper
	// fill arrays and store how many array cells were filled 
	array_idx = fill_array(fahrenheit_array, celsius_array, p_stepper, p_end, p_step);
	
	// add upper temperature to fahrenheit_array if not included already
	// ensure we do not write past the end of the array
	if (fahrenheit_array[array_idx - 1] != end && array_idx < (ArSize - 1))
	{
		fahrenheit_array[array_idx] = end;
		celsius_array[array_idx] = (fahrenheit_array[array_idx] - 32) * fT0cRatio;
		array_idx++;		// increment index to reflect added end value
	}
	
	// display Fahrenheit to Celsius table
	printf("---------------------------------------------\n");
	printf("\tFahrenheit\t|\t   Celsius\t\n");
	printf("---------------------------------------------\n");
	for (i = 0; i < array_idx; i++)
	{
		printf("\t%10.1f\t|\t%10.1f\n", fahrenheit_array[i], celsius_array[i]);
	}
	printf("---------------------------------------------\n");

	return 0;
}

// get_input() definition
void get_input(float* p_input, const char* input_name, float min_step, float max_step)
{
	const float AbsZero = -459.57f;
	const int BufferSize = 10;
	char* p_end = NULL;
	char input_buffer[BufferSize];

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

		if (fgets(input_buffer, BufferSize, stdin))
		{
			*p_input = strtof(input_buffer, &p_end);

			if (*p_end != '\n' || input_buffer[0] == '\n' || p_end == input_buffer)
			{
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

// fill_array() definition
int fill_array(float* fahrenheit_array, float* celsius_array, 
	float* p_stepper, float *p_end,	float *p_step)
{
	int i = 0;
	
	// while stepper value is less than end value fill both arrays  
	while (*p_stepper <= *p_end)
	{
		fahrenheit_array[i] = *p_stepper;
		celsius_array[i] = (fahrenheit_array[i] - 32) * fT0cRatio;
		*p_stepper += *p_step;
		i++;
		if (i >= ArSize) 		// fail safe exit sequence
		{						//  in case of rounding errors
			printf("Indexing Error: program exiting...");
			exit(1);
		}
	}

	return i;
}
