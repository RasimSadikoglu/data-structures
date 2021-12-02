#include "../include/binomial_heap.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct container {
    void *node;
    struct container *parent;
    struct container *sibling;
    struct container *child;
    int degree;
} container;

container* binomail_heap_create() {
    return calloc(sizeof(container), 1);
}

void swap(container **c1, container **c2) {
    container *temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void* merge(container *c, int (*node_handler)(const void*, const void*, int op)) {

    if (c == NULL) return NULL;

    for (container *it = c, *prev = NULL; it != NULL; prev = it, it = it->sibling) {
        container *next = it->sibling;

        if (next == NULL || it->degree != next->degree) continue;

        if (next->sibling != NULL && next->degree == next->sibling->degree) continue;

        container *next_next = next->sibling;

        if (node_handler(it->node, next->node, NODE_NODE_COMPARE) > 0) swap(&it, &next);

        next->parent = it;
        next->sibling = it->child;

        it->sibling = next_next;
        it->child = next;
        it->degree++;

        if (prev == NULL) c = it;
        else prev->sibling = it;

        return merge(c, node_handler);
    }

    return c;
}

void* binomail_heap_add(container *c, void *node, int (*node_handler)(const void*, const void*, int op)) {

    if (c->node == NULL) {
        c->node = node;
        return NULL;
    }
    
    container *root = binomail_heap_create();

    root->node = node;

    root->sibling = c;

    container *merged = merge(root, node_handler);
    if (merged != NULL) root = merged;

    return root;
}

void* binomail_heap_get(container *c, int (*node_handler)(const void*, const void*, int op)) {
    
    void *node = NULL;

    for (container *it = c; it != NULL && it->node != NULL; it = it->sibling) {
        if (node == NULL || node_handler(it->node, node, NODE_NODE_COMPARE) < 0) node = it->node;
    }

    return node;
}

void* binomail_heap_remove(container *c, int (*node_handler)(const void*, const void*, int op)) {
    
    if (c == NULL || c->node == NULL) return NULL;
    
    container *max_prev = NULL, *max = NULL;

    for (container *it = c, *prev = NULL; it != NULL; prev = it, it = it->sibling) {
        if (max == NULL || node_handler(it->node, max->node, NODE_NODE_COMPARE) < 0) {
            max_prev = prev;
            max = it;
        }
    }

    if (max_prev == NULL) c = max->sibling;
    else max_prev->sibling = max->sibling;

    container *childs = max->child;

    node_handler(max->node, NULL, NODE_FREE);
    free(max);

    if (c == NULL) return childs == NULL ? binomail_heap_create() : childs;

    for (container *it = c, *prev = NULL; childs != NULL;) {

        if (it == NULL || childs->degree < it->degree) {

            container *next_child = childs->sibling;

            childs->parent = NULL;
            childs->sibling = it;
            
            if (prev == NULL) c = childs;
            else prev->sibling = childs;

            childs = next_child;

            it = c;
            prev = NULL;
            continue;
        }

        prev = it;
        it = it->sibling;
    }

    container *merged = merge(c, node_handler);
    if (merged != NULL) c = merged;

    return c;

}

void binomail_heap_iterator(container *c, iterator **it) {

    if (c->node == NULL) return;

    (*it)->node = c->node;
    (*it)->next = calloc(sizeof(iterator), 1);
    (*it)->location = c->degree;
    *it = (*it)->next;

    if (c->sibling != NULL) binomail_heap_iterator(c->sibling, it);
    if (c->child != NULL) binomail_heap_iterator(c->child, it);

}

void binomail_heap_free(container *c, int (*node_handler)(const void*, const void*, int op)) {
    
    if (c == NULL) return;

    binomail_heap_free(c->sibling, node_handler);
    binomail_heap_free(c->child, node_handler);

    node_handler(c->node, NULL, NODE_FREE);
    free(c);

}

void* binomial_heap_handler(void *container, void *p, int (*node_handler)(const void*, const void*, int op), int op) {

    switch (op) {
        case CONTAINER_CREATE:
            return binomail_heap_create();
        case CONTAINER_ADD:
            return binomail_heap_add(container, p, node_handler);
        case CONTAINER_GET:
            return binomail_heap_get(container, node_handler);
        case CONTAINER_REMOVE:
            return binomail_heap_remove(container, node_handler);
        case CONTAINER_ITERATOR:;
            iterator *it = calloc(sizeof(iterator), 1), *it_c = it;
            binomail_heap_iterator(container, &it_c);
            return it;
        case CONTAINER_FREE:
            binomail_heap_free(container, p);
            return NULL;
        default:
            return NULL;
    }
}

void* binomial_heap_handler_address() {
    return binomial_heap_handler;
}