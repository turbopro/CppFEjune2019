// right_tri_area.cpp -- source file to compute area of a right triangle
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
	printf("Height: %.2f\n", height);						// display two decimal places
	printf("\nPlease enter the base of the triangle: ");
	scanf_s("%f", &base);
	printf("Base: %.2f\n", base);

	area = area_right_triangle(base, height);

	printf("\nArea of triangle: %.2f\n", area);

	return 0;
}