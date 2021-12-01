#include "../include/list.h"

#include <stdlib.h>

struct list {
    void *container; 
    void* (*container_handler)(void *container, void *p, int (*node_handler)(const void*, const void*, int op), int op);
    int (*node_handler)(const void*, const void*, int op);
};

list* list_create(void *list_type, int (*node_handler)(const void*, const void*, int op)) {

    list *t = malloc(sizeof(list));

    t->container_handler = list_type;

    t->node_handler = node_handler;

    t->container = t->container_handler(NULL, NULL, NULL, CONTAINER_CREATE);

    return t;
}

int list_add(list *t, void *node) {

    void *root = t->container_handler(t->container, node, t->node_handler, CONTAINER_ADD);

    if (root != NULL) t->container = root;

    return 0;

}

void* list_get(list *t, void *key) {

    return t->container_handler(t->container, key, t->node_handler, CONTAINER_GET);

}

int list_remove(list *t, void *key) {

    void *container = t->container_handler(t->container, key, t->node_handler, CONTAINER_REMOVE);
    
    if (container != NULL) t->container = container;

    return 0;

}

iterator* list_iterator(list *t) {

    return t->container_handler(t->container, NULL, NULL, CONTAINER_ITERATOR);
}

void list_free(list *t) {

    t->container_handler(t->container, t->node_handler, NULL, CONTAINER_FREE);

    free(t);
}

void iterator_free(iterator *it) {

    if (it->next != NULL) iterator_free(it->next);

    free(it);
}