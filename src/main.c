#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "duskc.h"

void help() {
    printf("Usage: %s [options] file...\n", programName);
    printf("Options:\n");
    printf("  --help        Display this information.\n");
    printf("  --version     Display compiler version information.\n");
    printf("  -dumpversion  Display the version of the compiler.\n");
    printf("  -o <file>     Place the output into <file>.\n");
}

void version() {
    printf("duskc (Cross-platform 1.0.0-0preboot0~1.0) 1.0.0\n");
    printf("Copyright (C) 2018 thebennybox-Community.\n");
    printf("This is free software; see the source for copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
}

int main(int argc, char **argv) {
    programName = strrchr(argv[0], '/')+1;
    list *inputFiles = list_new();
    char *outputFile = "a.out";
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') { // Option, maybe
            if(strcmp("--help", argv[i]) == 0) {
                help();
                return 0;
            } else if(strcmp("--version", argv[i]) == 0) {
                version();
                return 0;
            } else if(strcmp("-dumpversion", argv[i]) == 0) {
                printf("0\n");
                return 0;
            } else if(strcmp("-o", argv[i]) == 0) {
                if(i == argc-1)
                    fprintf(stderr, "%s: warning: missing filename after ‘-o‘; ignored\n", programName);
                else {
                    outputFile = argv[i+1];
                    i++;
                }
            } else {
                fprintf(stderr, "%s: warning: invalid option ‘%s‘; ignored\n", programName, argv[i]);
            }
        } else {
            list_add(inputFiles, argv[i]);
        }
    }
    if(!list_size(inputFiles)) {
        fprintf(stderr, "%s: fatal error: no input files\n", programName);
        return 1;
    }
}