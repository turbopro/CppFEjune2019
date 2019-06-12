// Level1.3_Ex2.cpp
//
// C program to calculate the area of a right triangle.
// Get user input for base and height values
//
// Formula: Area = 1/2 (Base * Height)
//
// All variables will use floats given that our triangles are generic
//  and academic, where the precision offered by floats should suffice
//
// We will do no input validation given that this is a basic program, and
//  input validation in C/C++ is somewhat complex.  We assume the user
//  enters valid data
//
// We will create a function, "area_right_triangle", to calculate the
//  area 

#include <stdio.h>

float area_right_triangle(float base, float height)			// declare & define
{
	return (height * base) / 2;
}

int main(void)
{
	// get user input
	float height = 0.0, base = 0.0, area = 0.0;				// all variables are float
	
	printf("Please enter the height of the triangle: ");
	scanf_s("%f", &height);
	printf("Height: %.1f\n", height);						// display to one decimal place

	printf("\nPlease enter the base of the triangle: ");
	scanf_s("%f", &base);
	printf("Base: %.1f\n", base);

	area = area_right_triangle(base, height);

	printf("\nArea of triangle with base %.1f, and height %.1f = %.1f\n", base, height, area);

	return 0;
}