#include <stdio.h>
#include <stdlib.h>
#include "filehandler.h"
#include "TGAHeader.h"
#include "utils.h"
#include "tgamanipulator.h"

void load_header(char* filename, TGAHeader *header) {
	FILE *fp;

	fp =  fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open fp %s\n", filename);
		exit(EXIT_FAILURE);
	}

	//Read the header.
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

const char UNCOMPRESSED_B_W = 3;
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
	unsigned char r, g, b;

	filesize = get_filesize(fp);

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

	if (header->pixeldepth == 24) {	
		for (i = 0; i < imgsize; i++) {
			r = imgbuf[i * 3];
			g = imgbuf[i * 3 + 1];
			b = imgbuf[i * 3 + 2];
			grayscaleimg[i] = convert_grayscale(r, g, b);
		}
	} else if(header->pixeldepth == 32) {
		for (i = 0; i < imgsize; i++) {
			r = imgbuf[i * 4];
			g = imgbuf[i * 4 + 1];
			b = imgbuf[i * 4 + 2];
			grayscaleimg[i] = convert_grayscale(r, g, b);
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