#include <stdlib.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"
#include "FileScanner.h"

int main(void) {
	
	BinaryTree *bt = createBinaryTree("./test.txt");
	//printf("\nTree size is %zu\n", bt->size);
	BinaryNode *res = rec_search(&bt->node, "av");

	if(res) {
		printf("Result was key=%s, line=%zu, word=%zu, length=%zu\n", res->key, res->lineNum, res->wordNum, res->lineLength);
	}

	return EXIT_SUCCESS; 
}
