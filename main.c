#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "Pixel.h"
#include "TGAHeader.h"

TGAHeader load_header(char* filename) {
	TGAHeader header;
	FILE *fp;

	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	//Read the header. 
	//The total size of the header is 18 bytes.
	//fgetc returns an unsigned char cast to an int, or 1 byte of data
	header.idlength = fgetc(fp);
	header.colormaptype = fgetc(fp);
	header.imagetype = fgetc(fp);
	//To read more than one byte we use fread and specifiy member length
	fread(&header.colormapentry, 2, 1, fp); //Read 1 member, 2 bytes long
	fread(&header.colormaplength, 2, 1, fp);
	header.colormaplength = fgetc(fp);
	fread(&header.xorigin, 2, 1, fp);
	fread(&header.yorigin, 2, 1, fp);
	fread(&header.imgwidth, 2, 1, fp);
	fread(&header.imgheight, 2, 1, fp);
	header.pixeldepth = fgetc(fp);
	header.imagedescriptor = fgetc(fp);

	//close/free stuff
	fclose(fp);
	return header;
}

void malloc_image(Pixel *pixels, TGAHeader *header) {
	//We assume the image data contains only whole pixels
	//therefore the total size of the image
	pixels = malloc(header->imgwidth*header->imgheight*sizeof(Pixel));
	
	for (int i = 0; i < header->imgwidth*header->imgheight; i++) {
		pixels[i].r = 0;
		pixels[i].g = 0;
		pixels[i].b = 0;
		pixels[i].a = 0;
	}
}

//Can we process the current img
void processability(TGAHeader *header) {

}

void add_pixel(Pixel *pixel, unsigned char * px, int bytes) {

}

const char COLOR_MAPPED = 1;
const char UNCOMPRESSED = 2;
const char UNCOMPRESSED_B_W = 3;
const char RLE_COLOR_MAPPED = 9;
const char RLE_UNCOMPRESSED = 10
;const char RLE_MAPPED_B_W = 11;
Pixel * load_image(char *filename, TGAHeader *header, Pixel *img) {
	unsigned char *pixl;
	const unsigned char headerSize = 18, imgIDSize = 255, colorMapData = (header->colormapentry * header->colormaplength) / 8;
	int itr = 0;

	if (!header) {
		fprintf(stderr, "Non-valid TGAHeader argument");
		exit(-1)
	}

	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	//We skip over the image ID data it is 255 bytes long
	//We also ignore the Color Map Data field, however it
	//is variable lengthed and we need to use color map
	//entry size and color map length to find the size.
	fseek(fp, headerSize + imgIDSize + colorMapData, SEEK_SET);

	while(header->width * header->height) {
		add_pxl_to_img(itr, pixl, header, img);

		itr++;
	}
	

	fclose(fp);
}

void add_pxl_to_img() {

}

void convert_grayscale(TGAHeader *headin, Pixel *imgin,TGAHeader *headout, Pixel *imgout) {
	headout.idlength = 0;
	headout.colormaptype = 0;
	headout.imagetype = UNCOMPRESSED_B_W;
	headout.colormapentry = 0
	headout.colormaplength = 0;
	headout.colormaplength = 0;
	headout.xorigin =;
	headout.yorigin = 0;
	headout.imgwidth =
	headout.imgheight =
	headout.pixeldepth = 0;
	headout.imagedescriptor = 0;



	int i;
	for (i = 0; i < headin->imgwidth * headin->imgheight; ++i) {
		Pixel *pin = &imgin[i*4];
		Pixel *pout = &imgout[i*4];
		
		float luma = 0.299 * pin->r + 0.587 * pin->g + 0.114 * pin->b;
		if (luma > 255) luma = 255;
	}

}

void save_image(char *filename, TGAHeader headout, Pixel *imgout) {
	FILE *fp = fopen(filename, "w");
	//put header into file

	//put image data into file
}

int main(void) {
	char * filename = "link.tga";

	TGAHeader headin;
	Pixel *imgin;
	TGAHeader headout;
	Pixel *imgout;
	
	headin = load_header(filename);

	malloc_image(imgin, &headin);

	processability(&headin);
 	
 	load_image(filename, &headin, imgin);

 	convert_grayscale(&headin, imgin, &headout, imgout);

	return EXIT_SUCCESS;
}
