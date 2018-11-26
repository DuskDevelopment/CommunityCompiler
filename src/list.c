#include "duskc.h"

list *list_new() {
    list *result = malloc(sizeof(list));
    result->data = 0;
    result->next = 0;
    return result;
}

void list_add(list *theList /* Anybody got a better variable name? */, void *data) {
    list *curList = theList;
    while(curList->next) curList = curList->next;
    curList->data = data;
    curList->next = list_new();
}

int list_size(list *theList) {
    int size = 0;
    list *curList = theList;
    while(curList->next) {
        curList = curList->next;
        size++;
    }
    return size;
}
