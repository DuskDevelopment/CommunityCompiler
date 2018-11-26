#include "vector.c"
#include "lexer.c"

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

static int
main(int argc, char **argv) {

    if (argc == 1) {
        print_help();
    }

    vector inputFiles = {0};
    inputFiles.MaxSize = 20;
    inputFiles.Elements = malloc(inputFiles.MaxSize * sizeof(char **));

    char *outputFileName = "a.out";

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (StringCompare(argv[i], "--help")) {
                print_help();
            } else if (StringCompare(argv[i], "--version")) {
                print_version();
            } else if (StringCompare(argv[i], "--dumpversion")) {
                print_version();
            } else if (StringCompare(argv[i], "-o")) {
                if (i == argc-1) {
                    printf("No output file specified with the -o flag. Ignoring\n");
                } else {
                    outputFileName = argv[++i];
                }
            } else {
                printf("Invalid option specified. Ignoring.\n");
            }
        } else {
            PushVector(&inputFiles, argv[i]);
        }
    }

    if (!inputFiles.size) {
        printf("No input files specified. Exiting.\n");
        return 1;
    }

    for(int i = 0; i < inputFiles.size; i++)
    {
        char *inputFile = (char *)inputFiles.Elements[i];
        lex(inputFile);
    }

    return 0;
}