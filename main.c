#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "util.h"
int main() {
    printf("SPL - Some Programming Language\n");
    char* fileContents = readFile("test.spl");
    // printf("%s\n", fileContents);
    TokenList tkns = parse(fileContents);
    for (size_t i = 0; i < tkns.length; i++) {
        char* literalAsString = startAndLengthToString(
            tkns.list[i].stringRepresentation, tkns.list[i].length);
        printf("Token %s %s\n", tokenTypeToString(tkns.list[i].type),
               literalAsString);
        free(literalAsString);
    }

    free(fileContents);
    return 0;
}