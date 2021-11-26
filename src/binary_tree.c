#include "../include/binary_tree.h"

typedef struct bt_container {
    void *root;
    struct bt_container *left;
    struct bt_container *right;
} bt_container;

bt_container* bt_container_create();
int bt_container_add_node(bt_container *container, void *node, int (*compare)(void*, void*));
void bt_container_free(bt_container *container, void (*node_free)(void*));

struct binary_tree {
    bt_container *container;
    size_t number_of_elements;
    size_t depth;
    int (*compare)(void*, void*);
};

binary_tree* binary_tree_create(int (*compare)(void*, void*)) {

    binary_tree *bt = calloc(sizeof(binary_tree), 1);

    bt->container = bt_container_create();

    bt->compare = compare;

    return bt;
}

int binary_tree_add_node(binary_tree *bt, void *node) {
    if (node == NULL) return 1;

    return bt_container_add_node(bt->container, node, bt->compare);
}

void binary_tree_free(binary_tree* bt, void (*node_free)(void*)) {

    bt_container_free(bt->container, node_free);
    free(bt);

}

bt_container* bt_container_create() {
    return calloc(sizeof(bt_container), 1);
}

int bt_container_add_node(bt_container *container, void *node, int (*compare)(void*, void*)) {

    if (container->root == NULL) {
        container->root = node;
        return 0;
    }

    if (compare(container->root, node) > 0) {
        if (container->left == NULL) container->left = bt_container_create();
        return bt_container_add_node(container->left, node, compare);
    } else {
        if (container->right == NULL) container->right = bt_container_create();
        return bt_container_add_node(container->right, node, compare);
    }

}

void bt_container_free(bt_container *container, void (*node_free)(void*)) {

    node_free(container->root);

    if (container->left != NULL) bt_container_free(container->left, node_free);
    if (container->right != NULL) bt_container_free(container->right, node_free);

    free(container);

}