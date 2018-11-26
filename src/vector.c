#include "vector.h"

#include <stdlib.h>

void pushVector(vector *dest, void *value)
{
    if(dest->size + 1 <= dest->maxSize)
    {
        dest->elements[dest->size] = value;
        dest->size+=1;
    }
}