typedef struct {

   char  idlength;            //1 byte
   char  colormaptype;       //1 byte
   char  imagetype;           //1 byte
   /* Color map specification 5 bytes */
   short int colormapentry;   //2 bytes
   short int colormaplength;  //2 bytes
   char  colourmapentrysize;  //1 byte
   /* Image specification 10 bytes */
   short int xorigin;         //2 bytes
   short int yorigin;         //2 bytes
   short int imgwidth;        //2 bytes
   short int imgheight;       //2 bytes
   char  pixeldepth;          //1 byte
   char  imagedescriptor;     //1 byte
} TGAHeader;