#include <stdio.h>
#include <stdlib.h>

#include "util.h"
int main() {
    printf("SPL - Some Programming Language");
    char* fileContents = readFile("main.c");
    printf("%s", fileContents);
    free(fileContents);
    return 0;
}