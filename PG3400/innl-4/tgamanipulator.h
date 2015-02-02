#pragma once
#include "TGAHeader.h"

int convert_grayscale(int, int, int);

char * merge_convert_header(TGAHeader, char *);

void flip_image(char *, TGAHeader *);