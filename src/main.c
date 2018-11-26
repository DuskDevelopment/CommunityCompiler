#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static void
PrintAndQuit(void)
{
    printf("Usage: dusk <input>\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if(argc == 1)
        PrintAndQuit();
    
    FILE *InputFile;
    long InputFileSize;
    char *InputBuffer;

    InputFile = fopen(argv[1], "rb");
    if(!InputFile)
        PrintAndQuit();
    fseek(InputFile, 0, SEEK_END);
    InputFileSize = ftell(InputFile);
    rewind(InputFile);

    InputBuffer = (char *)malloc(InputFileSize * sizeof(char) + 1);
    fread(InputBuffer, InputFileSize, 1, InputFile);
    fclose(InputFile);
    InputBuffer[InputFileSize] = 0;

    printf("%s\n", InputBuffer);
}
