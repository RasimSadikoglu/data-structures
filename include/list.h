#ifndef LIST_H
#define LIST_H

typedef struct list list;

typedef struct iterator {
    void *node;
    struct iterator *next;
    int location;
} iterator;

// Container Operations
#define CONTAINER_CREATE 0
#define CONTAINER_ADD 1
#define CONTAINER_GET 2
#define CONTAINER_REMOVE 3
#define CONTAINER_FREE 4
#define CONTAINER_ITERATOR 5

// Node Operations
#define NODE_NODE_COMPARE 0
#define NODE_KEY_COMPARE 1
#define NODE_FREE 2

/**
 * @param list_type 
 * List type is a handler function for container 
 * @param node_handler
 * Node handler function has to implement all node operations.
 * @return list*
 */
list* list_create(void *list_type, int (*node_handler)(const void*, const void*, int op));

/**
 * @param t
 * @param node 
 * @return 0 for success, non-zero for failure. (Not implemented fully!)
 */
int list_add(list *t, void *node);

/**
 * @param t 
 * @param key 
 * @return Memory address for requested node, if there is no matched node, return value
 * will be NULL.
 */
void* list_get(list *t, void *key);

/**
 * @param t 
 * @param key 
 * @return 0 for success, non-zero for failure. (Not implemented fully!)
 * Node will be freed if node_free function is specified. 
 */
int list_remove(list *t, void *key);

/**
 * @param t 
 * @return Iterator struct for list elements.
 * For sorted list the elements will be in lexicographic order. 
 */
iterator* list_iterator(list *t);
void iterator_free(iterator *it);

void list_free(list *t);

#endif // LIST_H