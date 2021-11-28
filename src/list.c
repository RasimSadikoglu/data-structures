#include "../include/list.h"

#include <stdlib.h>

struct list {
    void *container; 
    void* (*container_handler)(void *container, void *p, int (*node_handler)(const void*, const void*), int op);
    int (*node_node_compare)(const void*, const void*);
    int (*node_key_compare)(const void*, const void*);
    void (*node_free)(void*);
};

list* list_create(void *list_type, int (*node_node_compare)(const void*, const void*), int (*node_key_compare)(const void*, const void*), void (*node_free)(void*)) {

    list *t = malloc(sizeof(list));

    t->container_handler = list_type;

    t->node_node_compare = node_node_compare;
    t->node_key_compare = node_key_compare;
    t->node_free = node_free;

    t->container = t->container_handler(NULL, NULL, NULL, CONTAINER_CREATE);

    return t;
}

int list_add(list *t, void *node) {

    void *root = t->container_handler(t->container, node, t->node_node_compare, CONTAINER_ADD);

    if (root != NULL) t->container = root;

    return 0;

}

void* list_get(list *t, void *key) {

    return t->container_handler(t->container, key, t->node_key_compare, CONTAINER_GET);

}

int list_remove(list *t, void *key) {

    return t->container_handler(t->container, key, t->node_key_compare, CONTAINER_REMOVE) == NULL;

}

iterator* list_iterator(list *t) {

    return t->container_handler(t->container, NULL, NULL, CONTAINER_ITERATOR);
}

void list_free(list *t) {

    t->container_handler(t->container, t->node_free, NULL, CONTAINER_FREE);

    free(t);
}

void iterator_free(iterator *it) {

    if (it->next != NULL) iterator_free(it->next);

    free(it);
}