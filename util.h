#ifndef _SPL_UTIL_H_
#define _SPL_UTIL_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #define DEBUG_MALLOC
#ifdef DEBUG_MALLOC
#define allocate(size) __malloc__(size, __FILE__, __LINE__)
#else
#define allocate(size) malloc(size)
#endif
void* __malloc__(int size, char* file, int line);
void* reallocate(void* ptr, size_t size);

char* readFile(char filename[]);

char* charAsString(char chr);

char* _util_charAsStringCharArray;

char* startAndLengthToString(char* start, int length);

#endif