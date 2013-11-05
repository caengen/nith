#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"	

bool bf_insert(BinaryTree *tree, BinaryNode *other) {
	bool success = false, stepRight, stepLeft;
	BinaryNode *node = tree->node, *ahead;
	int cmpres, cmpresA;

	while (true) {
		stepRight = false, stepLeft = false;
		cmpres = 0, cmpresA = 0;

		//return less than, equal to or greater than zero in cases
		//of other being less than node, etc.
		cmpres = strcmp(other->key, node->key);
		if(cmpres == 0) break;

		ahead = (cmpres < 0) ? node->left : node->right;
		stepLeft = cmpres < 0;
		stepRight = !stepLeft;
		if (ahead != NULL) {
			//we check if other is the same as ahead
			cmpresA = strcmp(other->key, ahead->key);

			if(cmpresA == 0) break;
			
			//other is bigger than the node ahead and we need to coninue searching
			//for an appropriate place to insert it
			else if((stepRight && cmpres > 0) || (stepLeft && cmpres > 0)) {
				node = ahead;
				ahead = NULL;
				continue;
			}

			//we can insert it here
			else if((stepRight && cmpres < 0) || (stepLeft && cmpres < 0)) {
				nodeInsertion(node, ahead, other, stepLeft);
				tree->size++;
				//balanceTree(tree);
				success = true;
				break;
			}
		} else {
			if (stepRight) node->right = other;
			else node->left = other;
		}
	}

	return success;
}

//helper method
void nodeInsertion(BinaryNode *first, BinaryNode *last, BinaryNode *insertion, bool stepLeft) {
	if (stepLeft) {
		first->left = insertion;
	} else {
		first->right = insertion;
	}

	int cmpres = strcmp(insertion->key, last->key);

	if (cmpres < 0) {
		insertion->right = last;
	} else {
		insertion->left = last;
	}
}

bool bf_delete(BinaryTree *tree, BinaryNode *other) {
	return false;
}

bool bf_search(BinaryTree *tree, char *key) {
	bool found = false;
	int cmpres = -1;
	BinaryNode *node;

	if (tree != NULL && tree->size > 0) {
		node = tree->node;
	}
	else {
		return found;
	}

	while (!found) {
		cmpres = strcmp(node->key, key);
		if(cmpres == 0) {
			found = true;
			break;
		}

		node = (cmpres > 0) ? node->left : node->right;

		if (node == NULL) break;
	}

	return found;
}

void printTree(BinaryTree *tree) {
	printf("size of tree is %zu", tree->size);
	/*for(size_t i = 0; i < tree.size; ++i) {

	}*/
}