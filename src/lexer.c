#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "lexer.h"
#include "stretchy_buffers.h"
#include "string.h"

static Token *lexSource(char *inputBuffer) {
    Token *tokens = NULL;

    while (*inputBuffer) {
        Token token = {0};

        switch (*inputBuffer) {
            case ' ':
            case '\n':
            case '\t':
            case '\r':
            case '\v': {
                // Skip past whitespace
                while (isspace(*inputBuffer)) {
                    inputBuffer++;
                }
                continue;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                char *tokenStart = inputBuffer;
                while (isdigit(*inputBuffer)) {
                    inputBuffer++;
                }

                unsigned long length = inputBuffer - tokenStart;
                char *literal = malloc(sizeof(char) * length + 1);
                strncpy(literal, tokenStart, length);
                literal[length] = '\0';

                long value = strtol(literal, NULL, 10);

                token.tokenType = TOKEN_INTEGER_LITERAL;
                token.intLiteral = value;
                break;
            }
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
            case '_': {
                char *tokenStart = inputBuffer;
                while (isalnum(*inputBuffer) || *inputBuffer == '_') {
                    inputBuffer++;
                }

                unsigned long length = inputBuffer - tokenStart;
                char *identifier = malloc(sizeof(char) * length + 1);
                strncpy(identifier, tokenStart, length);
                identifier[length] = '\0';

                // TODO: Check for identifier or keyword
                token.tokenType = TOKEN_IDENTIFIER;
                token.identifier = identifier;

                break;
            }
            case '(': {
                token.tokenType = TOKEN_OPEN_PAREN;
                token.identifier = "(";
                inputBuffer++;
                break;
            }
            case ')': {
                token.tokenType = TOKEN_CLOSE_PAREN;
                token.identifier = ")";
                inputBuffer++;
                break;
            }
            case '{': {
                token.tokenType = TOKEN_OPEN_BRACE;
                token.identifier = "{";
                inputBuffer++;
                break;
            }
            case '}': {
                token.tokenType = TOKEN_CLOSE_BRACE;
                token.identifier = "}";
                inputBuffer++;
                break;
            }
            case ';': {
                token.tokenType = TOKEN_SEMICOLON;
                token.identifier = ";";
                inputBuffer++;
                break;
            }
            case '\0': {
                token.tokenType = TOKEN_EOF;
                break;
            }
            default: {

                break;
            }
        }

                sb_push(tokens, token);
    }

    for (int i = 0; i < sb_count(tokens); i++) {
        Token currentToken = tokens[i];
        printf("type: %d, ", currentToken.tokenType);
        if (currentToken.tokenType == TOKEN_INTEGER_LITERAL) {
            printf("value: %lu", currentToken.intLiteral);
        } else {
            printf("value: %s", currentToken.identifier);
        }
        printf("\n");
    }

    return tokens;
}

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

    Token *tokens = lexSource(inputBuffer);

    free(inputBuffer);

    return tokens;
}
