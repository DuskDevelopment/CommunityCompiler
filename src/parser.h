#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

ast_grammar *parse(Token *tokens);

void printGrammar(ast_grammar *grammar, int numTabs);

void freeGrammar(ast_grammar *grammar);

#endif
