#include "ast.h"
#include "parser.h"
#include "stretchy_buffers.h"
#include "string.h"

void parse(Token *tokens) {

    // Clean up tokens
    for (int i = 0; i < sb_count(tokens); ++i) {
        Token token = tokens[i];
        int type = token.tokenType;
        if (type == TOKEN_INTEGER_LITERAL || type == TOKEN_IDENTIFIER) {
            free(token.identifier);
        }
    }

    sb_free(tokens);
}
