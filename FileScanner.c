#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "FileScanner.h"

/* TODO: Merge this file with BinaryFunctions.c */

BinaryTree createBinaryTree(char *) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	size_t line_number = 0;
	ssize_t line_length;

	fp = fopen(path, "r");
	if (fp == NULL)
	   exit(EXIT_FAILURE);

	while ((line_length = getline(&line, &len, fp)) != -1) {
	   printf("%zu:%s", line_number, line);
	   ++line_number;
	}

	if (line)
	   free(line);
	exit(EXIT_SUCCESS);

	return NULL;
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
