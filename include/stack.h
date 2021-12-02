#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    void **container;
    size_t size;
    size_t index;
} stack;

stack stack_create();

// Modifiers
void stack_push(stack *s, const void *p, size_t size);
void stack_pop(stack *s);

// Element Access
void* stack_top(const stack *s);

// Capacity
int stack_empty(const stack *s);
size_t stack_size(const stack *s);

// Memory Management
void stack_free(stack *s);

#endif // STACK_H