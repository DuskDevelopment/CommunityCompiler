#ifndef DUSKC_H
#define DUSKC_H

#include <stdlib.h>
#include <string.h>

extern char *programName;

typedef struct list {
    void *data;
    struct list *next;
} list;

list *list_new();

void list_add(list*, void*);

int list_size(list*);

#endif
