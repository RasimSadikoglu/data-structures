#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 50

typedef struct node Node;
typedef Node* NodePtr;

struct node {
	char key[SIZE];
	int freq;
	NodePtr left;
	NodePtr right;
};

int counter;

void initAlphabeticalOrder(NodePtr *root, FILE *cfPtr);
void initFrequencyOrder(NodePtr *root, FILE *cfPtr);

void initBinaryTree(NodePtr *root, int index, NodePtr *nodes);
void initOptimizedOrder(NodePtr *root, NodePtr *nodes);
void initOptimizedOrder2(NodePtr *root, int start, int end, NodePtr *nodes);

NodePtr createNode(char *line);
void addNode(NodePtr *root, NodePtr node);
void addArray(NodePtr root, int *index, NodePtr *nodes);

int totalAccessTime(NodePtr root, int depth);

void LNR(NodePtr root);
void NLR(NodePtr root);
void levelOrderedTraversal(NodePtr root);

int strcmpncs(char *word1, char *word2);

void free_tree(Node *root);

int main() {

	counter = 0;

	FILE *cfPtr = fopen("input.txt", "r");
	if (cfPtr == NULL) {
		printf("File not found ?!");
		return -1;
	}

	NodePtr node_alphabetical_root = NULL;
	NodePtr node_freq_order_root = NULL;

	initAlphabeticalOrder(&node_alphabetical_root, cfPtr);
	initFrequencyOrder(&node_freq_order_root, cfPtr);

	fclose(cfPtr);

	NodePtr node_bt_root = NULL;
	NodePtr node_optimized_root = NULL;
	NodePtr node_optimized2_root = NULL;

	NodePtr nodes_freq[counter];
	int index = 0;
	addArray(node_freq_order_root, &index, nodes_freq);
	initBinaryTree(&node_bt_root, 1, nodes_freq);

	initOptimizedOrder(&node_optimized_root, nodes_freq);

	NodePtr nodes_alphabetical[counter];
	index = 0;
	addArray(node_alphabetical_root, &index, nodes_alphabetical);
	initOptimizedOrder2(&node_optimized2_root, 1, counter, nodes_alphabetical);

	int tat_for_b = totalAccessTime(node_alphabetical_root, 1); 
	int tat_for_d = totalAccessTime(node_bt_root, 1); 
	int tat_for_do1 = totalAccessTime(node_optimized_root, 1); 
	int tat_for_do2 = totalAccessTime(node_optimized2_root, 1);

	printf("a) LEFT - NODE - RIGHT\n");
	LNR(node_alphabetical_root);
	printf("\nb) Total Access Time: Binary Search Tree - Nodes are added in the order that in file. -> %d\n", tat_for_b);
	printf("\nc) Level Ordered Traversal\n");
	levelOrderedTraversal(node_bt_root);
	printf("\nd) Total Access Times:\nAnswer: Binary Tree - Nodes are ordered by their frequencies. (Biggest to Smallest) -> %d\n", tat_for_d);
	printf("\nAdditional Answer 1: Binary Search Tree - Nodes are added in the order that \nthe node that has highest frequency added first. -> %d\n", tat_for_do1);
	printf("\nAdditional Answer 2: Balanced Binary Tree (AVL Tree) - Tree is set to be that \nits heigth is going to be minimal. -> %d\n", tat_for_do2);

	free_tree(node_alphabetical_root);
	free_tree(node_freq_order_root);
	free_tree(node_bt_root);
	free_tree(node_optimized_root);
	free_tree(node_optimized2_root);
}

void initAlphabeticalOrder(NodePtr *root, FILE *cfPtr) {
	rewind(cfPtr);

	while (!feof(cfPtr)) {
		char line[100];
		fgets(line, 100, cfPtr);
		if (strchr(line, ',') == NULL) continue;

		counter++;
		NodePtr new_node = createNode(line);
		if (new_node != NULL) addNode(root, new_node);

		free(new_node);
	}
}

void initFrequencyOrder(NodePtr *root, FILE *cfPtr) {
	rewind(cfPtr);

	while (!feof(cfPtr)) {
		char line[100];
		fgets(line, 100, cfPtr);
		if (strchr(line, ',') == NULL) continue;

		NodePtr new_node = createNode(line);
		if (new_node == NULL) return;

		if (*root == NULL) {
			*root = new_node;
		} else {
			NodePtr current_node = *root;
			while (current_node != NULL) {
				if (new_node->freq > current_node->freq) {
					if (current_node->left == NULL) {
						current_node->left = new_node;
						break;
					} else {
						current_node = current_node->left;
					}
				} else {
					if (current_node->right == NULL) {
						current_node->right = new_node;
						break;
					} else {
						current_node = current_node->right;
					}
				}
			}
		}
	}
}

void initBinaryTree(NodePtr *root, int index, NodePtr *nodes) {
	if (*root == NULL) {
		*root = nodes[index - 1];
		initBinaryTree(root, index, nodes);
	} else {
		index *= 2;
		if (index > counter) return;
		(*root)->left = nodes[index - 1];
		initBinaryTree(&((*root)->left), index, nodes);
		if (++index > counter) return;
		(*root)->right = nodes[index - 1];
		initBinaryTree(&((*root)->right), index, nodes);
	}
}

