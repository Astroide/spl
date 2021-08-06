#include "parser.h"

#include <stdlib.h>
#include <string.h>

#include "util.h"

#define nextChar() \
    (currentCharacter >= sourceLength ? '\0' : source[currentCharacter++])
#define peek() \
    (currentCharacter >= sourceLength ? '\0' : source[currentCharacter])

TokenList parse(char* source) {
    int tokenCapacity = 20;
    TokenList tokens = {.length = 0,
                        .list = allocate(sizeof(Token) * tokenCapacity)};
    size_t sourceLength = strlen(source);
    int currentCharacter = 0;
    int lineNo = 1;
    while (peek() != '\0') {
        char* startPosition = source + currentCharacter;
        int length = 0;
        TokenType type = TOKEN_NOT_YET_FOUND;
        char first = nextChar();
        if ((first >= '0' && first <= '9') || first == '.') {
            length = 1;
            type = TOKEN_NUMBER;
            while ((first = peek()) &&
                   ((first >= '0' && first <= '9') || first == '.')) {
                nextChar();
                length++;
            }
        } else if (first == '"' || first == '\'' || first == '`') {
            type = TOKEN_STRING;
            char delimiter = first;
            length = 1;
            while (++length && (first = nextChar()) != delimiter) {
                if (first == '\n') lineNo++;
            }
        } else if (first == '_' || (first >= 'a' && first <= 'z') ||
                   (first >= 'A' && first <= 'Z')) {
            length = 1;
            while ((first = peek()) == '_' || (first >= 'a' && first <= 'z') ||
                   (first >= 'A' && first <= 'Z') ||
                   (first >= '0' && first <= '9'))
                nextChar(), length++;
            char* all = startAndLengthToString(startPosition, length);
            if (!strcmp(all, "var")) {
                type = TOKEN_VAR;
            } else if (!strcmp(all, "while")) {
                type = TOKEN_WHILE;
            } else if (!strcmp(all, "for")) {
                type = TOKEN_FOR;
            } else if (!strcmp(all, "fn")) {
                type = TOKEN_FN;
            } else if (!strcmp(all, "true")) {
                type = TOKEN_TRUE;
            } else if (!strcmp(all, "false")) {
                type = TOKEN_FALSE;
            } else {
                type = TOKEN_IDENTIFIER;
            }
            free(all);
        } else if (first == '\t' || first == ' ' || first == '\n') {
            if (first == '\n') lineNo++;
            continue;
        } else if (first == '(') {
            length = 1;
            type = TOKEN_LPAREN;
        } else if (first == ')') {
            length = 1;
            type = TOKEN_RPAREN;
        } else if (first == '{') {
            length = 1;
            type = TOKEN_LCURLYBRACKET;
        } else if (first == '}') {
            length = 1;
            type = TOKEN_RCURLYBRACKET;
        } else if (first == '[') {
            length = 1;
            type = TOKEN_LBRACKET;
        } else if (first == ']') {
            length = 1;
            type = TOKEN_RBRACKET;
        } else if (first == ',') {
            length = 1;
            type = TOKEN_COMMA;
        } else if (first == '+') {
            length = 1;
            type = TOKEN_PLUS;
        } else if (first == '-') {
            length = 1;
            type = TOKEN_MINUS;
        } else if (first == '/') {
            length = 1;
            type = TOKEN_SLASH;
        } else if (first == '*') {
            length = 1;
            type = TOKEN_STAR;
        } else {
            fprintf(stderr,
                    "Error while parsing : unexpected character : %c (hex "
                    "0x%X) on line %d\n",
                    first, ((int)first) & 0xff, lineNo);
            exit(1);
        }
        Token newToken = {.length = length,
                          .stringRepresentation = startPosition,
                          .type = type,
                          .line = lineNo};
        if (tokens.length == tokenCapacity - 1) {
            tokenCapacity += 20;
            tokens.list =
                reallocate(tokens.list, sizeof(Token) * tokenCapacity);
        }
        tokens.list[tokens.length++] = newToken;
    }

    return tokens;
}

char* tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_NOT_YET_FOUND:
            return "<error>";
        case TOKEN_VAR:
            return "VAR";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_FOR:
            return "FOR";
        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";
        case TOKEN_LBRACKET:
            return "LBRACKET";
        case TOKEN_RBRACKET:
            return "RBRACKET";
        case TOKEN_LCURLYBRACKET:
            return "LCURLYBRACKET";
        case TOKEN_RCURLYBRACKET:
            return "RCURLYBRACKET";
        case TOKEN_NUMBER:
            return "NUMBER";
        case TOKEN_STRING:
            return "STRING";
        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";
        case TOKEN_DOT:
            return "DOT";
        case TOKEN_FN:
            return "FN";
        case TOKEN_COMMA:
            return "COMMA";
        case TOKEN_TRUE:
            return "TRUE";
        case TOKEN_FALSE:
            return "FALSE";
        case TOKEN_PLUS:
            return "PLUS";
        case TOKEN_MINUS:
            return "MINUS";
        case TOKEN_SLASH:
            return "SLASH";
        case TOKEN_STAR:
            return "STAR";
    }
}