#include "../include/queue.h"

#define QUEUE_BLOCK_SIZE 0x10

queue queue_create() {
    queue q;
    q.size = QUEUE_BLOCK_SIZE;
    q.container = malloc(sizeof(void*) * q.size);
    q.head = 0;
    q.tail = 0;

    if (q.container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    return q;
}

void queue_push(queue *q, const void *p, size_t size) {
    if (q->head == (q->tail + 1) % q->size) {
        void **container = malloc(sizeof(void*) * (q->size + QUEUE_BLOCK_SIZE));

        if (container == NULL) {
            fprintf(stderr, "Memory allocation error!\n");
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < q->size; i++) {
            container[i] = q->container[(i + q->head) % q->size];
        }

        free(q->container);
        q->container = container;

        q->head = 0;
        q->tail = q->size - 1;

        q->size += QUEUE_BLOCK_SIZE;
    }

    q->container[q->tail] = malloc(size);

    if (q->container[q->tail] == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(q->container[q->tail++], p, size);
    q->tail %= q->size;

    return;
}

void queue_pop(queue *q) {

    if (q->head == q->tail) return;

    free(q->container[q->head]);

    q->container[q->head++] = NULL;

    q->head %= q->size;

    return;
}

void* queue_front(const queue *q) {
    if (q->head == q->tail) {
        fprintf(stderr, "Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    if (q->container[q->head] == NULL) {
        fprintf(stderr, "Invalid memory access!\n");
        exit(EXIT_FAILURE);
    }

    return q->container[q->head];
}

void* queue_back(const queue *q) {
    if (q->head == q->tail) {
        fprintf(stderr, "Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    if (q->container[(q->tail + q->size - 1) % q->size] == NULL) {
        fprintf(stderr, "Invalid memory access!\n");
        exit(EXIT_FAILURE);
    }

    return q->container[(q->tail + q->size - 1) % q->size];
}

int queue_empty(const queue *q) {
    return q->head == q->tail;
}

size_t queue_size(const queue *q) {
    return (q->size + q->tail - q->head) % q->size + 1;
}

void queue_free(queue *q) {
    for (size_t i = 0; i < q->size; i++) {
        if (q->container[i] != NULL) {
            free(q->container[i]);
        }
    }

    free(q->container);

    return;
}