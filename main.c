#include <stdio.h>
#include <stdlib.h>

#include "bytecode.h"
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
    double* nConstants = allocate(sizeof(double) * 4);
    nConstants[0] = 0.0;
    nConstants[1] = 1.0;
    nConstants[2] = 2.0;
    nConstants[3] = 64.0;
    char** stringConstants = allocate(sizeof(char**) * 2);
    stringConstants[0] = "chien";
    stringConstants[1] = "chat";
    Bytecode testBytecode = {.length = 0,
                             .list = NULL,
                             .constants = {.numberConstants = nConstants,
                                           .numberConstantsLength = 4,
                                           .stringConstants = stringConstants,
                                           .stringConstantsLength = 2}};
    // FILE* handle = fopen("out.btc", "w");
    // writeBytecodeToFile(handle, testBytecode);
    // fflush(handle);
    // fclose(handle);
    return 0;
}