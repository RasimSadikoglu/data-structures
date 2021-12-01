#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "list.h"

#define BINARY_SEARCH_TREE binary_search_tree_handler

void* binary_search_tree_handler(void *container, void *p, int (*node_handler)(const void*, const void*, int op), int op);

#endif // BINARY_SEARCH_TREE_H