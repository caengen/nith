#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"	

void rec_add(BinaryNode **n, char *word, size_t lineNum, size_t lineLength, size_t wordNum) {
	BinaryNode *node = *n;

	if(node == NULL) {
		node = malloc(sizeof(BinaryNode));
		node->key = word;
		node->left = node->right = NULL;
		node->lineNum = lineNum;
		node->wordNum = wordNum;
		node->lineLength = lineLength;

		*n = node;
		printf("Laget en node!\n");
	} else {
		if (strcmp(word, node->key) > 0) {
			rec_add(&node->right, word, lineNum, lineLength, wordNum);
		} else {
			rec_add(&node->left, word, lineNum, lineLength, wordNum);
		}
	}
}

bool rec_search(BinaryNode **n, char *word) {
	BinaryNode *node = *n;
	bool found = false;

	if(node == NULL) {
		return false;
	} else {
		int r = strcmp(word, node->key);
		printf("comparing %s and %s\n", word, node->key);
		if (r == 0) {
			return true;
		} else if (r > 0) {
			found = found | rec_search(&node->right, word);
		} else {
			found = found | rec_search(&node->left, word);
		}
	}

	return found;
}

bool bf_delete(BinaryTree *tree, BinaryNode *other) {
	return false;
}

void printTree(BinaryNode **n) {
	BinaryNode *node = *n;

	if (node == NULL) {
		return;
	} else {
		printf("%s : %zu", node->key, node->lineNum);
		printTree(&node->right);
	}
}