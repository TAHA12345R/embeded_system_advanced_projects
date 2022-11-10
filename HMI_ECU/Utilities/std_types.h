/****************************************************
* [File Name]: std_types.h
* [Description]: Types for AVR
* [Author]: taha Khaled
****************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Creating a data type boolean */
typedef unsigned char boolean;

/* Boolean Values */
#ifndef FALSE
#define FALSE (0u)
#endif
#ifndef TRUE
#define TRUE (1u)
#endif

/* Logic values (High-Low) */
#define LOGIC_High (1u)
#define LOGIC_Low (0u)

/* Define a Null Pointer */
#define NULL ((void*)0)

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#endif /* STD_TYPES_H */
