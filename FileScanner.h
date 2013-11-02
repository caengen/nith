#pragma once
#include <stdio.h>
#include "binaryTree.h"

BinaryTree createBinaryTree(char *);

void createBinaryNodes(BinaryTree *, char *, size_t, ssize_t);

/*
void begin(FILE *, char *, char *);

void end(FILE *, char *);

void scanfile(char *);

char* readline(char *, int *, FILE *);

char* next();

char* nextLine();*/
