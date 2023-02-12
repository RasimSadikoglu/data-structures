#include "node.h"

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

node* node_create(char *file_name, int key) {
    
    node *n = malloc(sizeof(node));

    strncpy(n->file_name, file_name, CHAR_LENGTH - 1);
    n->file_name[CHAR_LENGTH - 1] = '\0';
    n->key = key;

    return n;
}

int is_word_boundry(char c) {
    return !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int number_of_occurences(char *file_content, char *keyword) {

    size_t keyword_length = strlen(keyword), file_length = strlen(file_content);

    if (keyword_length > file_length) return 0;

    int occurence_count = 0;

    occurence_count += strncmp(file_content, keyword, keyword_length) == 0 && is_word_boundry(file_content[keyword_length]);

    size_t i; for (i = 1; i < file_length - keyword_length; i++) {
        occurence_count += strncmp(file_content + i, keyword, keyword_length) == 0 && 
            is_word_boundry(file_content[i - 1]) && is_word_boundry(file_content[i + keyword_length]);
    }

    occurence_count += strncmp(file_content + i, keyword, keyword_length) == 0 && is_word_boundry(file_content[i - 1]);
    
    return occurence_count;
}

node* read_file(char *file_name, char *keyword) {

    FILE *input_file = fopen(file_name, "r");

    if (input_file == NULL) {
        fprintf(stderr, "No file exists. (%s)\n", file_name);
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    rewind(input_file);

    char *file_content = malloc((unsigned long)file_size + 1);
    fread(file_content, sizeof(char), (unsigned long)file_size, input_file);
    file_content[file_size] = '\0';

    node *n = node_create(file_name, number_of_occurences(file_content, keyword));

    fclose(input_file);
    free(file_content);

    return n;
}

node** node_read_files(char *directory_path, char *keyword) {

    struct dirent *file_info;

    DIR *directory = opendir(directory_path);

    char **file_names = calloc(sizeof(char*), 1);
    int current_index = 0;

    while ((file_info = readdir(directory))) {
        if (file_info->d_type == DT_REG) { 
            file_names[current_index] = malloc(sizeof(char) * CHAR_LENGTH);
            
            strcpy(file_names[current_index], directory_path);
            strncat(file_names[current_index], file_info->d_name, CHAR_LENGTH - strlen(directory_path) - 1);
            file_names[current_index++][CHAR_LENGTH - 1] = '\0';

            file_names = realloc(file_names, sizeof(char*) * (size_t)(current_index + 1));
            file_names[current_index] = NULL;
        }
    }

    closedir(directory);
    
    node **nodes = calloc(sizeof(node*), 1);
    current_index = 0;

    for (char **file_name = file_names; *file_name != NULL; file_name++) {

        nodes[current_index++] = read_file(*file_name, keyword);
        
        nodes = realloc(nodes, sizeof(node*) * (size_t)(current_index + 1));
        nodes[current_index] = NULL;

        free(*file_name);
    }

    free(file_names);

    return nodes;
}