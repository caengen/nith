#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include "Pixel.h"
#include "TGAHeader.h"

void load_header(char* filename, TGAHeader *header) {
	FILE *fp;

	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	//Read the header. 
	//The total size of the header is 18 bytes.
	//fgetc returns an unsigned char cast to an int, or 1 byte of data
	header->idlength = fgetc(fp);
	header->colormaptype = fgetc(fp);
	header->imagetype = fgetc(fp);
	//To read more than one byte we use fread and specifiy member length
	fread(&header->colormapentry, 2, 1, fp); //Read 1 member, 2 bytes long
	fread(&header->colormaplength, 2, 1, fp);
	header->colormapentrysize = fgetc(fp);
	fread(&header->xorigin, 2, 1, fp);
	fread(&header->yorigin, 2, 1, fp);
	fread(&header->imgwidth, 2, 1, fp);
	fread(&header->imgheight, 2, 1, fp);
	header->pixeldepth = fgetc(fp);
	header->imagedescriptor = fgetc(fp);

	//close/free stuff
	fclose(fp);
}

void malloc_image(Pixel **imgin, int width, int height) {
	//We assume the image data contains only whole img
	//therefore the total size of the image
	Pixel *img = *imgin;
	img = malloc(width * height * sizeof(Pixel));

	for (int i = 0; i < width * height; ++i) {
		Pixel p = {
			.r = 0,
			.g = 0,
			.b = 0,
			.a = 0
		};

		img[i] = p;
	}
}

void free_image(Pixel *img) {
	if (img) free(img);
}

//Can we process the current img
void processability(TGAHeader *header) {

}

/* 24 bit images will have 3 channels consisting of 8 bits each, meaning r, g, b
 * 32 bit images will have 4 channels consisting of 8 bits each, meaning r, g, b, a
 * where a is the alpha for each pixel.
 */
void add_pixl_to_img(uint32_t itr, FILE* fp, char pixeldepth, Pixel **imgin) {
	int i;
	
	Pixel *img = *imgin;

	if (pixeldepth == 24) {
		for (i = pixeldepth / 8; i > 0; i--) {
			img[itr].r = fgetc(fp);
			img[itr].g = fgetc(fp);
			img[itr].b = fgetc(fp);
			img[itr].a = 0;
		}
	}
	else if(pixeldepth == 32) {
		for (i = pixeldepth / 8; i > 0; i--) {
			img[itr].r = fgetc(fp);
			img[itr].g = fgetc(fp);
			img[itr].b = fgetc(fp);
			img[itr].a = fgetc(fp);
		}
	}
}

const char COLOR_MAPPED = 1;
const char UNCOMPRESSED = 2;
const char UNCOMPRESSED_B_W = 3;
const char RLE_COLOR_MAPPED = 9;
const char RLE_UNCOMPRESSED = 10
;const char RLE_MAPPED_B_W = 11;
void load_image(char *filename, TGAHeader *header, Pixel **img) {
	const unsigned char headerSize = 18, imgIDSize = 255, colorMapData = (header->colormapentry * header->colormaplength) / 8;
	uint32_t itr = 0;

	if (!header) {
		fprintf(stderr, "Non-valid TGAHeader argument");
		exit(-1);
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

	while(header->imgwidth * header->imgheight) {
		add_pixl_to_img(itr++, fp, header->pixeldepth, img);
	}
	
	fclose(fp);
}

void convert_grayscale(TGAHeader *headin, Pixel *imgin,TGAHeader *headout, Pixel *imgout) {
	headout->idlength = 0;
	headout->colormaptype = 0;
	headout->imagetype = UNCOMPRESSED_B_W;
	headout->colormapentry = 0;
	headout->colormaplength = 0;
	headout->colormapentrysize = 24;
	headout->xorigin = headin->xorigin;
	headout->yorigin = headin->yorigin;
	headout->imgwidth = headin->imgwidth;
	headout->imgheight = headin->imgheight;
	headout->pixeldepth = 16;
	headout->imagedescriptor = 0;

	int i;

	for (i = 0; i < (headin->imgwidth * headin->imgheight); ++i) {	
		float luma = 0.299 * imgin[i].r + 0.587 * imgin[i].g + 0.114 * imgin[i].b;
		if (luma > 255) luma = 255;

		int intluma = (int) luma;

		imgout[i].r = intluma;
		imgout[i].g = intluma;
		imgout[i].b = intluma;
		imgout[i].a = 255;
	}

}

void save_image(char *filename, TGAHeader headout, Pixel *imgout) {
	FILE *fp = fopen(filename, "w");

	//put header into file
	fwrite(&headout.idlength, 1, 1, fp);
	fwrite(&headout.colormaptype, 1, 1, fp);
	fwrite(&headout.imagetype, 1, 1, fp);
	fwrite(&headout.colormapentry, 2, 1, fp);
	fwrite(&headout.colormaplength, 2, 1, fp);
	fwrite(&headout.colormapentrysize, 1, 1, fp);
	fwrite(&headout.xorigin, 2, 1, fp);
	fwrite(&headout.yorigin, 2, 1, fp);
	fwrite(&headout.imgwidth, 2, 1, fp);
	fwrite(&headout.imgheight, 2, 1, fp);
	fwrite(&headout.pixeldepth, 1, 1, fp);
	fwrite(&headout.imagedescriptor, 1, 1, fp);

	//put image data into file
	int i;

	for (i = 0; i < headout.imgwidth * headout.imgheight; ++i) {
		fwrite(&imgout[i].r, 1, 1, fp);
		fwrite(&imgout[i].g, 1, 1, fp);
		fwrite(&imgout[i].b, 1, 1, fp);
		fwrite(&imgout[i].a, 1, 1, fp);
	}

	fclose(fp);
}

int main(void) {
	char * filename = "link.tga";

	TGAHeader headin;
	Pixel *imgin = NULL;
	TGAHeader headout;
	Pixel *imgout = NULL;
	
	load_header(filename, &headin);

	//malloc_image(&imgin, headin.imgwidth, headin.imgheight);

	imgin = malloc(headin.imgwidth * headin.imgheight * sizeof(Pixel));

	for (int i = 0; i < headin.imgwidth * headin.imgheight; ++i) {
		Pixel p = {
			.r = 0,
			.g = 0,
			.b = 0,
			.a = 0
		};

		imgin[i] = p;
	}

	malloc_image(&imgout, headin.imgwidth, headin.imgheight);

	processability(&headin);
 	
 	load_image(filename, &headin, &imgin);

 	convert_grayscale(&headin, imgin, &headout, imgout);

 	save_image(filename, headout, imgout);

 	free_image(imgin);
 	free_image(imgout);

	return EXIT_SUCCESS;
}
