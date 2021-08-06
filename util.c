
#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* reallocate(void* source, size_t size) {
    void* dest = realloc(source, size);
    if (dest == NULL) {
        fprintf(stderr,
                "Fatal error : trying to reallocate memory at %p to size %ld "
                "failed.",
                source, size);
        exit(1);
    }
    return dest;
}

char* readFile(char filename[]) {
    int c;
    FILE* file;
    file = fopen(filename, "r");
    size_t capacity = sizeof(char) * 512;
    char* contents = allocate(capacity);
    size_t length = 0;
    char* characterAndNullByte = allocate(sizeof(char) * 2);
    characterAndNullByte[1] = '\0';
    strcpy(contents, "");
    if (file) {
        while ((c = getc(file)) != EOF) {
            length += 1;
            if (length == capacity - 2) {
                capacity += sizeof(char) * 512;
                contents = reallocate(contents, capacity);
            }
            characterAndNullByte[0] = c;
            strcat(contents, characterAndNullByte);
        }
        fclose(file);
    }
    free(characterAndNullByte);
    return contents;
}

bool _util_charAsStringCharArrayHasBeenInitialized = false;

char* charAsString(char chr) {
    if (!_util_charAsStringCharArrayHasBeenInitialized) {
        _util_charAsStringCharArray = allocate(sizeof(char) * 2);
        _util_charAsStringCharArray[1] = '\0';
        _util_charAsStringCharArrayHasBeenInitialized = true;
    }
    _util_charAsStringCharArray[0] = chr;
    return _util_charAsStringCharArray;
}

char* startAndLengthToString(char* start, int length) {
    char* returnString = allocate(sizeof(char) * (length + 1));
    for (size_t i = 0; i < length; i++) {
        returnString[i] = start[i];
    }
    returnString[length] = '\0';
    return returnString;
}
void* __malloc__(int size, char* file, int line) {
    printf("malloc size %d in file %s on line %d\n", size, file, line);
    return malloc(size);
}