void initOptimizedOrder(NodePtr *root, NodePtr *nodes) {
	int i; for (i = 0; i < counter; i++) {
		addNode(root, nodes[i]);
	}
}

void initOptimizedOrder2(NodePtr *root, int start, int end, NodePtr *nodes) {
	if (start > end) return;

	if (start == end) {
		if (strcmpncs(nodes[start - 1]->key, (*root)->key) < 0) {
			(*root)->left = nodes[start - 1];
		} else {
			(*root)->right = nodes[start - 1];
		}
		return;
	}

	int o = start + end;

	if (o % 2 == 0) {
		o = (start + end) / 2;
	} else {
		o = (start + end) / 2;
		o = (nodes[o - 1]->freq > nodes[o]->freq) ? o : o + 1;
	}

	if (*root == NULL) {
		*root = nodes[o - 1];
		initOptimizedOrder2(root, start, o - 1, nodes);
		initOptimizedOrder2(root, o + 1, end, nodes);
	} else if (strcmpncs(nodes[o - 1]->key, (*root)->key) < 0) {
		(*root)->left = nodes[o - 1];
		initOptimizedOrder2(&((*root)->left), start, o - 1, nodes);
		initOptimizedOrder2(&((*root)->left), o + 1, end, nodes);
	} else {
		(*root)->right = nodes[o - 1];
		initOptimizedOrder2(&((*root)->right), start, o - 1, nodes);
		initOptimizedOrder2(&((*root)->right), o + 1, end, nodes);
	}
}

NodePtr createNode(char *line) {
	char *token = strtok(line, ",");
	int index = atoi(token);
	token = strtok(NULL, ",");
	char word[SIZE];
	strcpy(word, token);
	token = strtok(NULL, "\n");
	int freq = atoi(token);

	NodePtr node = malloc(sizeof(Node));
	if (node == NULL) return NULL;

	strcpy(node->key, word);
	node->freq = freq;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void addNode(NodePtr *root, NodePtr node) {
	NodePtr new_node = malloc(sizeof(Node));
	if (new_node == NULL) return;

	strcpy(new_node->key, node->key);
	new_node->freq = node->freq;
	new_node->left = NULL;
	new_node->right = NULL;

	if (*root == NULL) {
		*root = new_node;
	} else {
		NodePtr current_node = *root;
		while (current_node != NULL) {
			if (strcmpncs(new_node->key, current_node->key) < 0) {
				if (current_node->left == NULL) {
					current_node->left = new_node;
					return;
				} else {
					current_node = current_node->left;
				}
			} else {
				if (current_node->right == NULL) {
					current_node->right = new_node;
					return;
				} else {
					current_node = current_node->right;
				}
			}
		}
	}
}

void addArray(NodePtr root, int *index, NodePtr *nodes) {
	if (root->left != NULL) addArray(root->left, index, nodes);

	NodePtr new_node = malloc(sizeof(Node));
	if (new_node == NULL) return;

	strcpy(new_node->key, root->key);
	new_node->freq = root->freq;
	new_node->left = NULL;
	new_node->right = NULL;

	nodes[(*index)++] = new_node;

	if (root->right != NULL) addArray(root->right, index, nodes);
}

int totalAccessTime(NodePtr root, int depth) {
	static int tat = 0;
	if (depth == 1) tat = 0;
	if (root == NULL) return tat;

	tat += root->freq * depth;

	totalAccessTime(root->left, depth + 1);
	totalAccessTime(root->right, depth + 1);
}

void LNR(NodePtr root) {
	if (root->left != NULL) LNR(root->left);
	printf("Key: %s\t-\tFrequency: %d\n", root->key, root->freq);
	if (root->right != NULL) LNR(root->right);
}

void NLR(NodePtr root) {
	printf("Key: %s\t-\tFrequency: %d\n", root->key, root->freq);
	if (root->left != NULL) LNR(root->left);
	if (root->right != NULL) LNR(root->right);
}

void levelOrderedTraversal(NodePtr root) {
	printf("Key: %s\t-\tFrequency: %d\n", root->key, root->freq);

	int level = 2;
	int i; for (i = 2; 1; i++) {
		if (i == level * 2) level *= 2;
		NodePtr current_node = root;
		int j; for (j = level / 2; j != 0; j /= 2) {
			current_node = !(i & j)	? current_node->left : current_node->right;
			if (current_node == NULL) return;
		}
		printf("Key: %s\t-\tFrequency: %d\n", current_node->key, current_node->freq);
	}
}

int strcmpncs(char *word1, char *word2) {
	char w1[SIZE], w2[SIZE];
	strncpy(w1, word1, SIZE);
	strncpy(w2, word2, SIZE);
	int i; for (i = 0; i < SIZE; i++) {
		w1[i] = tolower(w1[i]);
		w2[i] = tolower(w2[i]);
	}
	return strcmp(w1, w2);
}

void free_tree(Node *root) {

	if (root->left != NULL) free_tree(root->left);

	if (root->right != NULL) free_tree(root->right);

	free(root);

	return;
}