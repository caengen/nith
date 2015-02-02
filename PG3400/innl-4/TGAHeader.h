#pragma once

typedef struct {
   char  idlength;
   char  colormaptype;
   char  imagetype;
   /* Color map specification 5 bytes */
   short colormapentry;
   short colormaplength;
   char  colormapentrysize;
   /* Image specification 10 bytes */
   short xorigin;
   short yorigin; 
   short imgwidth;
   short imgheight;
   char  pixeldepth;
   char  imagedescriptor;
} TGAHeader;