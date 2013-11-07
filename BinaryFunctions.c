#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"	


void rec_add(BinaryNode **n, BinaryNode * parent, char *word, size_t lineNum, size_t lineLength, size_t wordNum) {
	BinaryNode *node = *n;

	if(!node) {
		node = malloc(sizeof(BinaryNode));

        //char buf[128];

        node->key = malloc(sizeof(char)*128);
        strncpy(node->key, word, 128);
		node->left = node->right = NULL;
		node->lineNum = lineNum;
		node->wordNum = wordNum;
		node->lineLength = lineLength;
        node->parent = parent;

        *n = node;
    }

		if (strncmp(word, node->key,100) > 0) {
            rec_add(&node->right, node, word, lineNum, lineLength, wordNum);
		} else if(strncmp(word, node->key,100) < 0) {
            rec_add(&node->left, node, word, lineNum, lineLength, wordNum);
		}


}

BinaryNode * rec_search(BinaryNode **n, char *word) {
	BinaryNode *node = *n;


    if(!node) {
		return NULL;
	}

	int r = strncmp(word, node->key,100);

    if (r > 0) {
        return rec_search(&node->right, word);
    } else if(r < 0) {
        return rec_search(&node->left, word);
	}
	
	printf("Did find word\n");
	return node;
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
