#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "FileScanner.h"

void printfile(char *path) {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(path, "r");
	if (fp == NULL)
	   exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
	   printf("Retrieved line of length %zu :\n", read);
	   printf("%s", line);
	}

	if (line)
	   free(line);
	exit(EXIT_SUCCESS);
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
