#ifndef NODE_H
#define NODE_H

#define CHAR_LENGTH 100

typedef struct {
    char file_name[CHAR_LENGTH];
    int key;
} node;

node* node_create(char *file_name, int key);
node** node_read_files(char *directory_path, char *keyword);

#endif // NODE_H