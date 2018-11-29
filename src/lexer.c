#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "stretchy_buffers.h"
#include "string.h"

#define arrayCount(value) (int)(sizeof(value)/sizeof((value)[0]))

char *tokenValues[] = {"fn", "(", ")", "{", "}", "return", ";"};

#include "lexer.h"

Token *lex(char *fileName) {
    FILE *inputFile;
    long inputFileSize;
    char *inputBuffer;

    inputFile = fopen(fileName, "rb");
    fseek(inputFile, 0, SEEK_END);
    inputFileSize = ftell(inputFile);
    rewind(inputFile);

    inputBuffer = (char *) malloc(inputFileSize * sizeof(char) + 1);
    fread(inputBuffer, inputFileSize, 1, inputFile);
    fclose(inputFile);
    inputBuffer[inputFileSize] = 0;

    Token *tokens = NULL;

    while (*inputBuffer) {
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
        Token newToken = {
                .tokenType = TOKEN_IDENTIFIER,
                .value = tokenValueSubstring
        };

        bool matched = false;
        for (int i = 0; i < arrayCount(tokenValues); i++) {
            if (stringCompare(tokenValueSubstring, tokenValues[i])) {
                matched = true;
                newToken.tokenType = i + 2;
            }
        }

        if (!matched) {
            if (!isalpha(tokenValueSubstring[0])) {
                newToken.tokenType = TOKEN_CONSTANT;
            }
        }

        sb_push(tokens, newToken);
        // printf("type: %d, value: %s\n", NewToken->TokenType, NewToken->Value);

        inputBuffer += tokenLength;
    }

    for (int i = 0; i < sb_count(tokens); i++) {
        Token currentToken = tokens[i];
        printf("type: %d, value: %s\n", currentToken.tokenType, currentToken.value);
    }

    return tokens;
}
