#ifndef _SPL_UTIL_H_
#define _SPL_UTIL_H_

#include <stdbool.h>
#include <stdio.h>

void* reallocate(void* ptr, size_t size);

char* readFile(char filename[]);

char* charAsString(char chr);

char* _util_charAsStringCharArray;

char* startAndLengthToString(char* start, int length);

#endif