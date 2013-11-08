#include <stdlib.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"
#include "FileScanner.h"
/* @author 		Cengen
 * @last edit	08/11/2013
 */


/* When running main the first argument (ignoring the execute argument itself) should
 * be the file.txt you want read, and the second argument should be the word
 * you want to search for. 
 *
 */
int main(int argc, char** argv) {
	
    BinaryTree *bt = createBinaryTreeFromFile(argv[1]);

    printf("Binary tree created.\n");

    BinaryNode *res = search(&bt->node, argv[2]);

	if(res) {
		printf("Word was %20s\nAt line %21zu\nWord placement in line %6zu\nLine total length %11zu\n", res->val, res->lineNum, res->wordNum, res->lineLength);
	} else {
		printf("There are no occurences of the word \"%s\" in the file \"%s\".\n", argv[2], argv[1]);
	}

	//free tree
	freeTree(bt->node);
	if(bt) free(bt);

	return EXIT_SUCCESS; 
}
