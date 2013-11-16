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
	header.idlength = fgetc(fp);
	header.colourmaptype = fgetc(fp);
	header.imagetype = fgetc(fp);
	fread(&header.colourmaporigin, 2, 1, fp); //Read 1 member, 2 bytes long
	fread(&header.colourmaplength, 2, 1, fp);
	header.colourmapdepth = fgetc(fp);
	fread(&header.xorigin, 2, 1, fp);
	fread(&header.yorigin, 2, 1, fp);
	fread(&header.width, 2, 1, fp);
	fread(&header.height, 2, 1, fp);
	header.pixeldepth = fgetc(fp);
	header.imagedescriptor = fgetc(fp);

	//close/free stuff
	fclose(fp);
	return header;
}

void malloc_image(Pixel *pixels, TGAHeader *header) {
	pixels = malloc(header->width*header->height*sizeof(Pixel));
	
	for (int i = 0; i < header->width*header->height; i++) {
		pixels[i].r = 0;
		pixels[i].g = 0;
		pixels[i].b = 0;
		pixels[i].a = 0;
	}
}

void check_legality(TGAHeader *header) {
	if (header->imagetype != 2 && header->imagetype != 10) {
		fprintf(stderr,"Can only handle image type 2 and 10\n");
		exit(-1);
	}
	if (header->pixeldepth != 16 && 
		header->pixeldepth != 24 && header->pixeldepth != 32) {
		fprintf(stderr,"Can only handle pixel depths of 16, 24, and 32\n");
		exit(-1);
	}
	if (header->colourmaptype != 0 && header->colourmaptype != 1) {
		fprintf(stderr,"Can only handle colour map types of 0 and 1\n");
		exit(-1);
	}
}

void put_pixel(Pixel *pixel, unsigned char * px, int bytes) {
	//32 bit
	if (bytes == 4) {

	}
	//24 bit, no alpha
	else if (bytes == 3) {
		pixel->r = px[2];
		pixel->g = px[1];
		pixel->b = px[0];
		pixel->a = 0;
	}
	//16 bit
	else if(bytes == 2) {

	}
}

const char COLOR_MAPPED = 1;
const char UNCOMPRESSED = 2;
const char UNCOMPRESSED_B_W = 3;
const char RLE_COLOR_MAPPED = 9;
const char RLE_UNCOMPRESSED = 10;
const char RLE_MAPPED_B_W = 11;
Pixel * load_image(char *filename, TGAHeader *header, Pixel *img) {
	int bytes2read, skipover = 0, i = 0, itr = 0;
	unsigned char *px;

	if (!header) {
		fprintf(stderr, "Non-valid TGAHeader argument");
		exit(-1);
	}

	FILE *fp;
	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(-1);
	}

	/* Skip over unnecessary stuff */
	skipover += header->idlength;
	skipover += header->colourmaptype * header->colourmaplength;
	fprintf(stderr,"Skip over %d bytes\n",skipover);
	fseek(fp,skipover,SEEK_CUR);

	bytes2read = header->pixeldepth / 8;
	while (itr < header->width * header->height) {
		switch (header->imagetype) {
			case UNCOMPRESSED:
				if (fread(px, 1, bytes2read, fp) != bytes2read+1) {
					fprintf(stderr,"Unexpected end of file at pixel %d\n",i);
					exit(-1);
				}
				put_pixel(&(img[itr]), px, bytes2read);
				break;
		}
	}

	fclose(fp);
}

void convert_grayscale(TGAHeader *headin, Pixel *imgin,TGAHeader *headout Pixel *imgout) {
	header.idlength = 0;
	header.colourmaptype = 0;
	header.imagetype = UNCOMPRESSED_B_W;
	header.colourmaporigin = 0; //Read 1 member, 2 bytes long
	header.colourmaplength = 0;
	header.colourmapdepth = 0;
	header.xorigin =;
	header.yorigin = 0;
	header.width =
	header.height =
	header.pixeldepth = 0;
	header.imagedescriptor = 0;

	int i;
	for (i = 0; i < headin->width * headin->height; ++i) {
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

	check_legality(&headin);
 	
 	load_image(filename, &headin, imgin);

 	convert_grayscale(&headin, imgin, &headout, imgout);

	return EXIT_SUCCESS;
}
