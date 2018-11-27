#ifndef LEXER_H
#define LEXER_H

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

typedef struct Token {
    int tokenType;
    char *value;
} Token;

Token *lex(char *fileName);

#endif
