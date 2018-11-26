#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

typedef struct vector
{
    int elementSize;
    void **elements;
    int maxSize;
    int size;
} vector;

void pushVector(vector *dest, void *value);

#endif