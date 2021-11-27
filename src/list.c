#include "../include/list.h"

#include <stdlib.h>

struct list {
    void *container; 
    void* (*container_handler)(void *container, void *p, int (*node_handler)(void*, void*), int op);
    int (*node_compare)(void*, void*);
    int (*node_find)(void*, void*);
};

list* list_create(int (*node_compare)(void*, void*), int (*node_find)(void*, void*), void *list_type) {

    list *t = malloc(sizeof(list));

    t->container_handler = list_type;

    t->node_compare = node_compare;
    t->node_find = node_find;

    t->container = t->container_handler(NULL, NULL, NULL, CONTAINER_CREATE);

    return t;
}

int list_add(list *t, void *node) {

    void *root = t->container_handler(t->container, node, t->node_compare, CONTAINER_ADD);

    if (root != NULL) t->container = root;

    return 0;

}

void* list_get(list *t, void *key) {

    return t->container_handler(t->container, key, t->node_find, CONTAINER_GET);

}

int list_remove(list *t, void *key) {

    return t->container_handler(t->container, key, t->node_find, CONTAINER_REMOVE) == NULL;

}

iterator* list_iterator(list *t) {

    return t->container_handler(t->container, NULL, NULL, CONTAINER_ITERATOR);
}

void list_free(list *t, void (*node_free)(void*)) {

    t->container_handler(t->container, node_free, NULL, CONTAINER_FREE);

    free(t);
}

void iterator_free(iterator *it) {

    if (it->next != NULL) iterator_free(it->next);

    free(it);
}