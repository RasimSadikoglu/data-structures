#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>

typedef struct binary_tree binary_tree;

binary_tree* binary_tree_create(int (*compare)(void*, void*));

int binary_tree_add_node(binary_tree *bt, void *node);

void binary_tree_free(binary_tree* bt, void (*node_free)(void*));

#endif // BINARY_TREE_H