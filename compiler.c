#include "compiler.h"

#include <stdbool.h>
#include <stdlib.h>

#include "bytecode.h"
#include "parser.h"
#include "util.h"

TokenList _compiler_tokens;
Bytecode _compiler_instructionList;
int _compiler_instructionListCapacity;
Token* _compiler_currentToken;

#define instructionListCapacity _compiler_instructionListCapacity
#define instructionList _compiler_instructionList
#define tokens _compiler_tokens
#define currentToken _compiler_currentToken

#define growInstructionListCapacityIfNeeded \
    _compiler_growInstructionListCapacityIfNeeded
void _compiler_growInstructionListCapacityIfNeeded() {
    if ((instructionListCapacity - instructionList.length) <= 2) {
        instructionListCapacity += 50;
        instructionList.list =
            reallocate(instructionList.list,
                       sizeof(Instruction) * instructionListCapacity);
    }
}

Token getToken() { return *(currentToken++); }

bool match(TokenType type) { return currentToken->type == type; }

void expression() {
    if (match(TOKEN_NUMBER))
        ;
}

Bytecode compile(TokenList tkns) {
    tokens = tkns;
    instructionListCapacity = 50;
    instructionList.length = 0;
    instructionList.list =
        allocate(sizeof(Instruction) * instructionListCapacity);

    return instructionList;
}

#undef tokens
#undef growInstructionListCapacityIfNeeded
#undef instructionList
#undef instructionListCapacity