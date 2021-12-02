#include "../include/vector.h"

#define VECTOR_BLOCK_SIZE 0x10

vector vector_create(size_t sov, size_t soe) {
    vector v;
    v.size = sov < VECTOR_BLOCK_SIZE ? VECTOR_BLOCK_SIZE : sov;
    v.index = 0;
    v.container = malloc(sizeof(void*) * v.size);

    if (v.container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    vector_resize(&v, soe, sov);
 
    return v;
}

void vector_clear(vector *v) {
    for (size_t i = 0; i < v->index; i++) {
        if (v->container[i] != NULL) free(v->container[i]);
    }
    v->index = 0;

    return;
}

void vector_insert(vector *v, const void *p, size_t size, size_t index) {

    if (index > v->index) {
        fprintf(stderr, "Out of bound!\n");
        exit(EXIT_FAILURE);
    }

    if (v->index >= v->size) {
        vector_reserve(v, v->size + VECTOR_BLOCK_SIZE);
        v->index++;
    }

    memmove(v->container + index + 1, v->container + index, (v->index - index) * sizeof(void*));

    v->container[index] = malloc(size);

    if (v->container[index] == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v->container[index], p, size);

    return;
}

void vector_erase(vector *v, size_t index) {

    if (index >= v->index) return;

    free(v->container[index]);

    memmove(v->container + index - 1, v->container + index, sizeof(void*) * (v->index - index));

    v->index--;

    return;
}

void vector_push(vector *v, const void *p, size_t size) {

    if (v->index >= v->size) vector_reserve(v, v->size + VECTOR_BLOCK_SIZE);

    v->container[v->index] = malloc(size);

    if (v->container[v->index] == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    memcpy(v->container[v->index++], p, size);

    return;
}

void vector_pop(vector *v) {

    if (v->index == 0) return;

    v->index--;

    free(v->container[v->index]);

    v->container[v->index] = NULL;

    return;
}

void vector_resize(vector *v, size_t size, size_t count) {
    
    if (count < v->index) {
        for (size_t i = v->index - 1; i >= count; i--) {
            if (v->container != NULL) free(v->container[i]);
        }

    } else {
        if (count >= v->size) {
            vector_reserve(v, count + 1);
        }

        for (size_t i = v->index; i < count; i++) {
            v->container[i] = calloc(size, 1);

            if (v->container[i] == NULL) {
                fprintf(stderr, "Memory allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    v->index = count;

    return;
}

void* vector_element_at(const vector *v, size_t index) {
    if (index >= v->index) {
        fprintf(stderr, "Out of bound!\n");
        exit(EXIT_FAILURE);
    }

    if (v->container[index] == NULL) {
        fprintf(stderr, "Invalid memory access!\n");
        exit(EXIT_FAILURE);
    }

    return v->container[index];
}

void* vector_front(const vector *v) {
    if (v->container[0] == NULL) {
        fprintf(stderr, "Invalid memory access!\n");
        exit(EXIT_FAILURE);
    }

    return v->container[0];
}

void* vector_back(const vector *v) {
    if (v->container[v->index - 1] == NULL) {
        fprintf(stderr, "Invalid memory access!\n");
        exit(EXIT_FAILURE);
    }

    return v->container[v->index - 1];
}

int vector_empty(const vector *v) {
    return v->index == 0;
}

size_t vector_size(const vector *v) {
    return v->index;
}

size_t vector_capacity(const vector *v) {
    return v->size;
}

void vector_reserve(vector *v, size_t size) {
    if (v->size >= size) return;

    v->container = realloc(v->container, sizeof(void*) * size);
    v->size = size;

    if (v->container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    return;
}

void vector_shrink(vector *v) {
    v->container = realloc(v->container, sizeof(void*) * v->index);

    if (v->container == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    v->size = v->index;

    return;
}

void vector_free(vector *v) {
    for (size_t i = 0; i < v->index; i++) {
        if (v->container[i] != NULL) free(v->container[i]);
    }

    free(v->container);

    return;
}