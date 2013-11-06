#pragma once
#include <stdio.h>
#include "binaryTree.h"

BinaryTree* createBinaryTree(char *);

void createNodes(BinaryTree *, char *, size_t, size_t);

char* substring(size_t, size_t, char *, char *, size_t);
