#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "FileScanner.h"
#include "BinaryFunctions.h"
/* @author 		Cengen
 * @last edit	08/11/2013
 */

char *delims = " ,.-_:;\n!?/&%()[]*'\"$@#+";
char *word;
char * line;
FILE * fp;
BinaryTree *tree;
const int MAX_LINE_SIZE = 81;

/* Function responsible for reading lines from a file, and sending
 * words from that line as arguments to the add function of BinaryFunctions.
 * 
 */
BinaryTree * createBinaryTreeFromFile(char *path) {
	size_t len = 0;
	size_t lineNum = 1;
	size_t lineLength;

	tree = malloc(sizeof(BinaryTree));
	tree->node = NULL;
	tree->size = 0;


	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("There is no such file. Make sure the file is located in the same folder as the .o files.\n");
	   	exit(EXIT_FAILURE);
	}

	//We iterate through each line of the file
	while ((lineLength = getline(&line, &len, fp)) != -1) {
		word = strtok(line, delims);
		int wordNum = 1;
		//We iterate through each word in the line
		while(word) {
			add(&tree->node, NULL, word, lineNum, lineLength, wordNum);
			word = strtok(NULL, delims);
			wordNum++;
		}
		lineNum++;
	}

	return tree;
}

void closeFileScanner(void) {
	if(line) free(line);
	if (tree) free(tree);
	if (fp) fclose(fp);
}