#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "string.c"

#define ArrayCount(value) (int)(sizeof(value)/sizeof(value[0]))

char *TokenValues[] = {"fn", "(", ")", "{", "}", "return", ";"};

enum TOKEN_TYPE
{
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

typedef struct Token
{
    int TokenType;
    char *Value;
} Token;

static void
lex(char *FileName)
{  
    FILE *InputFile;
    long InputFileSize;
    char *InputBuffer;

    InputFile = fopen(FileName, "rb");
    fseek(InputFile, 0, SEEK_END);
    InputFileSize = ftell(InputFile);
    rewind(InputFile);

    InputBuffer = (char *)malloc(InputFileSize * sizeof(char) + 1);
    fread(InputBuffer, InputFileSize, 1, InputFile);
    fclose(InputFile);
    InputBuffer[InputFileSize] = 0;

    vector TokenVector = {0};
    TokenVector.ElementSize = sizeof(Token);
    TokenVector.MaxSize = 20;
    TokenVector.Elements = malloc(sizeof(TokenVector.ElementSize) * TokenVector.MaxSize);

    while(*InputBuffer)
    {
        if(*InputBuffer == ' ' || *InputBuffer == '\n' || *InputBuffer == '\r' || *InputBuffer == '\t')
        {
            InputBuffer++;
            continue;
        }

        int TokenLength = StringFindNext(InputBuffer, " \t\n\r(){};", 9) - InputBuffer;
        if(!TokenLength)
            TokenLength = 1;

        char *TokenValueSubstring = StringSubstring(InputBuffer, TokenLength);

        // printf("%d\n", TokenLength);
        Token *NewToken = malloc(sizeof(Token));
        NewToken->TokenType = TOKEN_IDENTIFIER;
        NewToken->Value = TokenValueSubstring;

        bool matched = false;
        for(int i = 0; i < ArrayCount(TokenValues); i++)
        {
            if(StringCompare(TokenValueSubstring, TokenValues[i]))
            {
                matched = true;
                NewToken->TokenType = i+2;
            }
        }

        if(!matched)
            if(!isalpha(TokenValueSubstring[0]))
                NewToken->TokenType = TOKEN_CONSTANT;

        PushVector(&TokenVector, NewToken);
        // printf("type: %d, value: %s\n", NewToken->TokenType, NewToken->Value);

        if(TokenLength)
            InputBuffer+=TokenLength;
    }

    for(int i = 0; i < TokenVector.size; i++)
    {
        Token *CurrentToken = TokenVector.Elements[i];
        printf("type: %d, value: %s\n", CurrentToken->TokenType, CurrentToken->Value);
    }
}
