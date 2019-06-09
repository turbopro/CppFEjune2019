// Structs.c
// Level1.8_Ex1
//
// C source file with function Print(). This function prints 
// an Article structure.  The function take a pointer to an 
// Article as its single argument, and prints the fields of
// the Article struct. 
//
// Use pointers as arguments for the Print() function.
//

#include <stdio.h>
#include "Structs.h"

void Print(const Article* art1)
{
	printf("Article Number: %d\n", art1->article_number);
	printf("Article Quantity: %d\n", art1->quantity);
	printf("Article Description: %s\n", art1->description);
}
