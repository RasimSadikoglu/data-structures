#include "../include/tree.h"

#include <stdlib.h>

struct tree {
    void *container; 
    void* (*container_handler)(void *container, void *p, int (*node_handler)(void*, void*), int op);
    int (*node_compare)(void*, void*);
    int (*node_find)(void*, void*);
};

tree* tree_create(int (*node_compare)(void*, void*), int (*node_find)(void*, void*), void *tree_type) {

    tree *t = malloc(sizeof(tree));

    t->container_handler = tree_type;

    t->node_compare = node_compare;
    t->node_find = node_find;

    t->container = t->container_handler(NULL, NULL, NULL, CONTAINER_CREATE);

    return t;
}

int tree_add(tree *t, void *node) {

    void *root = t->container_handler(t->container, node, t->node_compare, CONTAINER_ADD);

    if (root != NULL) t->container = root;

    return 0;

}

void* tree_get(tree *t, void *key) {

    return t->container_handler(t->container, key, t->node_find, CONTAINER_GET);

}

int tree_remove(tree *t, void *key) {

    return t->container_handler(t->container, key, t->node_find, CONTAINER_REMOVE) == NULL;

}

iterator* tree_iterator(tree *t) {

    return t->container_handler(t->container, NULL, NULL, CONTAINER_ITERATOR);
}

void tree_free(tree *t, void (*node_free)(void*)) {

    t->container_handler(t->container, node_free, NULL, CONTAINER_FREE);

    free(t);
}

void iterator_free(iterator *it) {

    if (it->next != NULL) iterator_free(it->next);

    free(it);
}