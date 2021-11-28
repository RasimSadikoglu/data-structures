#include "../include/binomial_heap.h"

#include <stdlib.h>

typedef struct container {
    void *node;
    struct container *parent;
    struct container *sibling;
    struct container *child;
} container;

container* binomail_heap_create() {
    return calloc(sizeof(container), 1);
}

void* binomail_heap_add(container *c, void *node, int (*node_handler)(const void*, const void*)) {
    return NULL;
}

void* binomail_heap_get(container *c, void *key, int (*node_handler)(const void*, const void*)) {
    return NULL;
}

void* binomail_heap_remove(container *c, void *key, int (*node_handler)(const void*, const void*)) {
    return NULL;
}

void binomail_heap_iterator(container *c, iterator **it, int depth) {
    return;
}

void* binomail_heap_free(container *c, void (*node_free)(void*)) {
    return NULL;
}

void* binomail_heap_handler(void *container, void *p, int (*node_handler)(const void*, const void*), int op) {

    switch (op) {
        case CONTAINER_CREATE:
            return binomail_heap_create();
        case CONTAINER_ADD:
            return binomail_heap_add(container, p, node_handler);
        case CONTAINER_GET:
            return binomail_heap_get(container, p, node_handler);
        case CONTAINER_REMOVE:
            return binomail_heap_remove(container, p, node_handler);
        case CONTAINER_ITERATOR:;
            iterator *it = calloc(sizeof(iterator), 1), *it_c = it;
            binomail_heap_iterator(container, &it_c, 1);
            return it;
        case CONTAINER_FREE:
            return binomail_heap_free(container, p);
        default:
            return NULL;
    }
}