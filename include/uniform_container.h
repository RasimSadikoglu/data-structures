#ifndef UNIFORM_CONTAINER_H
#define UNIFORM_CONTAINER_H

#define TYPENAME_SIZE 50

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    void *container;
    char type[TYPENAME_SIZE];
} uobj;

uobj uobj_unify(const void *p, size_t size, char type[TYPENAME_SIZE]);

void* uobj_make_unique(const uobj *uo);

void uobj_free(uobj *uo);

#endif // UNIFORM_CONTAINER_H