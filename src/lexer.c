#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "string.h"
#include "vector.h"

#define arrayCount(value) (int)(sizeof(value)/sizeof(value[0]))

char *tokenValues[] = {"fn", "(", ")", "{", "}", "return", ";"};

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

void lex(char *fileName) {
    FILE *inputFile;
    long inputFileSize;
    char *inputBuffer;

    inputFile = fopen(fileName, "rb");
    fseek(inputFile, 0, SEEK_END);
    inputFileSize = ftell(inputFile);
    rewind(inputFile);

    inputBuffer = (char *)malloc(inputFileSize * sizeof(char) + 1);
    fread(inputBuffer, inputFileSize, 1, inputFile);
    fclose(inputFile);
    inputBuffer[inputFileSize] = 0;

    vector tokenVector = {0};
    tokenVector.elementSize = sizeof(token);
    tokenVector.maxSize = 20;
    tokenVector.elements = malloc(sizeof(tokenVector.elementSize) * tokenVector.maxSize);

    while(*inputBuffer) {
        if (*inputBuffer == ' ' || *inputBuffer == '\n' || *inputBuffer == '\r' || *inputBuffer == '\t') {
            inputBuffer++;
            continue;
        }

        int tokenLength = stringFindNext(inputBuffer, " \t\n\r(){};", 9) - inputBuffer;
        if (!tokenLength) {
            tokenLength = 1;
        }

        char *tokenValueSubstring = stringSubstring(inputBuffer, tokenLength);

        // printf("%d\n", TokenLength);
        token *newToken = malloc(sizeof(token));
        newToken->tokenType = TOKEN_IDENTIFIER;
        newToken->value = tokenValueSubstring;

        bool matched = false;
        for(int i = 0; i < arrayCount(tokenValues); i++) {
            if (stringCompare(tokenValueSubstring, tokenValues[i])) {
                matched = true;
                newToken->tokenType = i+2;
            }
        }

        if (!matched) {
            if (!isalpha(tokenValueSubstring[0])) {
                newToken->tokenType = TOKEN_CONSTANT;
            }
        }

        pushVector(&tokenVector, newToken);
        // printf("type: %d, value: %s\n", NewToken->TokenType, NewToken->Value);

        if(tokenLength)
            inputBuffer+=tokenLength;
    }

    for(int i = 0; i < tokenVector.size; i++)
    {
        token *currentToken = tokenVector.elements[i];
        printf("type: %d, value: %s\n", currentToken->tokenType, currentToken->value);
    }
}
