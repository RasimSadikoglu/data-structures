#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/binomial_heap.h"
#include "node.h"

int main() {

    char keyword[CHAR_LENGTH];
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    
    node **nodes = node_read_files("files/", keyword);


    /* Free Memory */
    for (node **n = nodes; *n != NULL; n++) free(*n);
    free(nodes);
    /* Free Memory */

    return 0;
}