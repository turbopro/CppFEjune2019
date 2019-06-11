// Defs.h
// Level1.6_Ex2
// 
// header file with definitions for macros
// MAX2 and MAX3
// 
// For our purposes, all variables will be of type integer.
//
// since #pragma once is OS/compiler specific, we
// will use the C standard #ifndef / #define procedure
//

#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define MAX2(x, y)    (x > y ? x : y)
#define MAX3(x, y, z) (MAX2(MAX2(x, y), z))

#endif // DEFS_H_INCLUDED
