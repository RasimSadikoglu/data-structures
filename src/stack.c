#include "../include/stack.h"

#define STACK_BLOCK_SIZE 0x10

stack stack_create() {
    stack s;
    s.size = STACK_BLOCK_SIZE;
    s.container = malloc(sizeof(void*) * s.size);
    s.index = 0;

    if (s.container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    return s;
}

void stack_push(stack *s, const void *p, size_t size) {
    if (s->index >= s->size) {
        s->size += STACK_BLOCK_SIZE;
        s->container = realloc(s->container, sizeof(void*) * s->size);
    }

    if (s->container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    s->container[s->index] = malloc(size);

    if (s->container[s->index] == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->container[s->index++], p, size);

    return;
}

void stack_pop(stack *s) {

    if (s->index != 0) s->index--;

    free(s->container[s->index]);

    s->container[s->index] = NULL;

    return;
}

void* stack_top(const stack *s) {

    if (s->index == 0) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    return s->container[s->index - 1];
}

int stack_empty(const stack *s) {

    return s->index == 0;
}

size_t stack_size(const stack *s) {

    return s->index;
}

void stack_free(stack *s) {

    for (size_t i = 0; i < s->size; i++) {
        free(s->container[i]);
    }

    free(s->container);

    return;
}