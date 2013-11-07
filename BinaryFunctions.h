#pragma once
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"

void rec_add(BinaryNode **, BinaryNode *, char *, size_t, size_t, size_t);

BinaryNode * rec_search(BinaryNode **, char *);

bool bf_delete(BinaryTree *, BinaryNode *);

void printTree(BinaryNode **);
