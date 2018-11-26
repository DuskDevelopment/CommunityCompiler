#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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
PrintAndQuit(void)
{
    printf("Usage: dusk <input>\n");
    exit(EXIT_FAILURE);
}

typedef struct Vector
{
    int ElementSize;
    void **Elements;
    int MaxSize;
    int Location;
} Vector;

static int
StringLength(char *Input)
{
    int Count = 0;
    while(Input[Count])
    {
        Count++;
    }
    return Count;
}

// true if equal
// must be null terminated
static bool
StringCompare(char *String1, char* String2)
{
    bool Result = (String1 == String2);

    if(String1 && String2)
    {
        while(*String1 && *String2 && (*String1 == *String2))
        {
            ++String1;
            ++String2;
        }

        Result = ((*String1 == 0) && (*String2 == 0));
    }

    return Result;
}

static bool
StringCompareWithLength(char *String1, char *String2, int Length)
{
    bool Result = (String1 == String2);
    int Cursor = 0;
    while(Cursor != Length)
    {
        Result = (String1[Cursor] == String2[Cursor]);
        if(!Result)
            break;
        Cursor++;
    }

    return Result;
}

static char*
StringFindNext(char *Input, char *Search, int Count)
{
    char *Result = Input;

    while(*Result)
    {
        for(int i = 0; i < Count; i++)
        {
            if(*Result == Search[i])
                return Result;
        }

        Result++;
    }

    return Result;
}

static char*
StringSubstring(char *Input, int Count)
{
    char *Result = malloc(sizeof(char) * Count + 1);
    for(int i = 0; i < Count; i++)
    {
        Result[i] = Input[i];
    }

    Result[Count] = 0;

    return Result;
}

static void PushVector(Vector *Dest, void *Value)
{
    if(Dest->Location + 1 <= Dest->MaxSize)
    {
        Dest->Elements[Dest->Location] = Value;
        Dest->Location+=1;
    }
}

int main(int argc, char **argv) {
    if(argc == 1)
        PrintAndQuit();
    
    FILE *InputFile;
    long InputFileSize;
    char *InputBuffer;

    InputFile = fopen(argv[1], "rb");
    if(!InputFile)
        PrintAndQuit();
    fseek(InputFile, 0, SEEK_END);
    InputFileSize = ftell(InputFile);
    rewind(InputFile);

    InputBuffer = (char *)malloc(InputFileSize * sizeof(char) + 1);
    fread(InputBuffer, InputFileSize, 1, InputFile);
    fclose(InputFile);
    InputBuffer[InputFileSize] = 0;

    Vector TokenVector = {0};
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

    for(int i = 0; i < TokenVector.Location; i++)
    {
        Token *CurrentToken = TokenVector.Elements[i];
        printf("type: %d, value: %s\n", CurrentToken->TokenType, CurrentToken->Value);
    }

    return 0;
}
