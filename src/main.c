#include "lexer.h"
#include "parser.h"
#include "stretchy_buffers.h"
#include "string.h"

#include <stdlib.h>
#include <stdio.h>

static void
print_help(void) {
    printf("Usage: duskc [options] file...\n");
    printf("Options:\n");
    printf("  --help        Display this information.\n");
    printf("  --version     Display compiler version information.\n");
    printf("  -dumpversion  Display the version of the compiler.\n");
    printf("  -o <file>     Place the output into <file>.\n");
}

static void
print_version(void) {
    printf("duskc (Cross-platform 1.0.0-0preboot0~1.0) 1.0.0\n");
    printf("Copyright (C) 2018 thebennybox-Community.\n");
    printf("This is free software; see the source for copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
}

int main(int argc, char **argv) {

    if (argc == 1) {
        print_help();
    }

    char **inputFiles = NULL;
    //char *outputFileName = "a.out";

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (stringCompare(argv[i], "--help")) {
                print_help();
                return 0;
            } else if (stringCompare(argv[i], "--version")) {
                print_version();
                return 0;
            } else if (stringCompare(argv[i], "-dumpversion")) {
                printf("1\n");
                return 0;
            } else if (stringCompare(argv[i], "-o")) {
                if (i == argc - 1) {
                    printf("No output file specified with the -o flag. Ignoring\n");
                } else {
                    //outputFileName = argv[++i];
                }
            } else {
                printf("Invalid option specified. Ignoring.\n");
            }
        } else {
            sb_push(inputFiles, argv[i]);
        }
    }

    if (!sb_count(inputFiles)) {
        printf("No input files specified. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < sb_count(inputFiles); i++) {
        char *inputFile = inputFiles[i];
        freeGrammar(parse(lex(inputFile)));
    }

    sb_free(inputFiles);

    return 0;
}
