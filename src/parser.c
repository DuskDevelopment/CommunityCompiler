#include <stdio.h>

#include "stretchy_buffers.h"
#include "string.h"

#include "ast.h"
#include "lexer.h"

ast_statement *parseStatement(Token *tokens, int *pos, int *endPos) {
    if(endPos) *endPos = *pos;
    return NULL;
}

ast_codeBlock *parseCodeBlock(Token *tokens, int *pos, int *endPos) {
    if(endPos) *endPos = *pos;
    return NULL;
}

ast_function *parseFunction(Token *tokens, int *pos, int *endPos) {
    char *name;
    struct {
        char *name;
        char *type;
    } *parameters = NULL; // stretchy buffer
    char *returnType = NULL; // Token for return type doesn't exists; can't detect
    ast_codeBlock *codeBlock;
    int curPos = *pos;
    if(tokens[curPos].tokenType != 2) { // Not a function if it doesn't begin with `fn`
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    if(tokens[curPos].tokenType != 0) { // Expect identifier
        if(endPos) *endPos = curPos;
        return NULL;
    }
    name = tokens[curPos].value;
    curPos++;
    if(tokens[curPos].tokenType != 3) { // Expect open parenthesis
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    while(tokens[curPos].tokenType != 4) { // Until closed parenthesis (or something else goes wrong)
        // Will fill in later
    }
    curPos++;
    // Detect return type when the token exists
    if(!(codeBlock = parseCodeBlock(tokens, &curPos, endPos))) {
        return NULL; // End pos has already been set
    }
    *pos = curPos;
    ast_function *result = malloc(sizeof(ast_function));
    {
        result->name = name;
        result->parameters = parameters;
        result->returnType = returnType;
        result->codeBlock = codeBlock;
    }
    return result;
}

ast_grammar *parseGrammar(Token *tokens, int *endPos) {
    int *types = NULL;
    int curPos = 0;
    union {
        ast_function *function;
        ast_statement *statement;
    } *statements = NULL; // stretchy buffer
    for(;curPos < sb_count(tokens);) {
        ast_statement *statement = parseStatement(tokens, &curPos, NULL);
        if(statement) {
            sb_push(types, 0);
            sb_add(statements, 1);
            statements[sb_count(statements)-1].statement = statement;
            continue;
        }
        ast_function *function = parseFunction(tokens, &curPos, NULL);
        if(function) {
            sb_push(types, 1);
            sb_add(statements, 1);
            statements[sb_count(statements)-1].function = function;
            continue;
        }
        fprintf(stderr, "error: expected function or statement\n");
        *endPos = curPos;
        return NULL;
    }
    ast_grammar *result = malloc(sizeof(ast_grammar));
    {
        result->types = types;
        result->statements = statements;
    }
    *endPos = curPos;
    return result;
}

void parse(Token *tokens) {
    int position = 0;
    ast_grammar *grammar = parseGrammar(tokens, &position);
    fprintf(stderr, "at token id %i\n", position);
    sb_free(tokens);
}
