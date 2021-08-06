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
    fprintf(file, "%c", (char)bytecode.constants.numberConstantsLength & 0xFF);
    int littleEndian = isLittleEndian();
    for (size_t i = 0; i < bytecode.constants.numberConstantsLength; i++) {
        // printf("Writing %zu\n", i);
        double number = bytecode.constants.numberConstants[i];
        uint64_t num = doubleToUint64Bits(number);
        if (!littleEndian) {
            num = swapEndian(num);
            // printf("big endian");
        }

        // printf("Number %f as uint64_t is %llu (bits ", number, num);
        // for (size_t j = 0; j < 64; j++) {
        // printf("%llu", (num >> j) & 0x01);
        // }
        // printf(")\nCHARBITS = ");
        for (size_t j = 0; j < 8; j++) {
            // printf("!!!!");
            unsigned char t = (unsigned char)((num >> (8 * j)) & 0xFF);
            // for (size_t k = 0; k < 8; k++) {
            // printf("%d", (t >> k) & 0x01);
            // }
            fprintf(file, "%c", t);
        }
        // printf("\n");
    }
}

Bytecode readBytecodeFromFile(FILE* file) {
    int c;
    size_t capacity = sizeof(char) * 512;
    char* contents = allocate(capacity);
    size_t length = 0;
    char* characterAndNullByte = allocate(sizeof(char) * 2);
    characterAndNullByte[1] = '\0';
    strcpy(contents, "");
    if (file) {
        while ((c = getc(file)) != EOF) {
            length += 1;
            if (length == capacity - 2) {
                capacity += sizeof(char) * 512;
                contents = reallocate(contents, capacity);
            }
            contents[length - 1] = c;
        }
    }
    free(characterAndNullByte);
    if (!stringStartsWith(contents, "SPLBTC")) {
        fprintf(stderr,
                "Error while reading bytecode : invalid prefix (should start "
                "with SPLBTC)");
        exit(1);
    }
    Bytecode bytecode = {.length = 0,
                         .list = 0,
                         .constants = {.stringConstantsLength = 0,
                                       .stringConstants = NULL,
                                       .numberConstantsLength = 0,
                                       .numberConstants = NULL}};
#define readChar() contents[currentCharacter++]
    int currentCharacter = 6;
    int numberOfStringConstants = readChar();
    bytecode.constants.stringConstantsLength = numberOfStringConstants;
    bytecode.constants.stringConstants =
        allocate(sizeof(char*) * numberOfStringConstants);
    for (int i = 0; i < numberOfStringConstants; i++) {
        int length = readChar();
        bytecode.constants.stringConstants[i] =
            allocate(sizeof(char) * (length + 1));
        bytecode.constants.stringConstants[i][length] = '\0';
        for (int j = 0; j < length; j++) {
            bytecode.constants.stringConstants[i][j] = readChar();
        }
    }
    int numberOfNumberConstants = readChar();
    bytecode.constants.numberConstantsLength = numberOfNumberConstants;
    bytecode.constants.numberConstants =
        allocate(sizeof(uint64_t) * numberOfNumberConstants);
    int littleEndian = isLittleEndian();
    for (int i = 0; i < numberOfNumberConstants; i++) {
        uint64_t out = 0;
        unsigned char* cursor = (unsigned char*)&out;
        unsigned char t;
        for (int j = 0; j < 8; j++) {
            t = readChar();
            // printf("read %d\n", t);
            cursor[j] = t & 0xFF;
            // out = out | (((int)t >> (j * 8)) & 0xFF);
        }
        if (!littleEndian) {
            out = swapEndian(out);
        }
        // printf("Number [uint64_t] is %llu (bits ", out);
        // for (size_t j = 0; j < 64; j++) {
        // printf("%llu", (out >> j) & 0x01);
        // }
        // printf(")\n");
        bytecode.constants.numberConstants[i] = uint64ToDoubleBits(out);
    }

#undef readChar
    return bytecode;
}