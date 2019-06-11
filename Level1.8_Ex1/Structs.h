// Structs.h
// Level1.8_Ex1
// 
// header file with Struct Article, and Print() function definition
//
// since #pragma once is OS/compiler specific, we
// will use the C standard #ifndef / #define procedure
//

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define DESCRIPTION_SIZE 20		// max string length of Article's description

// Article declaration/definition
struct Article
{
	int article_number;
	int quantity;
	char description[DESCRIPTION_SIZE + 1];
};

// const Article* for Print, to prevent Print from changing Article pointed to by 'art1'
void Print(const Article* art1);

#endif // STRUCTS_H_INCLUDED
