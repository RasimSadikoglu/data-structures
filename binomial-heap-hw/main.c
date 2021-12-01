#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/binomial_heap.h"
#include "node.h"

#define MAX_RESULTS 5

int node_handler(const void *p1, const void *p2, int op) {

    switch (op) {

        case NODE_NODE_COMPARE:
            return ((node*)p2)->key - ((node*)p1)->key;
        default:
            return 0;
    }

}

int main() {

    char keyword[CHAR_LENGTH];
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    
    node **nodes = node_read_files("files/", keyword);

    list *binomial_heap = list_create(BINOMIAL_HEAP, node_handler);

    for (node **n = nodes; *n != NULL; n++) {
        list_add(binomial_heap, *n);
    }

    for (int i = 0; i < MAX_RESULTS; i++) {

        node *n = list_get(binomial_heap, NULL);

        if (n == NULL) break;

        printf("%d. %d number of occurences found in %s.\n", i + 1, n->key, n->file_name);

        list_remove(binomial_heap, NULL);
    }

    /* Free Memory */
    list_free(binomial_heap);

    for (node **n = nodes; *n != NULL; n++) free(*n);
    free(nodes);
    /* Free Memory */

    return 0;
}