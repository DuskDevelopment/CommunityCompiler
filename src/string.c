#include "string.h"

#include <stdlib.h>

int stringLength(char *input) {
    int count = 0;
    while(input[count]) {
        count++;
    }

    return count;
}

bool stringCompare(char *string1, char* string2) {
    bool result = (string1 == string2);

    if (string1 && string2) {
        while(*string1 && *string2 && (*string1 == *string2)) {
            ++string1;
            ++string2;
        }

        result = ((*string1 == 0) && (*string2 == 0));
    }

    return result;
}

bool stringCompareWithLength(char *string1, char *string2, int length) {
    bool result = (string1 == string2);
    int cursor = 0;
    while(cursor != length) {
        result = (string1[cursor] == string2[cursor]);
        if (!result) {
            break;
        }
        cursor++;
    }

    return result;
}

char *stringFindNext(char *input, char *search, int count)
{
    char *result = input;

    while(*result) {
        for(int i = 0; i < count; i++) {
            if (*result == search[i]) {
                return result;
            }
        }

        result++;
    }

    return result;
}

char *stringSubstring(char *input, int count) {
    char *result = malloc(sizeof(char) * count + 1);
    for(int i = 0; i < count; i++) {
        result[i] = input[i];
    }

    result[count] = 0;

    return result;
}
