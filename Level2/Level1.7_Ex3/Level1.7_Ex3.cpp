// Level1.7_Ex3

/* Predict what will be printed on the screen */

#include <stdio.h>

#define PRD(a) printf("%d", (a) ) // Print decimal
#define NL printf("\n"); // Print new line

// Create and initialize array
int a[] = { 0, 1, 2, 3, 4 };

int main()
{
	int i;
	int* p;

	// print each member of array 'a' by the array subscripting operator [] with integer indexer
	for (i = 0; i <= 4; i++) PRD(a[i]); // 1:	01234				
	NL;

	// print each member by dereferencing a pointer indexer
	for (p = &a[0]; p <= &a[4]; p++) PRD(*p); // 2:		01234		
	NL;
	NL;

	// 	print each member by pointer and indexer with the subscripting operator
	for (p = &a[0], i = 0; i <= 4; i++) PRD(p[i]); // 3:	01234
	NL;

	// print each member by dereferencing a pointer index
	// pointer and indexer increment each loop, so we skip every other (odd numbered) array element
	for (p = a, i = 0; p + i <= a + 4; p++, i++) PRD(*(p + i)); // 4:	024		
	NL;															
	NL;															

	// print in the reverse direction by dereferencing a pointer, while using the pointer as an indexer
	for (p = a + 4; p >= a; p--) PRD(*p); // 5:		43210		
	NL;

	// print each member in reverse by pointer and subscripting operator with integer indexer
	for (p = a + 4, i = 0; i <= 4; i++) PRD(p[-i]); // 6:		43210		
	NL;

	// print each member in reverse by pointer indexer, pointer arithmetic and subscripting operator
	for (p = a + 4; p >= a; p--) PRD(a[p - a]); // 7:		43210
	NL;
	
	return 0;
}