typedef struct {
   char  idlength;        //1 byte
   char  colormaptype;    //1 byte
   char  imagetype;       //1 byte
   /* Color map specification 5 bytes */
   short colormapentry;   //2 bytes
   short colormaplength;  //2 bytes
   char  colormapentrysize;  //1 byte
   /* Image specification 10 bytes */
   short xorigin;         //2 bytes
   short yorigin;         //2 bytes
   short imgwidth;        //2 bytes
   short imgheight;       //2 bytes
   char  pixeldepth;      //1 byte
   char  imagedescriptor; //1 byte
} TGAHeader;