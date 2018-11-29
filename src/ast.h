#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef struct ast_expression {
    int type;
    union {
        char *identifier;
        int number;
        double floatingNumber;
    } content;
} ast_expression;

typedef struct ast_vardecl {
    bool constant;
    char *name;
    char *type;
    bool hasValue;
    ast_expression value;
} ast_vardecl;

typedef struct ast_return {
    ast_expression value;
} ast_return;

typedef struct ast_statement {
    int type;
    union {
        ast_expression expression;
        ast_vardecl vardecl;
    } content;
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
} ast_grammar;

#endif
