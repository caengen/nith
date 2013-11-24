#define _GNU_SOURCE
#include <stdlib.h>
#include "TGAHeader.h"
#include "utils.h"
#include "filehandler.h"
#include "tgamanipulator.h"

int main(int argc, char **argv) {

	TGAHeader header;
	
	load_header(argv[1], &header);

	if (argc > 2) {
		flip_image(argv[2], &header);
	}

	evaluate_image(header.imagetype);

	load_image(argv[1], &header);

	return EXIT_SUCCESS;
}
