// Defs.h
// Level1.6_Ex1
// 
// header file with definitions for macros
// PRINT1 and PRINT2
//
// for our purposes, we will define the macros to print
// integers 
//
// since #pragma once is OS/compiler specific, we
// will use the C standard #ifndef / #define procedure
//

#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define PRINT1(a)    (printf("%d", a))
#define PRINT2(a, b) (printf("%d and %d", a, b))

#endif // DEFS_H_INCLUDED
