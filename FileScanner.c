#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "FileScanner.h"
#include "BinaryFunctions.h"

/* TODO: Merge this file with BinaryFunctions.c */
BinaryTree* createBinaryTree(char *path) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	size_t lineNumber = 1;
	size_t lineLength;

	BinaryTree *tree = malloc(sizeof(BinaryTree));

	fp = fopen(path, "r");
	if (fp == NULL)
	   exit(EXIT_FAILURE);

	while ((lineLength = getline(&line, &len, fp)) != -1) {
	   printf("%zu:%s", lineNumber, line);
	   createBinaryNodes(tree, line, lineNumber++, lineLength);
	}

	if (line) free(line);

	return tree;
}

void createBinaryNodes(BinaryTree *tree, char *line, size_t lineNumber, size_t lineLength) {
	char *word = malloc(sizeof *word);
	size_t start = 0;
	size_t end = 0;
	size_t wordNumber = 1;

	for (int i = 0; i < lineLength; ++i) {
		if (line[i] == ' ') {
			end = i-1;

			word = substring(start, end, line, word, sizeof word);

			bool exists = bf_search(tree, word);

			if(!exists) {
				BinaryNode node = {
					.key = word,
					.left = NULL,
					.right = NULL,
					.lineNumber = lineNumber,
					.wordNumber = wordNumber,
					.lineLength = lineLength
				};
				bf_insert(tree, &node);
			}
		}
		start = end+1;
		++wordNumber;
	}

	if(word) free(word);
}

char* substring(size_t start, size_t end, char *src, char *dst, size_t size) {
   int count = end - start;
   if ( count >= --size )
   {
      count = size;
   }
   sprintf(dst, "%.*s", count, src + start);
   return dst;
}
