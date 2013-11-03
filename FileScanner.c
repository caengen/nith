#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include "binaryNode.h"
#include "binaryTree.h"
#include "FileScanner.h"

/* TODO: Merge this file with BinaryFunctions.c */

BinaryTree createBinaryTree(char *path) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	size_t lineNumber = 1;
	ssize_t lineLength;

	BinaryTree tree;

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

void createBinaryNodes(BinaryTree tree, char *line, size_t lineNumber, ssize_t lineLength) {
	char *word = NULL;
	size_t start = 0;
	size_t end = 0;
	size_t wordNumber = 1;

	for (int i = 0; i < lineLength; ++i) {
		if (line[i] == ' ') {
			end = i-1;

			word = substring(line, start, end);

			bool exists = bf_search(word);

			if(!exists) {
				BinaryNode node {
					.key = word,
					.left = NULL,
					.right = NULL,
					.lineNumber = lineNumber,
					.wordNumber = wordNumber,
					.lineLength = lineLength;

				};
				bf_insert(tree, node);
			}
		}
		start = end+1;
		++wordNumber;
	}

	if(word) free(word);
}



/*
char* readline(char *line, int * line_size, FILE *file) {
	//memset(*line, '\n', line_size);

	return NULL;
	
}

void begin(FILE *fp, char *path, char *line) {
	line = (char*) malloc(sizeof(char) * 512);
}

void end(FILE *fp, char *line) {
	if(line) free(line);
	fclose(fp);
}

void scanfile(char *path) {
	FILE *fp = fopen(path, "r");
	char *line = NULL;	

	begin(fp, path, line);

	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	while ( fgets(line, 512, fp) != NULL ) {
		printf("%s", line);
		line = NULL;
	}

	end(fp, line);
}
*/
