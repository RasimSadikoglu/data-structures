#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/binary_search_tree.h"
#include "node.h"

#define CHAR_LENGTH 50

int alpha_node_node_compare(const void *n1, const void *n2) { return strcasecmp(((node*)n1)->key, ((node*)n2)->key); }
int alpha_node_key_compare(const void *n, const void *key) { return strcasecmp(((node*)n)->key, key); }

int freq_node_node_compare(const void *n1, const void *n2) { return (*((node**)n2))->freq - (*((node**)n1))->freq; }

list* get_alpha_tree(node **nodes);

int get_alpha_access_time(list *l);
int get_freq_access_time(node **nodes);

void print_tree(list *l);

int main(int argc, char **argv) {

    if (argc != 2) {
        perror("Usage: .exe <file_path>");
        exit(EXIT_FAILURE);
    }

    node **nodes = node_read_file(argv[1]);

    list *alpha_tree = get_alpha_tree(nodes);
    
    int size = 0; for (node **n = nodes; *n != NULL; n++, size++); 

    qsort(nodes, size, sizeof(node*), freq_node_node_compare);

    printf("a) LEFT - NODE - RIGHT\n");
	print_tree(alpha_tree);
	printf("\nb) Total Access Time: Binary Search Tree - Nodes are added in order by their file order. -> %d\n", get_alpha_access_time(alpha_tree));
	printf("\nc) Level Ordered Traversal\n");
	for (node **n = nodes; *n != NULL; n++) { printf("%d - %s\n", (*n)->freq, (*n)->key); }
	printf("\nd) Total Access Times:\nAnswer: Binary Tree - Nodes are ordered by their frequencies. (Biggest to Smallest) -> %d\n", get_freq_access_time(nodes));

    /* Free Memory */
    list_free(alpha_tree);

    for (node **n = nodes; *n != NULL; n++) {
        free(*n);
    }

    free(nodes);
    /* Free Memory */

    return 0;
}

list* get_alpha_tree(node **nodes) {

    list *alpha_tree = list_create(BINARY_SEARCH_TREE, alpha_node_node_compare, alpha_node_key_compare, NULL);

    for (node **n = nodes; *n != NULL; n++) {
        list_add(alpha_tree, *n);
    }

    return alpha_tree;
}

int get_alpha_access_time(list *l) {

    int access_time = 0;

    iterator *it = list_iterator(l);

    for (iterator *i = it; i->node != NULL; i = i->next) {
        access_time += i->location * ((node*)i->node)->freq;
    }

    free(it);

    return access_time;
}

int ilog2(int num) { return num == 0 ? -1 : ilog2(num >> 1) + 1; }

int get_freq_access_time(node **nodes) {
    
    int access_time = 0;

    int level = 1;
    for (node **n = nodes; *n != NULL; n++, level++) {
        access_time += (*n)->freq * (ilog2(level) + 1);
    }

    return access_time;
}

void print_tree(list *l) {

    iterator *it = list_iterator(l);

    for (iterator *i = it; i->node != NULL; i = i->next) {
        node *n = i->node;

        printf("%d - %s\n", n->freq, n->key);
    }

    iterator_free(it);

}