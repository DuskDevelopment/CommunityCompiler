#include <stdio.h>

#include "stretchy_buffers.h"
#include "string.h"

#include "ast.h"
#include "lexer.h"

ast_grammar parseGrammar(Token *tokens, int curPos) {
    ast_grammar result = {
        .types = NULL,
        .statements = NULL
    };
    for(;curPos < sb_count(tokens);) {
        ast_statement *statement = parseStatement(tokens, &curPos);
        if(statement) {
            sb_push(result.types, 0);
            sb_push(result.statements, { .statement = *statement });
            continue;
        }
        ast_function *function = parseFunction(tokens, &curPos);
        if(function) {
            sb_push(result.types, 1);
            sb_push(result.statements, { *function });
            continue;
        }
        fprintf(stderr, "error: expected function or statement");
    }
}

void parse(Token *tokens) {
    ast_grammar grammar = parseGrammar(tokens, 0);
    free(tokens);
}
