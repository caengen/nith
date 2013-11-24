#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include "Pixel.h"
#include "TGAHeader.h"

void save_image(char *, TGAHeader, char *, int, char *);

//Can we process the current img
void evaluate_image(char imagetype) {
	if (imagetype != 2) {
		fprintf(stderr, "The image type is not supported.");
		exit(EXIT_FAILURE);
	}
}

int convert_grayscale16(int g, int a) {
	return (int)(g * (255 / a));
}

//Y = 0.299 * R + 0.587 * G + 0.114 * B
int convert_grayscale24(int r, int g, int b) {
	int luma = (((int)r * 0.299) + ((int)g * 0.587) + ((int)b * 0.114));
	if (luma > 255) luma = 255;
	return luma;
}

/* 
* ConversionFactor = 255 / (NumberOfShades - 1)
* AverageValue = (Red + Green + Blue) / 3
* Gray = Integer((AverageValue / ConversionFactor) + 0.5) * ConversionFactor
* source: http://www.tannerhelland.com/3643/
*/
int convert_grayscale32(int r, int g, int b, int a) {
	double avgval = convert_grayscale24(r, g, b);
	return (int)(avgval * 255/a);
}

unsigned int getFileSize(FILE *file) {
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

const char COLOR_MAPPED = 1;
const char UNCOMPRESSED = 2;
const char UNCOMPRESSED_B_W = 3;
const char RLE_COLOR_MAPPED = 9;
const char RLE_UNCOMPRESSED = 10;
const char RLE_MAPPED_B_W = 11;
void load_image(char *filename, TGAHeader *header) {
	if (!header) {
		fprintf(stderr, "Non-valid TGAHeader argument\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s\n", filename);
		exit(EXIT_FAILURE);
	}

	unsigned int colormapsize, imgsize, imgdatasize, filesize, headsize = 18, footsize = 26;
	char *imgid, *imgmap, *imgbuf, *footer, *grayscaleimg;
	int i;
	unsigned char r, g, b, a;

	filesize = getFileSize(fp);

	colormapsize = header->colormaplength * header->colormapentrysize / 8;
	imgsize = header->imgheight * header-> imgwidth;
	imgdatasize = filesize - (headsize + footsize + header->idlength + colormapsize);

	imgid = malloc(256 * sizeof(char));
	imgmap = malloc(colormapsize * sizeof(char));
	imgbuf = malloc(imgdatasize * sizeof(char));
	footer = malloc(footsize * sizeof(char));
	grayscaleimg = malloc(imgsize * sizeof(char));

	fseek(fp, headsize, SEEK_SET);
	if (header->idlength > 0) {
		fread(imgid, sizeof(char), header->idlength, fp);
		printf("%s\n", imgid);
	}
	fread(imgmap, sizeof(char), colormapsize, fp);
	fread(imgbuf, sizeof(char), imgdatasize, fp);
	fread(footer, sizeof(char), footsize, fp);

	if (header->pixeldepth == 16) {
		for (i = 0; i < imgsize; i++) {
			g = imgbuf[i * 2];
			a = imgbuf[i * 2 + 1];
			grayscaleimg[i] = convert_grayscale16(g, a);
		}		
	}
	else if (header->pixeldepth == 24) {	
		for (i = 0; i < imgsize; i++) {
			r = imgbuf[i * 3];
			g = imgbuf[i * 3 + 1];
			b = imgbuf[i * 3 + 2];
			grayscaleimg[i] = convert_grayscale24(r, g, b);
		}
	} else if(header->pixeldepth == 32) {
		for (i = 0; i < imgsize; i++) {
			r = imgbuf[i * 4];
			g = imgbuf[i * 4 + 1];
			b = imgbuf[i * 4 + 2];
			a = imgbuf[i * 4 + 3];
			//
			grayscaleimg[i] = convert_grayscale32(r, g, b, a);
		}		
	}

	save_image(filename, *header, grayscaleimg, imgsize, imgid);
	
	free(imgid);
	free(imgmap);
	free(imgbuf);
	free(footer);
	free(grayscaleimg);
	fclose(fp);
}

short fread_smallendian(FILE *fp) {
	short right = fgetc(fp) & 0x00ff;
	short left = (fgetc(fp) << 8) & 0xff00;

	return right | left;
}

void load_header(char* filename, TGAHeader *header) {
	FILE *fp;

	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s\n", filename);
		exit(EXIT_FAILURE);
	}

	//Read the header. 
	//The total size of the header is 18 bytes.
	header->idlength = fgetc(fp);
	header->colormaptype = fgetc(fp);
	header->imagetype = fgetc(fp);
	header->colormapentry = fread_smallendian(fp);
	header->colormaplength = fread_smallendian(fp);
	header->colormapentrysize = fgetc(fp);
	header->xorigin = fread_smallendian(fp);
	header->yorigin = fread_smallendian(fp);
	header->imgwidth = fread_smallendian(fp);
	header->imgheight = fread_smallendian(fp);
	header->pixeldepth = fgetc(fp);
	header->imagedescriptor = fgetc(fp);

	fclose(fp);
}

char* merge_convert_header(TGAHeader header, char *m) {
	header.colormaptype = 0;
	header.colormaplength = 0;
	header.colormapentrysize = 0;
	header.imagetype = UNCOMPRESSED_B_W;
	header.pixeldepth = 8;

	//endre til variabler
	char cme_r =  (header.colormapentry >> 8) & 0x00ff;
	char cme_l =  header.colormapentry & 0x00ff;
	char cml_r =  (header.colormaplength >> 8) & 0x00ff;
	char cml_l =  header.colormaplength & 0x00ff;
	char xo_r =  header.xorigin & 0x00ff;
	char xo_l =  (header.xorigin >> 8) & 0x00ff;
	char yo_r = header.yorigin & 0x00ff;
	char yo_l = (header.yorigin >> 8) & 0x00ff;
	char iw_r = (header.imgwidth >> 8) & 0x00ff;
	char iw_l = header.imgwidth & 0x00ff;
	char ih_r = (header.imgheight >> 8) & 0x00ff;
	char ih_l = header.imgheight & 0x00ff;

	snprintf(m, 19, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 
		header.idlength, header.colormaptype, header.imagetype,
		cme_l, cme_r,
		cml_l, cml_r,
		header.colormapentrysize,
		xo_l, xo_r,
		yo_l, yo_r,
		iw_l, iw_r,
		ih_l, ih_r,
		header.pixeldepth,															
		header.imagedescriptor);	
	
	return m;
}

void save_image(char *filename, TGAHeader header, char* imgout, int imgSize, char *imageid) {

	char newfilename[128];
	char *fileprefix = "grayscale_";
	snprintf(newfilename, sizeof(newfilename), "%s%s", fileprefix, filename);

	FILE *fp = fopen(newfilename, "w");
	if (!fp) {
		fprintf(stderr, "Unable to create/overwrite file %s\n", newfilename);
	}

	char *merged = malloc(sizeof(char)*18);
	merged = merge_convert_header(header, merged);

	fwrite(merged, sizeof(char), 18, fp);
	if (header.idlength > 0) fwrite(imageid, sizeof(char), header.idlength, fp);
	fwrite(imgout, sizeof(char), imgSize, fp);

	free(merged);
	fclose(fp);
}

int main(int argc, char **argv) {

	TGAHeader header;
	
	load_header(argv[1], &header);

	evaluate_image(header.imagetype);

	load_image(argv[1], &header);

	return EXIT_SUCCESS;
}
