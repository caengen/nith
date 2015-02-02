#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryTreeFunctions.h"	
/* @author 		Cengen
 * @last edit	08/11/2013
 */


/* Recursive add function for a BinaryNode and its children
 * Function parameters are a double pointer to a node and the data needed to complete
 * a BinaryNode
 *
 * If the double pointer is NULL, we insert our data to that node
 * if it is not NULL we continue searching through its children, left and right
 */
void add(BinaryNode **n, BinaryNode * parent, char *val, size_t lineNum, size_t lineLength, size_t wordNum) {
	BinaryNode *node = *n;

	if(!node) {
		node = malloc(sizeof(BinaryNode));
		node->val = malloc(sizeof(char)*128);
		strncpy(node->val, val, 128);
		node->left = node->right = NULL;
		node->lineNum = lineNum;
		node->wordNum = wordNum;
		node->lineLength = lineLength;
		node->parent = parent;

		*n = node;
	}
	
	if ( strncasecmp(val, node->val,100) > 0) {
		add(&node->right, node, val, lineNum, lineLength, wordNum);
	} else if( strncasecmp(val, node->val,100) < 0) {
		add(&node->left, node, val, lineNum, lineLength, wordNum);
	}
}

/* Recursive search function for a BinaryNode and its children
 * Has two parameters, a double pointer to a BinaryNode and a char pointer to the word
 * to search for.
 * 
 * We compare the struct BinaryNode's val to our word.
 * strncmp returns either a negative, a positive or a zero in cases of the 
 * first argument being less than, more than or equal to the second argument.
 * If the first argument is less than, we return the search result of the left node
 * and opposite if it is more than.
 *
 */
BinaryNode * search(BinaryNode **n, char *word) {
	BinaryNode *node = *n;


	if(!node) {
		return NULL;
	}

	int r =  strncasecmp(word, node->val,100);

	if (r > 0) {
		return search(&node->right, word);
	} else if(r < 0) {
		return search(&node->left, word);
	}
	
	printf("Word found, printing data:\n");
	return node;
}

bool delete(BinaryTree *tree, BinaryNode *other) {
	return false;
}

/* Recursive function for freeing the pointers in our binary tree.
 *
 */
void freeTree(BinaryNode *node) {

	if (!node) { return; }

	if (node->left)  freeTree(node->left);
	if (node->right) freeTree(node->right);

	free(node->val);
	free(node);
}
