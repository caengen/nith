#include <stdbool.h>
#include "BinaryFunctions.h"

bool insert(BinaryTree *tree, BinaryNode *other) {
	bool success = false;
	int cmpres = 0;
	int cmpresA = 0;
	BinaryNode node = tree;
	BinaryNode ahead = NULL;

	while (true) {
		cmpres = strcmp(node.key, other.key);
		if(cmpres == 0) {
			break;
		}

		ahead = (cmpres > 0) ? node.left : node.right;

		cmpresA = strcmp(ahead.key, other.key);
		if(cmpresA == 0) {
			break;
		}

		if (cmpres < 0 && compresA > 0 || cmpres > 0 && compresA < 0) {
			
		}
	}

	return success;
}

bool delete(BinaryTree *tree, BinaryNode *other) {
	return false;
}

bool search(BinaryTree *tree, char *key) {
	bool found = false;
	int cmpres = -1;

	if (tree.size > 0)
		BinaryNode node = tree.node;
	else
		found = !found;

	while (!found) {
		cmpres = strcmp(node.key, key);
		if(cmpres == 0) {
			found = true;
			break;
		}

		node = (cmpres > 0) ? node.left : node.right;

		if (node == NULL) break;
	}

	return found;
}