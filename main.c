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
	printf("We see you want to have %d files scanned.\n", (argc-1));
	printf("Scanning files...\n\n");

}

void explainSearch() {
	printf("Type the word you want to search for (type q to quit).\n");
	printf("Max string length allowed is 80 characters.\n");
	printf("Search for: ");
}

const int MAX_SEARCH_WORD = 80;
void readSearchInput(bool *finished, char *searchWord) {

	scanf("%s", searchWord);

	if (strncmp(searchWord, "q", MAX_SEARCH_WORD) == 0) {
		*finished = true;
	}
}

/* When running main you pass all the files you want to read as
 * arguments. Words from all files are added into the tree as if
 * they were a single document, with the first file argument being
 * the lead of the "single document".
 * 
 */
int main(int argc, char **argv) {
	bool finished = false;

	printIntroduction(argc);

    BinaryTree *bt = createBinaryTreeFromFile(argc, argv);
    printf("Binary tree created.\n\n");

    while (!finished) {
		char *searchWord = malloc(sizeof(char)*MAX_SEARCH_WORD);

    	explainSearch();
    	readSearchInput(&finished, searchWord);

    	if (finished) {
    		free(searchWord);
    		break;
    	}

	    BinaryNode *res = search(&bt->node, searchWord);

		if(res) {
			printf("\nWord was %20s\nAt line %21zu\nWord placement in line %6zu\nLine total length %11zu\n\n", res->val, res->lineNum, res->wordNum, res->lineLength);
		} else {
			printf("There are no occurences of the word \"%s\" in the file \"%s\".\n\n", argv[2], argv[1]);
		}

		if(searchWord) {
			free(searchWord);
		}
    } 

    //cleanup
	freeTree(bt->node);
	closeFileScanner();

	return EXIT_SUCCESS; 
}