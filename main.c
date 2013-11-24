#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include "Pixel.h"
#include "TGAHeader.h"

void free_pixel(Pixel **pixel) {
	if (pixel) free(pixel);
}

//Can we process the current img
void processability(TGAHeader *header) {

}

/* 24 bit images will have 3 channels consisting of 8 bits each, meaning r, g, b
 * 32 bit images will have 4 channels consisting of 8 bits each, meaning r, g, b, a
 * where a is the alpha for each pixel.
 */
void add_pixl_to_img(uint32_t itr, FILE* fp, char pixeldepth, Pixel *img) {
	int i;

	if (pixeldepth == 24) {
		for (i = pixeldepth / 8; i > 0; i--) {
			img[itr].r = fgetc(fp);
			img[itr].g = fgetc(fp);
			img[itr].b = fgetc(fp);
			img[itr].a = fgetc(fp);
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
const char RLE_UNCOMPRESSED = 10;
const char RLE_MAPPED_B_W = 11;
void load_image(char *filename, TGAHeader *header, Pixel *img) {
	const unsigned char headerSize = 18, imgIDSize = 255; 
	uint32_t colorMapData = (header->colormapentry * header->colormaplength) / 8;
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

	//We skip over the image ID data it is 256 bytes long
	//We also ignore the Color Map Data field, however it
	//is variable lengthed and we need to use color map
	//entry size and color map length to find the size.
	fseek(fp, headerSize + imgIDSize + colorMapData, SEEK_SET);

	while(header->imgwidth * header->imgheight) {
		add_pixl_to_img(itr++, fp, header->pixeldepth, img);
	}
	
	fclose(fp);
}


void convert_grayscale(TGAHeader *headin, Pixel *imgin, TGAHeader *headout, Pixel *imgout) {
	headout->idlength = headin.idlength;
	headout->colormaptype = 0;
	headout->imagetype = UNCOMPRESSED_B_W;
	headout->colormapentry = headin->colormapentry;
	headout->colormaplength = headin->colormaplength;
	headout->colormapentrysize = 24;
	headout->xorigin = headin->xorigin;
	headout->yorigin = headin->yorigin;
	headout->imgwidth = headin->imgwidth;
	headout->imgheight = headin->imgheight;
	headout->pixeldepth = 8;
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

void load_header(char* filename, TGAHeader *header) {
	FILE *fp;

	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	short left;
	short right;

	//Read the header. 
	//The total size of the header is 18 bytes.

	/* DEBUG: LAG METODE */
	header->idlength = fgetc(fp);
	header->colormaptype = fgetc(fp);
	header->imagetype = fgetc(fp);

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;
	header->colormapentry = right | left;

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;
	header->colormaplength = right | left;

	header->colormapentrysize = fgetc(fp);

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;	
	header->xorigin = right | left;

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;	
	header->yorigin = right | left;

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;	
	header->imgwidth = right | left;

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;	
	header->imgheight = right | left;

	header->pixeldepth = fgetc(fp);
	header->imagedescriptor = fgetc(fp);

	//close/free stuff
	fclose(fp);
}

char* merge_header(TGAHeader header) {
	char merged[18];

	merged[0] = header.idlength;
	merged[1] = header.colormaptype;
	merged[2] = header.imagetype;
	merged[3] = (header.colormapentry >> 8) & 0x00ff;
	merged[4] = 

	return NULL;
}

void save_image(char *filename, TGAHeader headout, Pixel *imgout) {

	FILE *fp = fopen("lol.tga", "w");

	right = fgetc(fp) & 0x00ff;
	left = (fgetc(fp) << 8) & 0xff00;	

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

void malloc_pixel(Pixel **pixel) {
	//We assume the image data contains only whole img
	//therefore the total size of the image
	Pixel *p = malloc(sizeof(Pixel));

	p->r = 0;
	p->g = 0;
	p->b = 0;
	p->a = 0;

	*pixel = p;
	
}

int main(void) {
	char * filename = "Calvin-Hobbes.tga";

	TGAHeader headin;
	TGAHeader headout;
	
	load_header(filename, &headin);

	processability(&headin);


	int width = headin.imgwidth;
	int height= headin.imgheight;

	Pixel *imgin;
	Pixel *imgout;
	imgin = malloc(width * height * sizeof(imgin));
	imgout = malloc(width * height * sizeof(imgout));

	//const unsigned char headerSize = 18, imgIDSize = 255; 
	//uint32_t colorMapData = (headin.colormapentry * headin.colormaplength) / 8;
	uint32_t itr = 0;


	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	//We skip over the image ID data it is 256 bytes long
	//We also ignore the Color Map Data field, however it
	//is variable lengthed and we need to use color map
	//entry size and color map length to find the size.
	//fseek(fp, headerSize + imgIDSize + colorMapData, SEEK_SET);

	while(itr < headin.imgwidth * headin.imgheight) {
		int i;

		if (headin.pixeldepth == 24) {
			for (i = headin.pixeldepth / 8; i > 0; i--) {
				imgin[itr].r = fgetc(fp);
				imgin[itr].g = fgetc(fp);
				imgin[itr].b = fgetc(fp);
				imgin[itr].a = fgetc(fp);
			}
		}
		else if(headin.pixeldepth == 32) {
			for (i = headin.pixeldepth / 8; i > 0; i--) {
				imgin[itr].r = fgetc(fp);
				imgin[itr].g = fgetc(fp);
				imgin[itr].b = fgetc(fp);
				imgin[itr].a = fgetc(fp);
			}
		}

		itr++;
	}
	
	fclose(fp);

 	convert_grayscale(&headin, imgin, &headout, imgout);

 	save_image(filename, headout, imgout);

/*
	for (i = 0; i < width * height; i++)
	{
		free_pixel(&imgin[i]);
		free_pixel(&imgout[i]);
	}
*/
	return EXIT_SUCCESS;
}
