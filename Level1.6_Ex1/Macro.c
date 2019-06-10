// Macro.c
// Level1.6_Ex1
//
// C program that contains two print macro calls. The first prints the 
// variable a, the second prints the variables a and b. Printing happens 
// by the use of the PRINT1 and PRINT2 macros that accept arguments. 
// These macros must be defined in an include-file. The variables a and b 
// gets [sic] their value in the function main().
//
// Name the program “Macro.c”and the include - file “Defs.h”.
// Don’t forget to implement the mechanism to avoid multiple inclusion 
// of the header file.
//

#include <stdio.h>
//#include <stdlib.h>
#include "Defs.h"

int main()
{
	int a = 100, b = 200;

	printf("Variables values,\n");
	printf("a:\t%d\nb:\t%d", a, b);

	printf("\n\n\nWhen we apply the macro, PRINT1, with argument 'a', we get\n\n");
	PRINT1(a);

	printf("\n\n\nWhen we apply the macro, PRINT2, with arguments 'a' and 'b', we get\n");
	printf("\n");
	PRINT2(a, b);
	printf("\n");

	return 0;
}
