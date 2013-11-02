#include <stdlib.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "BinaryFunctions.h"
#include "FileScanner.h"

int main(void) {
	
	BinaryTree bt = createBinaryTree("./test.txt");
	
	return EXIT_SUCCESS; 
}