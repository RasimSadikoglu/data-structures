#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "tree.h"

#define BINARY_TREE binary_tree_handler

void* binary_tree_handler(void *container, void *p, int (*node_handler)(void*, void*), int op);

#endif // BINARY_TREE_H