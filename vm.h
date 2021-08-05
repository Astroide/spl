#ifndef _SPL_VM_H_
#define _SPL_VM_H_

typedef enum { OP_EXIT } Instruction;

typedef struct {
    Instruction* list;
    int length;
} InstructionList;

#endif
