#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "Pixel.h"
#include "TGAHeader.h"

TGAHeader load_header(char* filename) {
	TGAHeader header;
	FILE *fptr;

	fptr =  fopen(filename, "r");
	if (!fptr) {
		fprintf(stderr, "Unable to open fptr %s", filename);
		exit(-1);
	}

	//Read the header. 
	//The total size of the header is 18 bytes.
	header.idlength = fgetc(fptr);
	header.colourmaptype = fgetc(fptr);
	header.imagetype = fgetc(fptr);
	fread(&header.colourmaporigin, 2, 1, fptr); //Read 1 member, 2 bytes long
	fread(&header.colourmaplength, 2, 1, fptr);
	header.colourmapdepth = fgetc(fptr);
	fread(&header.xorigin, 2, 1, fptr);
	fread(&header.yorigin, 2, 1, fptr);
	fread(&header.width, 2, 1, fptr);
	fread(&header.height, 2, 1, fptr);
	header.pixeldepth = fgetc(fptr);
	header.imagedescriptor = fgetc(fptr);

	//close/free stuff
	fclose(fptr);
	return header;
}

void malloc_image(Pixel *pixels, TGAHeader header) {
	//Allocate space for image
	if ((pixels = malloc(header.width*header.height*sizeof(Pixel))) == NULL) {
		fprintf(stderr, "malloc of image failed\n");
		exit(-1);
	}
	for (int i = 0; i < header.width*header.height; i++) {
		pixels[i].r = 0;
		pixels[i].g = 0;
		pixels[i].b = 0;
		pixels[i].a = 0;
	}
}

int main(void) {

	//Main burde forenkles til noe slikt
	/*
	uint8_t *inputimg, *outputimg;
	int sizex, sizey;

	inputimg = load_image("image.ppm", &sizex, &sizey);

	outputimg = malloc(sizex * sizey * 4);

	convert_grayscale(inputimg, outputimg, sizex, sizey);

	save_image("output.ppm", outputimg, sizex, sizey);

	*/

	char * filename = "link.tga";

	int bytes2read, skipover = 0;
	TGAHeader header;
	Pixel *pixels;
	
	header = load_header(filename);

	malloc_image(pixels, header);

	/* What we can handle */
   if (header.imagetype != 2 && header.imagetype != 10) {
      fprintf(stderr,"Can only handle image type 2 and 10\n");
      exit(-1);
   }
   if (header.pixeldepth != 16 && 
       header.pixeldepth != 24 && header.pixeldepth != 32) {
      fprintf(stderr,"Can only handle pixel depths of 16, 24, and 32\n");
      exit(-1);
   }
   if (header.colourmaptype != 0 && header.colourmaptype != 1) {
      fprintf(stderr,"Can only handle colour map types of 0 and 1\n");
      exit(-1);
   }

   /* Skip over unnecessary stuff */
   skipover += header.idlength;
   skipover += header.colourmaptype * header.colourmaplength;
   fprintf(stderr,"Skip over %d bytes\n",skipover);
   //fseek(fptr,skipover,SEEK_CUR);   

   /* Read the image */


	//Free pixels

	return EXIT_SUCCESS;
}
