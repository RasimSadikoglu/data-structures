#ifndef NODE_H
#define NODE_H

#define CHAR_LENGTH 50

typedef struct {
    char key[CHAR_LENGTH];
    int freq;
    int index;
} node;

node* node_create(int index, char *key, int freq);
node** node_read_file(char *file_path);

#endif // NODE_H