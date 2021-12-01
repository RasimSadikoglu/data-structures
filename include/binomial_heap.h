#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include "list.h"

#define BINOMIAL_HEAP binomial_heap_handler

void* binomial_heap_handler(void *container, void *p, int (*node_handler)(const void*, const void*, int op), int op);

#endif // BINOMIAL_HEAP_H