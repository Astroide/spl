#include "util.h"

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
    file = fopen("main.c", "r");
    size_t capacity = sizeof(char) * 512;
    char* contents = malloc(capacity);
    size_t length = 0;
    char* characterAndNullByte = malloc(sizeof(char) * 2);
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