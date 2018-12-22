#include "codegen.h"
#include "stretchy_buffers.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>

#ifdef _WIN32
// Windows doesn't support the restrict keyword
#define restrict
#endif

LLVMValueRef codegenExpression(ast_expression *expression) {
    return LLVMConstInt(LLVMIntType(32), expression->integer, true);
}

void codegenReturn(ast_return *returnStatement, LLVMBuilderRef builder) {
    LLVMBuildRet(builder, codegenExpression(returnStatement->value));
}

void codegenStatement(ast_statement *statement, LLVMBuilderRef builder) {
    switch(statement->type) {
        case TYPE_RETURN:
            codegenReturn(statement->returnStatement, builder);
            break;
        default:
            // I can't codegen this! But... I won't complain.
            break;
    }
}

void codegen(ast_grammar *grammar) {
    LLVMModuleRef module = LLVMModuleCreateWithName("duskc");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMExecutionEngineRef engine;
    LLVMInitializeNativeTarget();
    LLVMLinkInMCJIT();

    LLVMTypeRef *mainParams = malloc(0); // I mean, I may be able to pass NULL, but I'm not sure...
    LLVMTypeRef mainType = LLVMFunctionType(LLVMIntType(32), mainParams, 0, 0);
    LLVMValueRef main = LLVMAddFunction(module, "main", mainType);
    LLVMSetLinkage(main, LLVMExternalLinkage);

    LLVMBasicBlockRef mainBlock = LLVMAppendBasicBlock(main, "entry");
    LLVMPositionBuilderAtEnd(builder, mainBlock);

    for(int i = 0; i < sb_count(grammar->types); i++) {
        if(grammar->types[i] == 1) {
            // Function generation, WIP
        } else {
            codegenStatement(grammar->statements[i].statement, builder);
        }
    }

    if(LLVMVerifyFunction(main, LLVMPrintMessageAction) == 1) {
        fprintf(stderr, "Invalid main function");
        LLVMDeleteFunction(main);
    }
    LLVMDumpModule(module);
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    freeGrammar(grammar);
}
