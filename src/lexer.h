#ifndef LEXER_H
#define LEXER_H

#include "vector.h"

enum TOKEN_TYPE {
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_FUNCTION,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_RETURN,
    TOKEN_SEMICOLON,
};

typedef struct token {
    int tokenType;
    char *value;
} token;

vector lex(char *fileName);

#endif