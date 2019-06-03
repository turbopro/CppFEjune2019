// Level1.3_Ex5.cpp -- demonstrate the difference between the --i and i--
//
// Calculate the sum of a range of digits: eg, sum of 1, 2, 3, ... 25 = 325
// We use a while loop that terminates when an indexer/counter reaches a
//  threshold.

#include <stdio.h>

int main(void)
{
	int i = 0, n = 25, sum = 0;

	// calculate sum of digits from 1 to n
	// use while loop and post decrement operator gives the correct output 
	i = n;
	while (true)
	{
		if (i > 0)
		{
			sum += i--;		// current value of i added to sum before decrement;
							// during first iteration of while loop, i = 5,
							// is added to sum
		}			
		else
			break;
	}
	printf("Post decrement: sum of digits 1 through %d = %d\n", n, sum);

	// use while loop and pre decrement operator gives incorrect output
	i = n;
	sum = 0;
	while (true)
	{
		if (i > 0)
		{
			sum += --i;		// current value of i decremented then added to sum;
							// during first iteration of while loop, i = 5, is
							// decremented firstly to i = 4, then added to sum
		}
		else
			break;
	}
	printf("Pre decrement:  sum of digits 1 through %d != %d\n", n, sum);

	return 0;
}