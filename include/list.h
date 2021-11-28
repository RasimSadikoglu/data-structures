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

/**
 * @param list_type 
 * List type is a handler function for container 
 * @param node_node_compare 
 * Compare function for 2 nodes, return the difference [arg1 - arg2].
 * @param node_key_compare
 * Compare function for node and a key for that node, return the difference [arg1 - arg2].
 * @param node_free
 * Memory free function for nodes, NULL for no implicit free, all nodes has to be freed 
 * before termination.
 * @return list*
 */
list* list_create(void *list_type, int (*node_node_compare)(const void*, const void*), int (*node_key_compare)(const void*, const void*), void (*node_free)(void*));

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