#ifndef TREE_H
#define TREE_H

typedef struct tree tree;

typedef struct iterator {
    void *node;
    struct iterator *next;
} iterator;

// Container Operations
#define CONTAINER_CREATE 0
#define CONTAINER_ADD 1
#define CONTAINER_GET 2
#define CONTAINER_REMOVE 3
#define CONTAINER_FREE 4
#define CONTAINER_ITERATOR 5

tree* tree_create(int (*node_compare)(void*, void*), int (*node_find)(void*, void*), void *tree_type);

int tree_add(tree *t, void *node);
void* tree_get(tree *t, void *key);
int tree_remove(tree *t, void *key);

iterator* tree_iterator(tree *t);
void iterator_free(iterator *it);

void tree_free(tree *t, void (*node_free)(void*));

#endif // TREE_H