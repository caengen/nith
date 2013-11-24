#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include "Pixel.h"
#include "TGAHeader.h"

void save_image(char*, TGAHeader, char*, int);

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
int add_pixl_to_img(/*uint32_t itr, FILE* fp, char pixeldepth, */int r, int g, int b) {
	//int i;

	return ((((int)r * 30) + ((int)g * 59) + ((int)b * 11)) / 100);

	/*if (pixeldepth == 24) {
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
	}*/
}


unsigned int getFileSize(FILE *file) {
	unsigned int filesize;
	if (fseek (file, 0, SEEK_END) == 0) {
		filesize = ftell(file);
		rewind(file);
	} else {
		printf("File can not be read.");
		exit(EXIT_FAILURE);
	}
	return filesize;

}

const char COLOR_MAPPED = 1;
const char UNCOMPRESSED = 2;
const char UNCOMPRESSED_B_W = 3;
const char RLE_COLOR_MAPPED = 9;
const char RLE_UNCOMPRESSED = 10;
const char RLE_MAPPED_B_W = 11;
void load_image(char *filename, TGAHeader *header, char *img) {
	if (!header) {
		fprintf(stderr, "Non-valid TGAHeader argument");
		exit(EXIT_FAILURE);
	}

	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(EXIT_FAILURE);
	}

	unsigned int colormapsize, imgsize, imgdatasize, filesize, headsize = 18, footsize = 26;
	char *imgid, *imgmap, *imgbfr, *footer, *imgout;
	int i;
	unsigned char r, g, b;

	filesize = getFileSize(fp);

	imgid = malloc(256 * sizeof(char));
	if (header->idlength > 0) {
		fread(imgid, sizeof(char), header->idlength, fp);
	}

	colormapsize = header->colormaplength * header->colormapentrysize / 8;
	imgsize = header->imgheight * header-> imgwidth;
	imgdatasize = filesize - (headsize + footsize + header->idlength + colormapsize);

	imgmap = malloc(colormapsize * sizeof(char));
	imgbfr = malloc(imgdatasize * sizeof(char));
	footer = malloc(footsize * sizeof(char));
	imgout = malloc(imgsize * sizeof(char));

	fseek(fp, headsize, SEEK_SET);
	fread(imgmap, sizeof(char), colormapsize, fp);
	fread(imgbfr, sizeof(char), imgdatasize, fp);
	fread(footer, sizeof(char), footsize, fp);


	for (i = 0; i < imgsize; i++) 
	{
		r = imgbfr[i * 3];
		g = imgbfr[i * 3 + 1];
		b = imgbfr[i * 3 + 2];
		imgout[i] = add_pixl_to_img(r, g, b);
	}

	save_image("lol2.tga", *header, imgout, imgsize);
	
	free(imgid);
	free(imgmap);
	free(imgbfr);
	free(footer);
	free(imgout);
	fclose(fp);
}




void convert_grayscale(TGAHeader *headin, Pixel *imgin, TGAHeader *headout, Pixel *imgout) {
	headout->idlength = headin->idlength;
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
		exit(EXIT_FAILURE);
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

char* merge_convert_header(TGAHeader header, char *m) {
	header.colormaptype = (char)0;
	header.colormaplength = (char)0;
	header.colormapentrysize = (char)0;
	header.imagetype = UNCOMPRESSED_B_W;
	header.pixeldepth = (char)8;

	char merged[12];

	merged[0] =  (char)((header.colormapentry >> 8) & 0x00ff);
	merged[1] =  (char)(header.colormapentry & 0x00ff);
	merged[2] =  (char)(header.colormaplength >> 8) & 0x00ff;
	merged[3] =  (char)(header.colormaplength) & 0x00ff;
	merged[4] =  (char)(header.xorigin) & 0x00ff;
	merged[5] =  (char)(header.xorigin >> 8) & 0x00ff;
	merged[6] = (char)(header.yorigin) & 0x00ff;
	merged[7] = (char)(header.yorigin >> 8) & 0x00ff;
	merged[8] = (char)(header.imgwidth >> 8) & 0x00ff;				
	merged[9] = (char)(header.imgwidth) & 0x00ff;	
	merged[10] = (char)(header.imgheight >> 8) & 0x00ff;				
	merged[11] = (char)(header.imgheight) & 0x00ff;

	snprintf(m, 19, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 
		header.idlength,
		header.colormaptype,
		header.imagetype,
		merged[1],
		merged[0],
		merged[3],
		merged[2],
		header.colormapentrysize,
		merged[5],
		merged[4],
		merged[7],
		merged[6],
		merged[9],
		merged[8],
		merged[11],
		merged[10],
		header.pixeldepth,															
		header.imagedescriptor);	
	
	return m;
}

void save_image(char *filename, TGAHeader headout, char* data, int imgSize/*Pixel *imgout*/) {

	FILE *fp = fopen("lol.tga", "w");

	//put header into file
	char *merged = malloc(sizeof(char)*18);
	merged = merge_convert_header(headout, merged);

	fwrite(merged, sizeof(char), 18, fp);
	fwrite(data, sizeof(char), imgSize, fp);

	//put image data into file
	/*int i;

	for (i = 0; i < headout.imgwidth * headout.imgheight; ++i) {
		fwrite(&imgout[i].r, sizeof(char), 1, fp);
		fwrite(&imgout[i].g, sizeof(char), 1, fp);
		fwrite(&imgout[i].b, sizeof(char), 1, fp);
	}*/

	free(merged);
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
	//TGAHeader headout;
	
	load_header(filename, &headin);

	processability(&headin);

	int width = headin.imgwidth;
	int height= headin.imgheight;

	Pixel *imgin;
	Pixel *imgout;
	imgin = malloc(width * height * sizeof(imgin));
	imgout = malloc(width * height * sizeof(imgout));

	load_image(filename, &headin, imgin);

	//const unsigned char headerSize = 18, imgIDSize = 255; 
	//uint32_t colorMapData = (headin.colormapentry * headin.colormaplength) / 8;
	/*uint32_t itr = 0;


	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s", filename);
		exit(EXIT_FAILURE);
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
	
	fclose(fp);*/

 	//convert_grayscale(&headin, imgin, &headout, imgout);
 	//save_image(filename, headout, imgout);

/*
	for (i = 0; i < width * height; i++)
	{
		free_pixel(&imgin[i]);
		free_pixel(&imgout[i]);
	}
*/
	return EXIT_SUCCESS;
}
