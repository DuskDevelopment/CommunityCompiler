#include <stdio.h>

#include "ast.h"
#include "parser.h"
#include "stretchy_buffers.h"
#include "string.h"

// This function will be rewriteen when we need more types of expressions. For now, it only acknowledges integers.
ast_expression *parseExpression(Token *tokens, int *pos, int *endPos) {
    ast_expression *result = malloc(sizeof(ast_expression));
    result->type = 1; // integer
    int curPos = *pos;
    if(tokens[curPos].tokenType != TOKEN_INTEGER_LITERAL) {
        fprintf(stderr, "Expected integer literal ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    result->integer = tokens[curPos].intLiteral;
    curPos++;
    
    *pos = curPos;
    *endPos = curPos;
    return result;
}

ast_return *parseReturn(Token *tokens, int *pos, int *endPos) {
    ast_expression *value;
    int curPos = *pos;
    if(tokens[curPos].tokenType != TOKEN_IDENTIFIER || !stringCompare("return", tokens[curPos].identifier)) {
        fprintf(stderr, "Expected return statement ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    if(!(value = parseExpression(tokens, &curPos, endPos))) {
        return NULL; // End pos has already been set, error has been printed
    }
    
    *pos = curPos;
    *endPos = curPos;
    ast_return *result = malloc(sizeof(ast_return));
    {
        result->value = value;
    }
    return result;
}

// This function will be rewritten when we need more statements. For now, it only acknowledges return.
ast_statement *parseStatement(Token *tokens, int *pos, int *endPos) {
    ast_statement *result = malloc(sizeof(ast_statement));
    result->type = 2; // return
    int curPos = *pos;
    if(tokens[curPos].tokenType != TOKEN_IDENTIFIER || !stringCompare("return", tokens[curPos].identifier)) {
        fprintf(stderr, "Expected return statement ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    if(!(result->returnStatement = parseReturn(tokens, &curPos, endPos))) {
        return NULL; // End pos has already been set, error has been printed
    }
    if(tokens[curPos].tokenType != TOKEN_SEMICOLON) {
        fprintf(stderr, "Expected semicolon ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    
    *pos = curPos;
    *endPos = curPos;
    return result;
}

ast_codeBlock *parseCodeBlock(Token *tokens, int *pos, int *endPos) {
    ast_statement **statements = NULL; // stretchy buffer
    bool hasFinalExpression = false; // Don't allow for now
    ast_expression *finalExpression = NULL;
    int curPos = *pos;
    if(tokens[curPos].tokenType != TOKEN_OPEN_BRACE) { // Expect code block
        fprintf(stderr, "Expected beginning of code block ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    
    ast_statement *curStatement;
    while(true) {
        if(tokens[curPos].tokenType == TOKEN_CLOSE_BRACE) {
            curPos++;
            break;
        }
        if(!(curStatement = parseStatement(tokens, &curPos, endPos))) {
            return NULL; // End pos has already been set, error has been printed
        }
        sb_push(statements, curStatement);
    }
    
    *pos = curPos;
    *endPos = curPos;
    ast_codeBlock *result = malloc(sizeof(ast_codeBlock));
    {
        result->statements = statements;
        result->hasFinalExpression = hasFinalExpression;
        result->finalExpression = finalExpression;
    }
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
    if(tokens[curPos].tokenType != TOKEN_IDENTIFIER || !stringCompare("fn", tokens[curPos].identifier)) { // Not a function if it doesn't begin with `fn`
        fprintf(stderr, "Expected function ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    if(tokens[curPos].tokenType != TOKEN_IDENTIFIER) { // Expect identifier
        fprintf(stderr, "Expected identifier ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    name = tokens[curPos].identifier;
    curPos++;
    if(tokens[curPos].tokenType != TOKEN_OPEN_PAREN) { // Expect open parenthesis
        fprintf(stderr, "Expected open parenthesis ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    curPos++;
    while(tokens[curPos].tokenType != TOKEN_CLOSE_PAREN) { // Until closed parenthesis (or something else goes wrong)
        // Will fill in later
    }
    curPos++;
    // I will write code to detect return type when the token exists
    if(tokens[curPos].tokenType != TOKEN_OPEN_BRACE) { // Expect code block
        fprintf(stderr, "Expected beginning of code block ");
        if(endPos) *endPos = curPos;
        return NULL;
    }
    if(!(codeBlock = parseCodeBlock(tokens, &curPos, endPos))) {
        return NULL; // End pos has already been set
    }
    *pos = curPos;
    *endPos = curPos;
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
        int failPos;
        if(tokens[curPos].tokenType == TOKEN_IDENTIFIER && stringCompare("fn", tokens[curPos].identifier)) {
            ast_function *function = parseFunction(tokens, &curPos, &failPos);
            if(function) {
                sb_push(types, 1);
                sb_add(statements, 1);
                statements[sb_count(statements)-1].function = function;
                continue;
            } else {
                *endPos = failPos;
                return NULL;
            }
        }
        ast_statement *statement = parseStatement(tokens, &curPos, &failPos);
        if(statement) {
            sb_push(types, 0);
            sb_add(statements, 1);
            statements[sb_count(statements)-1].statement = statement;
            continue;
        } else {
            *endPos = failPos;
            return NULL;
        }
    }
    ast_grammar *result = malloc(sizeof(ast_grammar));
    {
        result->types = types;
        result->statements = statements;
    }
    return result;
}

void parse(Token *tokens) {
    int position = -1;
    ast_grammar *grammar = parseGrammar(tokens, &position);
    if(position != -1) fprintf(stderr, "at token id %i\n", position);

    // Clean up tokens
    for (int i = 0; i < sb_count(tokens); ++i) {
        Token token = tokens[i];
        int type = token.tokenType;
        if (type == TOKEN_IDENTIFIER) {
            free(token.identifier);
        }
    }

    sb_free(tokens);
}
