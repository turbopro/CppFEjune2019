// Level1.4_Ex4.cpp
//
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
// - MaxRange = maximum value for the upper fahrenheit temperature
// - ArSize = the size of the arrays to hold the fahrenheit and celsius arrays
// - StepDivisor = divisor to create maximum number of steps allowed for a particular range
// - fTocRatio = fahrenheit to celsius conversion ratio
// - start, end = starting and ending fahrenheit temperatures
// - step = step size
// - stepper = aggregate step size used to populate the fahrenheit array
// - p_start, p_end, p_step = pointers to relevant floats above
//   pointers are used as arguments to the 'get_input' function 
// - min_step, max_step = minimum and maximum step sizes
// - fahrenheit_array = array to store fahrenheit temperatures
// - celsius_array = array to store celsius temperatures
// - array_size, i = array indexers
//
// - get_input() = function to get user input for start, end, and step values
//                 the function does some error checking, but needs to do much more
// - check_input = function to check/validate user input
// - fill_array() = function to fill the fahrenheit and celsius arrays

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void get_input(float* p_input, const char* input_name, 
//	float min_step = 0, float max_step = 0);		// function declaration to get user input

// function declaration to get user input
void get_input(float* p_start, float* p_end, float* p_step);

// function declaration to check user input
void check_input(float* user_input, float min_step = 0.0, float max_step = 0.0);

// function definition to fill arrays
int fill_array(float* fahrenheit_array, float* celsius_array, 
	float* p_start, float *end, float *p_step);

const int ArSize = 1000;
const float MaxRange = 1000;
const float fT0cRatio = 5.0f / 9.0f;
const float AbsZero = -459.57f;

int main(void)
{
	float start = 0, end = 0, step = 0;
	float* p_start = &start, * p_end = &end, * p_step = &step;	
	float fahrenheit_array[ArSize];
	float celsius_array[ArSize];
	int array_idx = 0, i = 0;

	// to run the program with different values, change the below:
	start = 0;			// set the start value
	end = 300;			// set the end value
	step = 20;			// set the step size
	
	// get user input for start, end and step values
	// to run the program to accept user input, uncomment the line below
	// get_input(p_start, p_end, p_step);
	
	// create arrays of fahrenheit and celsius temperatures
	// fill arrays and store how many array cells were filled 
	array_idx = fill_array(fahrenheit_array, celsius_array, p_start, p_end, p_step);

	// display Fahrenheit to Celsius table
	printf("---------------------------------------------\n");
	printf("\tFahrenheit\t|\t   Celsius\t\n");					// header
	printf("---------------------------------------------\n");
	for (i = 0; i < array_idx; i++)
	{
		printf("\t%10.1f\t|\t%10.1f\n", fahrenheit_array[i], celsius_array[i]);
	}
	printf("---------------------------------------------\n");

	return 0;
}

// get_input() definition
//void get_input(float* p_input, const char* input_name, float min_step, float max_step)
void get_input(float* p_start, float* p_end, float* p_step)
{
	const int StepDivisor = 2;
	float min_step, max_step;

	// get start temperature: minimum value is -459.67, absolute zero
	printf("Please enter start temperature\n");
	printf("range between: %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
	printf("Ctrl-Z to quit\n");
	check_input(p_start);

	// get end temperature: maximum value is 1000
	printf("\nPlease enter end temperature\n");
	printf("range between: %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
	printf("Ctrl-Z to quit\n");
	do
	{
		check_input(p_end);
		if (*p_end > *p_start)
			break;
		else
		{
			printf("\nInvalid entry: end value must be greater than start value\n");
			printf("range between: %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
		}
	} while (1);

	// get step size
	// step size allows for maximum 1000 steps in lower to upper range
	max_step = (*p_end - *p_start) / StepDivisor;
	min_step = (*p_end - *p_start) / MaxRange;
	printf("\nPlease enter step size\n");
	printf("range between: %.1f to %.1f\n", min_step, max_step);
	printf("Ctrl-Z to quit\n");
	do
	{
		//printf("\n");
		check_input(p_step);
		if (*p_step > min_step && *p_step < max_step)
			break;
		else
		{
			printf("\nInvalid entry: step size out of range\n");
			printf("range between: %.1f to %.1f\n", min_step, max_step);
		}
	} while (1);
}

// check user input
void check_input(float* user_input, float min_step, float max_step)
{
	const int BufferSize = 10;
	char* p_end = NULL;
	char input_buffer[BufferSize];

	do
	{
		if (fgets(input_buffer, BufferSize, stdin))
		{
			*user_input = strtof(input_buffer, &p_end);

			if (*p_end != '\n' || input_buffer[0] == '\n' || p_end == input_buffer)
			{
				printf("\nERROR: not a valid number\n");
				printf("Enter a valid number between %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
				continue;
			}
			else if (*user_input < AbsZero || *user_input > MaxRange)
			{
				printf("\nInvalid entry: value out of range\n");
				printf("Enter a valid number between %.1f (absolute zero) to %.1f\n", AbsZero, MaxRange);
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
	float* p_start, float* p_end, float* p_step)
{
	int i = 0;
	float stepper = *p_start;
	
	// while stepper value is less than end value fill both arrays  
	while (stepper <= *p_end)
	{
		fahrenheit_array[i] = stepper;
		celsius_array[i] = (fahrenheit_array[i] - 32) * fT0cRatio;
		stepper += *p_step;
		i++;
		
		// failsafe sequence in case of rounding errors
		if (i >= ArSize)
		{
			printf("Indexing Error: program exiting...");
			exit(1);
		}
	}

	// add upper temperature to fahrenheit_array if not included already
	// ensure we do not write past the end of the array
	if (fahrenheit_array[i-1] != *p_end && i < (ArSize - 1))
	{
		fahrenheit_array[i] = *p_end;
		celsius_array[i] = (fahrenheit_array[i] - 32) * fT0cRatio;
		i++;		// increment index to reflect added end value
	}

	return i;
}
