#ifndef LEXER_H
#define LEXER_H

enum TOKEN_TYPE {
    TOKEN_EMPTY,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER_LITERAL,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_SEMICOLON,
    TOKEN_EOF
};

typedef struct Token {
    int tokenType;
    union {
        char *identifier;
        char *keyword;
        long intLiteral;
    };
} Token;

Token *lex(char *fileName);

#endif
