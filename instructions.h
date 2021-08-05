#ifndef _SPL_INSTRUCTIONS_H_
#define _SPL_INSTRUCTIONS_H_

typedef enum { OP_NUMBER_CONSTANT, OP_STRING_CONSTANT } Instruction;

typedef struct {
    Instruction* list;
    int length;
} InstructionList;

#endif