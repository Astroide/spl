#include <math.h>
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
    double* nConstants = allocate(sizeof(double) * 5);
    nConstants[0] = 0.0;
    nConstants[1] = 1.0;
    nConstants[2] = 2.0;
    nConstants[3] = 64.5;
    nConstants[4] = 65536.f;
    char** stringConstants = allocate(sizeof(char*) * 2);
    stringConstants[0] = "chien";
    stringConstants[1] = "chat";
    Bytecode testBytecode = {.length = 0,
                             .list = NULL,
                             .constants = {.numberConstants = nConstants,
                                           .numberConstantsLength = 5,
                                           .stringConstants = stringConstants,
                                           .stringConstantsLength = 2}};
    FILE* handle = fopen("out.btc", "w");
    writeBytecodeToFile(handle, testBytecode);
    fflush(handle);
    fclose(handle);
    handle = fopen("out.btc", "r");
    Bytecode bytecode = readBytecodeFromFile(handle);
    for (size_t i = 0; i < bytecode.constants.stringConstantsLength; i++) {
        printf("STRCONST %zu <%s>\n", i, bytecode.constants.stringConstants[i]);
    }
    for (size_t i = 0; i < bytecode.constants.numberConstantsLength; i++) {
        printf("NUMCONST %zu <%f>\n", i, bytecode.constants.numberConstants[i]);
    }
    fclose(handle);
    return 0;
}