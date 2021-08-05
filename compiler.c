#include "compiler.h"

#include <stdbool.h>
#include <stdlib.h>

#include "parser.h"
#include "util.h"
#include "vm.h"

TokenList _compiler_tokens;
InstructionList _compiler_instructionList;
int _compiler_instructionListCapacity;
Token* _compiler_currentToken;

#define instructionListCapacity _compiler_instructionListCapacity
#define instructionList _compiler_instructionList
#define tokens _compiler_tokens
#define currentToken _compiler_currentToken

#define growInstructionListCapacity _compiler_growInstructionListCapacity
void _compiler_growInstructionListCapacity() {
    instructionListCapacity += 50;
    instructionList.list = reallocate(
        instructionList.list, sizeof(Instruction) * instructionListCapacity);
}

Token getToken() { return *(currentToken++); }

bool match(TokenType type) { return currentToken->type == type; }

InstructionList compile(TokenList tkns) {
    tokens = tkns;
    instructionListCapacity = 50;
    instructionList.length = 0;
    instructionList.list =
        malloc(sizeof(Instruction) * instructionListCapacity);

    return instructionList;
}

#undef tokens
#undef growInstructionListCapacity
#undef instructionList
#undef instructionListCapacity