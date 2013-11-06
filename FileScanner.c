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
	size_t lineNum = 1;
	size_t lineLength;

	BinaryTree *tree = malloc(sizeof(BinaryTree));
	tree->node = NULL;
	tree->size = 0;

	fp = fopen(path, "r");
	if (fp == NULL)
	   exit(EXIT_FAILURE);

	while ((lineLength = getline(&line, &len, fp)) != -1) {
	   //printf("%zu:%s", lineNum, line); DEBUG
	   createBinaryNodes(tree, line, lineNum++, lineLength);
	}

	if (line) free(line);

	return tree;
}

void createBinaryNodes(BinaryTree *tree, char *line, size_t lineNum, size_t lineLength) {
	char *word = malloc(sizeof *word);
	size_t start = 0;
	size_t end = 0;
	size_t wordNum = 1;

	for (int i = 0; i < lineLength; ++i) {
		if (line[i] == ' ') {
			end = i-1;

			word = substring(start, end, line, word, sizeof(word));

			bool exists = rec_search(&tree->node, word);
			printf("bool exists = %d\n", exists);
			/*
			if(!exists) {
				BinaryNode node = {
					.key = word,
					.left = NULL,
					.right = NULL,
					.lineNum = lineNum,
					.wordNum = wordNum,
					.lineLength = lineLength
				};
				bf_insert(tree, &node);
			}*/
			if(!exists)
				rec_add(&tree->node, word, lineNum, lineLength, wordNum);

		}
		start = end+1;
		++wordNum;
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
