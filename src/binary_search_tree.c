#include "../include/binary_search_tree.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct container {
    void *node;
    struct container *left;
    struct container *right;
} container;

container* binary_search_tree_create() {

    container *c = malloc(sizeof(container));

    c->node = NULL;
    c->left = NULL;
    c->right = NULL;

    return c;
}

void* binary_search_tree_add(container *c, void *node, int (*node_handler)(const void*, const void*, int op)) {
    
    if (c->node == NULL) {
        c->node = node;
        return NULL;
    }

    if (node_handler(c->node, node, NODE_NODE_COMPARE) > 0) {
        if (c->left == NULL) c->left = binary_search_tree_create();
        return binary_search_tree_add(c->left, node, node_handler);
    } else {
        if (c->right == NULL) c->right = binary_search_tree_create();
        return binary_search_tree_add(c->right, node, node_handler);
    }
}

void* binary_search_tree_get(container *c, void *key, int (*node_handler)(const void*, const void*, int op)) {
    
    if (c->node == NULL) return NULL;

    int cmp = node_handler(c->node, key, NODE_KEY_COMPARE);

    if (cmp == 0) return c->node;
    else if (cmp > 0) return c->left == NULL ? NULL : binary_search_tree_get(c->left, key, node_handler);
    else return c->right == NULL ? NULL : binary_search_tree_get(c->right, key, node_handler);
}

void* binary_search_tree_remove(container *c, void *key, int (*node_handler)(const void*, const void*, int op)) {
    return NULL;
}

void binary_search_tree_iterator(container *c, iterator **it, int depth) {

    if (c->node == NULL) return;

    if (c->left != NULL) binary_search_tree_iterator(c->left, it, depth + 1);

    (*it)->node = c->node;
    (*it)->next = calloc(sizeof(iterator), 1);
    (*it)->location = depth;
    *it = (*it)->next;

    if (c->right != NULL) binary_search_tree_iterator(c->right, it, depth + 1);
}

void binary_search_tree_free(container *c, int (*node_handler)(const void*, const void*, int op)) {

    node_handler(c->node, NULL, NODE_FREE);

    if (c->left != NULL) binary_search_tree_free(c->left, node_handler);
    if (c->right != NULL) binary_search_tree_free(c->right, node_handler); 

    free(c);

}

void* binary_search_tree_handler(void *container, void *p, int (*node_handler)(const void*, const void*, int op), int op) {

    switch (op) {
        case CONTAINER_CREATE:
            return binary_search_tree_create();
        case CONTAINER_ADD:
            return binary_search_tree_add(container, p, node_handler);
        case CONTAINER_GET:
            return binary_search_tree_get(container, p, node_handler);
        case CONTAINER_REMOVE:
            return binary_search_tree_remove(container, p, node_handler);
        case CONTAINER_ITERATOR:;
            iterator *it = calloc(sizeof(iterator), 1), *it_c = it;
            binary_search_tree_iterator(container, &it_c, 0);
            return it;
        case CONTAINER_FREE:
            binary_search_tree_free(container, p);
            return NULL;
        default:
            return NULL;
    }
}

void* binary_search_tree_handler_address() {
    return binary_search_tree_handler;
}