#pragma once
#include <sys/types.h>

typedef struct binaryNode {
	char *key;
	struct node *left, *right;
	size_t line_number;
	size_t word_number;
	ssize_t line_length;
} BinaryNode;