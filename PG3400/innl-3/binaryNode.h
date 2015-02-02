#pragma once
#include <sys/types.h>
/* @author 		Cengen
 * @last edit	07/11/2013
 */

/*BinaryNode for storing word data from a file
 * Stores this data
 * val 			a word from a file
 * lineNum 		the line that word was found one
 * wordNum		the placement of the word in the line
 * lineLength 	the total length of the line
 */
typedef struct binaryNode {
	char *val;
	struct binaryNode *parent, *left, *right;
	size_t lineNum;
	size_t wordNum;
	size_t lineLength;
} BinaryNode;