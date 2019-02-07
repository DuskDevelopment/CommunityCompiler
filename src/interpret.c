#include <stdbool.h>
#include <stdio.h>

#include "ast.h"
#include "interpret.h"
#include "parser.h"
#include "stretchy_buffers.h"

typedef enum INTERPRETER_TYPE {
    INTEGER,
    DOUBLE
} INTERPRETER_TYPE;

typedef struct interpreter_value {
    INTERPRETER_TYPE type;
    union {
        int integer;
        double doubleVal;
    };
} interpreter_value;

typedef struct interpreter_state {
    bool crashed;
    bool returned;
    int returnValue;
} interpreter_state;

interpreter_value *interpretExpression(interpreter_state *state, ast_expression *expression) {
    switch(expression->type) {
        case TYPE_INTEGER: {
            interpreter_value *result = malloc(sizeof(interpreter_value));
            result->type = INTEGER;
            result->integer = expression->integer;
            return result;
        }
        case TYPE_REAL: {
            interpreter_value *result = malloc(sizeof(interpreter_value));
            result->type = DOUBLE;
            result->doubleVal = expression->real;
            return result;
        }
        default:
            fprintf(stderr, "ERROR: Unrecognized expression type!\n");
            state->crashed = true;
            return NULL;
    }
}

void interpretStatement(interpreter_state *state, ast_statement *statement) {
    switch(statement->type) {
        case TYPE_RETURN: {
            ast_return *returnStatement = statement->returnStatement;
            interpreter_value *result = interpretExpression(state, returnStatement->value);
            if(state->crashed) return;
            if(result->type != INTEGER) {
                fprintf(stderr, "ERROR: Main function didn't return an integer!\n");
                state->crashed = true;
                free(result);
                return;
            }
            state->returned = true;
            state->returnValue = result->integer;
            free(result);
            break;
        }
        default:
            // WIP
            break;
    }
}

int interpret(ast_grammar *ast) {
    interpreter_state state;
    state.crashed = false;
    state.returned = false;
    for(int i = 0; i < sb_count(ast->types) && !state.crashed; i++) {
        if(state.returned) {
            fprintf(stderr, "ERROR: Main has already returned!\n");
            state.crashed = true;
            break;
        }
        interpretStatement(&state, ast->statements[i].statement);
    }
    freeGrammar(ast);
    if(state.returned) {
        printf("Return value = %i\n", state.returnValue);
    } else {
        fprintf(stderr, "WARNING: Main never returned! This may become an error in the future.\n");
        state.returnValue = 0;
    }
    if(state.crashed) {
        fprintf(stderr, "Crashed, exiting...\n");
        return 1;
    }
    return state.returnValue;
}
