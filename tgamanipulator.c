#include "tgamanipulator.h"
#include <string.h>
#include <stdio.h>


const char T_UNCOMPRESSED_B_W = 3;

//Y = 0.299 * R + 0.587 * G + 0.114 * B
//formula source: Espeland, Håvard
int convert_grayscale(int r, int g, int b) {
	int luma = (((int)r * 0.299) + ((int)g * 0.587) + ((int)b * 0.114));
	if (luma > 255) luma = 255;
	return luma;
}

char* merge_convert_header(TGAHeader header, char *m) {
	header.colormaptype = 0;
	header.colormaplength = 0;
	header.colormapentrysize = 0;
	header.imagetype = T_UNCOMPRESSED_B_W;
	header.pixeldepth = 8;

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

void flip_image(char *flip, TGAHeader *header) {
	if(strncmp(flip, "vh", 2) == 0 || strncmp(flip, "hv", 2) == 0) {
		header->xorigin = header->imgwidth;
		header->imagedescriptor ^= 1 << 5;
		header->yorigin = header->imgheight;
		header->imagedescriptor ^= 1 << 4;		
	}
	else if(strncmp(flip, "v", 1) == 0) {
		header->xorigin = header->imgwidth;
		header->imagedescriptor ^= 1 << 5;
	}
	else if(strncmp(flip, "h", 1) == 0) {
		header->yorigin = header->imgheight;
		header->imagedescriptor ^= 1 << 4;
	}
}