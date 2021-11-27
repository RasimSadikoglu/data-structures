#ifndef LIST_H
#define LIST_H

typedef struct list list;

typedef struct iterator {
    void *node;
    struct iterator *next;
} iterator;

// Container Operations
#define CONTAINER_CREATE 0
#define CONTAINER_ADD 1
#define CONTAINER_GET 2
#define CONTAINER_REMOVE 3
#define CONTAINER_FREE 4
#define CONTAINER_ITERATOR 5

list* list_create(int (*node_compare)(void*, void*), int (*node_find)(void*, void*), void *list_type);

int list_add(list *t, void *node);
void* list_get(list *t, void *key);
int list_remove(list *t, void *key);

iterator* list_iterator(list *t);
void iterator_free(iterator *it);

void list_free(list *t, void (*node_free)(void*));

#endif // LIST_H