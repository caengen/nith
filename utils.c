#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void evaluate_image(char imagetype) {
	if (imagetype != 2) {
		fprintf(stderr, "The image type is not supported.");
		exit(EXIT_FAILURE);
	}
}

unsigned int get_filesize(FILE *file) {
	unsigned int filesize;
	if (fseek (file, 0, SEEK_END) == 0) {
		filesize = ftell(file);
		rewind(file);
	} else {
		fprintf(stderr, "File size can not be read.");
		exit(EXIT_FAILURE);
	}

	return filesize;
}

short fread_smallendian(FILE *fp) {
	short right = fgetc(fp) & 0x00ff;
	short left = (fgetc(fp) << 8) & 0xff00;

	return right | left;
}