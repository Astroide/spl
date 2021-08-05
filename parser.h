#ifndef _SPL_PARSER_H_
#define _SPL_PARSER_H_

typedef enum {
    TOKEN_NOT_YET_FOUND,
    TOKEN_VAR,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LCURLYBRACKET,
    TOKEN_RCURLYBRACKET,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_DOT,
    TOKEN_FN,
    TOKEN_COMMA,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH
} TokenType;

typedef struct {
    TokenType type;
    char* stringRepresentation;
    int length;
    int line;
} Token;

typedef struct {
    Token* list;
    int length;
} TokenList;

TokenList parse(char* source);

char* tokenTypeToString(TokenType type);

#endif