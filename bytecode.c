#include "bytecode.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void writeBytecodeToFile(FILE* file, Bytecode bytecode) {
    fprintf(file, "SPLBTC%c",
            (char)bytecode.constants.stringConstantsLength & 0xFF);
    for (size_t i = 0; i < bytecode.constants.stringConstantsLength; i++) {
        fprintf(file, "%c%s",
                (int)strlen(bytecode.constants.stringConstants[i]),
                bytecode.constants.stringConstants[i]);
    }
    for (size_t i = 0; i < bytecode.constants.numberConstantsLength; i++) {
        int number = (int)bytecode.constants.numberConstants[i];
        char* numberAsString =
            allocate((int)((ceil(log10(number)) + 1) * sizeof(char)));
        memset(numberAsString, 0,
               (int)((ceil(log10(number)) + 1) * sizeof(char)));
        sprintf(numberAsString, "%d", number);
        fprintf(file, "%c%s", (int)strlen(numberAsString), numberAsString);
        free(numberAsString);
    }
}