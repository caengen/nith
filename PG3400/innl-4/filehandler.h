#pragma once
#include "TGAHeader.h"

void load_header(char* filename, TGAHeader *header);

void load_image(char *filename, TGAHeader *header);

void save_image(char *filename, TGAHeader header, char* imgout, int imgSize, char *imageid);
