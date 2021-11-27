#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/binary_tree.h"

#define CHAR_LENGTH 50

char* parse_input(char **line) {

    char *start = *line;
    
    int i;
    for (i = 0; start[i] != ',' && start[i] != '\0' && start[i] != '\n'; i++);
    start[i] = '\0';

    *line = *line + i + 1;

    return start;
}

typedef struct {
    char key[CHAR_LENGTH];
    int freq;
    int index;
} node;

node* node_create(int index, char *key, int freq) {
    node *n = malloc(sizeof(node));

    strncpy(n->key, key, CHAR_LENGTH);
    n->freq = freq;
    n->index = index;

    return n;
}

node** node_read_file(char *file_path) {

    size_t current_index = 0;

    node** nodes = malloc(sizeof(node*));
    nodes[current_index] = NULL;

    FILE *input_file = fopen(file_path, "r");

    char *buffer_memory = malloc(CHAR_LENGTH);
    while (fgets(buffer_memory, CHAR_LENGTH, input_file) != NULL) {
        char *buffer = buffer_memory;
        
        int index = atoi(parse_input(&buffer));
        char *key = parse_input(&buffer);
        int freq = atoi(parse_input(&buffer));

        nodes[current_index++] = node_create(index, key, freq);

        nodes = realloc(nodes, sizeof(node*) * (current_index + 1));
        nodes[current_index] = NULL;
    }
    free(buffer_memory);

    fclose(input_file);

    return nodes;

}

void free_nodes(node **nodes) {

    for (node **n = nodes; *n != NULL; n++) {
        free(*n);
    }

    free(nodes);

}

int alpha_compare(void *n1, void *n2) { return strcmp(((node*)n1)->key, ((node*)n2)->key); }
int alpha_find(void *n, void *key) { return strcmp(((node*)n)->key, key); }
void f_print(void *n) { printf("%s - %d\n", ((node*)n)->key, ((node*)n)->freq); }

tree* get_alpha_tree(node **nodes);

int main(int argc, char **argv) {

    if (argc != 2) {
        perror("Usage: .exe <file_path>");
        exit(EXIT_FAILURE);
    }

    node** nodes = node_read_file(argv[1]);

    tree *alpha_tree = get_alpha_tree(nodes);

    iterator *it = tree_iterator(alpha_tree);

    for (iterator *i = it; i->node != NULL; i = i->next) {
        node *n = i->node;

        printf("%d - %s\n", n->freq, n->key);
    }

    iterator_free(it);

    tree_free(alpha_tree, NULL);

    free_nodes(nodes);

}

tree* get_alpha_tree(node **nodes) {

    tree *alpha_tree = tree_create(alpha_compare, alpha_find, BINARY_TREE);

    for (node **n = nodes; *n != NULL; n++) {
        tree_add(alpha_tree, *n);
    }

    return alpha_tree;
}