#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

#include "string.h"

int stringLength(char *input);

bool stringCompare(char *string1, char* string2);

bool stringCompareWithLength(char *string1, char *string2, int length);

char *stringFindNext(char *input, char *search, int count);

char *stringSubstring(char *input, int count);

#endif
