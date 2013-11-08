#pragma once
#include <stdbool.h>
#include "binaryNode.h"
#include "binaryTree.h"
/* @author 		Cengen
 * @last edit	08/11/2013
 */
 
void add(BinaryNode **, BinaryNode *, char *, size_t, size_t, size_t);

BinaryNode * search(BinaryNode **, char *);

void freeTree(BinaryNode *tree);

bool delete(BinaryTree *, BinaryNode *);
