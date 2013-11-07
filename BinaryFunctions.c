#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"	

void rec_add(BinaryNode **n, char *word, size_t lineNum, size_t lineLength, size_t wordNum) {
	BinaryNode *node = *n;

	if(!node) {
		node = malloc(sizeof(BinaryNode));
		node->key = word;
		node->left = node->right = NULL;
		node->lineNum = lineNum;
		node->wordNum = wordNum;
		node->lineLength = lineLength;

		*n = node;
		printf("Laget en node for %s!\n\n", word);
	} else {
		if (strcmp(word, node->key) > 0) {
			rec_add(&node->right, word, lineNum, lineLength, wordNum);
		} else if(strcmp(word, node->key) < 0) {
			rec_add(&node->left, word, lineNum, lineLength, wordNum);
		}
	}
}

BinaryNode * rec_search(BinaryNode **n, char *word) {
	BinaryNode *node = *n;

	if(!node) {
		return NULL;
	} else {
		int r = strcmp(word, node->key);
		/*DEBUG*/printf("comparing %s and %s\n", word, node->key);

		if (r == 0) {
			return node;
		} else if (r > 0) {
			//printf("Going right\n");
			rec_search(&node->right, word);
		} else {
			//printf("Going left\n");
			rec_search(&node->left, word);
		}
	}
	
	return NULL;
}

bool bf_delete(BinaryTree *tree, BinaryNode *other) {
	return false;
}

void printTree(BinaryNode **n) {
	BinaryNode *node = *n;

	if (node == NULL) {
		return;
	} else {
		printf("%s : %zu\n", node->key, node->lineNum);
		printTree(&node->right);
	}
}