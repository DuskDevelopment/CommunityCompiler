#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include "lexer.h"

typedef enum EXPRESSION_TYPE {
    TYPE_IDENTIFIER,
    TYPE_INTEGER,
    TYPE_REAL
} EXPRESSION_TYPE;

typedef struct ast_expression {
    EXPRESSION_TYPE type;
    union {
        char *identifier;
        int integer;
        double real;
    };
} ast_expression;

typedef struct ast_vardecl {
    bool constant;
    char *name;
    char *type;
    bool hasValue;
    ast_expression value;
} ast_vardecl;

typedef struct ast_return {
    ast_expression *value;
} ast_return;

typedef enum STATEMENT_TYPE {
    TYPE_EXPRESSION,
    TYPE_VARDECL,
    TYPE_RETURN
} STATEMENT_TYPE;

typedef struct ast_statement {
    STATEMENT_TYPE type;
    union {
        ast_expression *expression;
        ast_vardecl *vardecl;
        ast_return *returnStatement;
    };
} ast_statement;

typedef struct ast_codeBlock {
    ast_statement **statements;
    bool hasFinalExpression;
    ast_expression *finalExpression;
} ast_codeBlock;

typedef struct ast_function {
    char *name;
    struct {
        char *name;
        char *type;
    } *parameters;
    char *returnType;
    ast_codeBlock *codeBlock;
} ast_function;

typedef struct ast_grammar {
    int *types;
    union {
        ast_function *function;
        ast_statement *statement;
    } *statements;
    Token *origTokens;
} ast_grammar;

#endif
