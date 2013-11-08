#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "FileScanner.h"
#include "BinaryFunctions.h"
/* @author 		Cengen
 * @last edit	08/11/2013
 */

 void printIntroduction(int argc) {
	printf("\n\nWelcome, to the Scan-O-Matic Machine, that's SOMM for short.\n");
	printf("We see you want to have %d files scanned.\n\n", (argc-1));

}

void explainSearch() {
	printf("Type the word you want to search for (type q to quit).\n");
	printf("Max string length allowed is 80 characters.\n");
	printf("Search for: ");
}

const int MAX_SEARCH_WORD = 80;
char* readSearchInput(bool *finished) {
	char* searchWord = malloc(sizeof(char)*MAX_SEARCH_WORD);

	scanf("%s", searchWord);

	if (strncmp(searchWord, "q", MAX_SEARCH_WORD) == 0) {
		*finished = true;
	}

	return searchWord;
}

/* When running main the first argument (ignoring the execute argument itself) should
 * be the file.txt you want read, and the second argument should be the word
 * you want to search for.
 *
 */
int main(int argc, char **argv) {
	bool finished = false;

	printIntroduction(argc);

    BinaryTree *bt = createBinaryTreeFromFile(argv[1]);
    printf("Binary tree created.\n\n");

    while (!finished) {
    	char *searchWord;

    	explainSearch();
    	searchWord = readSearchInput(&finished);
    	if (finished) break;

	    BinaryNode *res = search(&bt->node, searchWord);

		if(res) {
			printf("\nWord was %20s\nAt line %21zu\nWord placement in line %6zu\nLine total length %11zu\n\n", res->val, res->lineNum, res->wordNum, res->lineLength);
		} else {
			printf("There are no occurences of the word \"%s\" in the file \"%s\".\n", argv[2], argv[1]);
		}

		if(searchWord) free(searchWord);
    } 

	//free tree
	freeTree(bt->node);
	closeFileScanner();

	return EXIT_SUCCESS; 
}