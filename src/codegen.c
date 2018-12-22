#include "codegen.h"
#include "parser.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>

#ifdef _WIN32
#define restrict
#endif

void codegen(ast_grammar *grammar) {
    LLVMModuleRef module = LLVMModuleCreateWithName("duskc");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMExecutionEngineRef engine;
    LLVMInitializeNativeTarget();
    LLVMLinkInMCJIT();

    LLVMDumpModule(module);
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    freeGrammar(grammar);
}
