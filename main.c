#include <stdlib.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"
#include "FileScanner.h"

int main(void) {
	
	BinaryTree *bt = createBinaryTree("./test.txt");
	//printTree(&bt->node);
	printf("%s", bt->node->key);
	printf("\nTree size is %zu\n", bt->size);

	
	return EXIT_SUCCESS; 
}