#ifndef _SPL_BYTECODE_H_
#define _SPL_BYTECODE_H_

#include <stdio.h>
typedef struct {
    char** stringConstants;
    double* numberConstants;
    int stringConstantsLength;
    int numberConstantsLength;
} ConstantTable;

typedef enum { OP_NUMBER_CONSTANT, OP_STRING_CONSTANT } Instruction;

typedef struct {
    Instruction* list;
    int length;
    ConstantTable constants;
} Bytecode;

void writeBytecodeToFile(FILE* file, Bytecode bytecode);

Bytecode readBytecodeFromFile(FILE* file);

#endif