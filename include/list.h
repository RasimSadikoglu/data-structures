#ifndef LIST_H
#define LIST_H

typedef struct list list;

typedef struct iterator {
    void *node;
    struct iterator *next;
    int location;
} iterator;

enum container_operations {
    CONTAINER_CREATE,
    CONTAINER_ADD,
    CONTAINER_GET,
    CONTAINER_REMOVE,
    CONTAINER_FREE,
    CONTAINER_ITERATOR
};

enum node_operations {
    NODE_NODE_COMPARE,
    NODE_KEY_COMPARE,
    NODE_FREE
};

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