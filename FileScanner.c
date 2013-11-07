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
	   createNodes(tree, line, lineNum++, lineLength);
	}

	if (line) free(line);

	return tree;
}

void createNodes(BinaryTree *tree, char *line, size_t lineNum, size_t lineLength) {
	char *word = malloc(sizeof(char)*128);
	size_t start = 0;
	size_t end = 0;
	size_t wordNum = 1;

	for (int i = 0; i < lineLength; ++i) {
		if (line[i] == ' ') {
			end = i;

			word = substring(start, end, line, word, sizeof(word));

			BinaryNode *resolved = rec_search(&tree->node, word);
			
			if(!resolved) {
				rec_add(&tree->node, word, lineNum, lineLength, wordNum);
				tree->size++;
			}
		}
		start = end;
		++wordNum;
	}

	if(word) free(word);
}

char* substring(size_t start, size_t end, char *src, char *dst, size_t size) {
   int count = end - start;
   if ( count >= --size ) {
      count = size;
   }
   sprintf(dst, "%.*s", count, src + start);
   printf("substring gir %s\n", dst);
   return dst;
}
