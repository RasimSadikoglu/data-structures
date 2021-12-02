#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **container;
    size_t size;
    size_t index;
} vector;

vector vector_create(size_t sov, size_t soe);

// Modifiers
void vector_clear(vector *v);
void vector_insert(vector *v, const void *p, size_t size, size_t index);
void vector_erase(vector *v, size_t index);
void vector_push(vector *v, const void *p, size_t size);
void vector_pop(vector *v);
void vector_resize(vector *v, size_t size, size_t count);

// Element Access
void* vector_element_at(const vector *v, size_t index);
void* vector_front(const vector *v);
void* vector_back(const vector *v);

// Capacity
int vector_empty(const vector *v);
size_t vector_size(const vector *v);
size_t vector_capacity(const vector *v);

// Memory Management
void vector_reserve(vector *v, size_t size);
void vector_shrink(vector *v);
void vector_free(vector *v);

#endif // VECTOR_H