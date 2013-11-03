#pragma once
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"

bool bf_insert(BinaryTree *, BinaryNode *);

bool bf_delete(BinaryTree *, BinaryNode *);

bool bf_search(BinaryTree *, char *);

void nodeInsertion(BinaryNode *, BinaryNode *, BinaryNode *, bool);

void printTree(BinaryTree);