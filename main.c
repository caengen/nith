#include <stdlib.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"
#include "FileScanner.h"

int main(void) {
	
    BinaryTree *bt = createBinaryTree("./pg4300.txt");
    printf("Ferdig å legge inn!\n");
    BinaryNode *res = rec_search(&bt->node, "Nationalgymnasiummuseumsanatoriumandsuspensoriumsordinaryprivatdocent");

	if(res) {
		printf("Result was key=%s, line=%zu, word=%zu, length=%zu\n", res->key, res->lineNum, res->wordNum, res->lineLength);
	}

	return EXIT_SUCCESS; 
}
