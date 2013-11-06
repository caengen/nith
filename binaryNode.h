#pragma once
#include <sys/types.h>

typedef struct binaryNode {
	char *key;
	struct binaryNode *left, *right;
	size_t lineNum;
	size_t wordNum;
	size_t lineLength;
} BinaryNode;