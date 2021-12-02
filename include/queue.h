#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    void **container;
    size_t size;
    size_t head;
    size_t tail;
} queue;

queue queue_create();

// Modifiers
void queue_push(queue *q, const void *p, size_t size);
void queue_pop(queue *q);

// Element Access
void* queue_front(const queue *q);
void* queue_back(const queue *q);

// Capacity
int queue_empty(const queue *q);
size_t queue_size(const queue *q);

// Memory Management
void queue_free(queue *q);

#endif // QUEUE_H