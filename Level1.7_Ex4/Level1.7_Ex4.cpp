// Level1.7_Ex4.cpp
//
// C program  that has a function DayName() which can print the day 
// of a given day-number. 
//
// For example:
//
// 1 gives: Day 1 is a Sunday
// 7 gives: Day 7 is a Saturday.
//
// The day-name(1 - 7) should be written "hard-coded” into the 
// program using an array of strings.
//

#include <stdio.h>

#define WEEK_LENGTH 7
#define MAX_STRING_LENGTH 12

// const char [] since the function does not change the array elements
void DayName(const char day_name[][MAX_STRING_LENGTH], int day_of_week);

int main(void)
{
	// array of strings for days of the week
	char day_name[WEEK_LENGTH+1][MAX_STRING_LENGTH] =
	{
		"offset day", "Sunday", "Monday", "Tuesday", 
		"Wednesday", "Thursday", "Friday", "Saturday"
	};
	int choice, i;		// user input, array indexer
	
	printf("Please enter the single digit day number from 1 through 7: ");
	scanf_s("%d", &choice);			// assuming user enters valid single integer from 1 to 7
									// no error checking
	
	DayName(day_name, choice);		// call DayName() to print the day of the week

	printf("\n\nThe full list of day numbers vs the days of the week:\n");
	for (i = 1; i <= WEEK_LENGTH; i++)
	{
		DayName(day_name, i);
	}

	return 0;
}

void DayName(const char day_name[][MAX_STRING_LENGTH], int day_of_week)
{
	printf("Day %d: %s\n", day_of_week, day_name[day_of_week]);
}