#include "LedControl.h"

/* BYTE ARRAY TABLE */

/* Binary byte arrays for english alphabet. 
 * Each array corresponds to the variable name character 
 */
byte a[6]={B00000000,B00000000,B00101110,B00101010,B00011110,B00000000};
byte b[6]={B00000000,B00000000,B01111110,B00001010,B00001110,B00000000};    
byte c[6]={B00000000,B00011100,B00100010,B00100010,B00000000,B00000000};
byte d[6]={B00000000,B00001100,B00010010,B00010010,B01111110,B00000000};
byte e[6]={B00000000,B00011100,B00101010,B00101010,B00110000,B00000000};
byte f[6]={B00000000,B00001000,B00011110,B00101000,B00100000,B00000000};
byte g[6]={B00000000,B00010000,B00101010,B00101010,B00011100,B00000000};
byte h[6]={B00000000,B00000000,B00111110,B00001000,B00001110,B00000000};
byte i[6]={B00000000,B00000000,B00100010,B10111110,B00000010,B00000000};
byte j[6]={B00000000,B00000010,B00100010,B10111100,B00000000,B00000000};
byte k[6]={B00000000,B00000000,B01111110,B00010000,B00101110,B00000000};
byte l[6]={B00000000,B00000000,B01000010,B01111110,B00000010,B00000000};
byte m[6]={B00000000,B00011110,B00010000,B00001110,B00010000,B00001110};
byte n[6]={B00000000,B00111110,B00010000,B00100000,B00100000,B00011110};
byte o[6]={B00000000,B00011100,B00100010,B00100010,B00011100,B00000000};
byte p[6]={B00000000,B00000000,B00111110,B00101000,B00111000,B00000000};
byte q[6]={B00000000,B00000000,B00111000,B00101000,B00111110,B00000000};
byte r[6]={B00000000,B00111110,B00010000,B00100000,B00100000,B00010000};
byte s[6]={B00000000,B00111010,B00101010,B00101110,B00000000,B00000000};
byte t[6]={B00000000,B00010000,B01111110,B00010010,B00000000,B00000000};
byte u[6]={B00000000,B00111100,B00000010,B00000010,B00000100,B00111110};
byte v[6]={B00000000,B00000000,B00111100,B00000010,B00111100,B00000000};
byte w[6]={B00000000,B00111100,B00000010,B00001100,B00000010,B00111100};
byte x[6]={B00000000,B00100010,B00010100,B00001000,B00010100,B00100010};
byte y[6]={B00000000,B00000000,B00111000,B00000110,B00111000,B00000000};
byte z[6]={B00000000,B00100100,B00101100,B00110100,B00100100,B00000000};
byte space[6]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

/* CONST VALUES */

/* We need to know the max size of the byteString variable.
 * Increasing the value of inDataSize will allow the program
 * to read longer character strings from the Serial terminal.
 */
const int inDataSize = 20;
/* The number of rows in a single byte array of a character */
const int numOfRows = 6;
/* The size of the matrix being drawn on the LED display.
 * Do not increase above 8 and no negative values allowed.*/
const int matrixSize= 8;
const int alphabetSize = 26;
/* The number we use to find the appropriate array index for
 * a character. E.g., the character 'a' has a decimal value
 * of 97. So the substraction 97 - 97 yields the array index
 * of 0 which is where we have placed our byte array for 'a'.
 * @see http://www.asciitable.com/
 */
const int smallCharToArrayPos = 97;

/* VARIABLES */

/*
 * Now we need a LedControl to work with.
 * pin 12 is connected to the DataIn 
 * pin 11 is connected to the CLK 
 * pin 10 is connected to LOAD 
 * We are only using one MAX7219
 */
LedControl lc=LedControl(12,11,10,1);

/* A short delay between matrix updates to simulate scrolling 
 */
unsigned long delaytime=100;

/* An array of pointers to the byte arrays. 
 */
byte* alphabet[alphabetSize] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
/* We store the string of characters read from Serial in this variable. 
 * byteString is initialized to space, which will turn no LEDs on, on the matrix.
 */
byte* byteString[inDataSize] = { space };
/* To create a scrolling effect we draw to the LED matrix using this variable. 
 * Then we gradually add character arrays from byteString into it. This allows us to have 
 * data from two (or more) character arrays on the matrix at the same time.
 */
byte matrix[matrixSize] = {B00000000};

/* FUNCTIONS */
 
 /* User input is read from Serial using the Serial.read() function
 */
char* serialRead(void) {
  char inData[inDataSize];
  char inChar;
  byte index = 0;
  
  //We read from Serial while there is data available
  while (Serial.available() > 0) {
    //We make sure we don't store values outside of our array
    if (index < inDataSize - 1) {
      inChar = Serial.read();
      inData[index] = inChar;
      /* Each time we add a character we also add a \0 at the end.
       * This is good practice because we now can stop our loop
       * at anytime and our char array will still be a valid string.
       */
      index++;
      inData[index] = '\0';
    }
  }
  return inData;
}

void buildByteString(char* string) {
  /* byteString is built up depending on the characters written.
   * The characters are being substracted by 97 (see smallCharToArrayPos)
   * to find the characters position in the alphabet array. The byte character
   * arrays are then being added to byteString as pointers.
   */
  for (int i = 0; i < inDataSize; i++) {
    if (string[i]-smallCharToArrayPos > alphabetSize-1 || string[i]-smallCharToArrayPos < 0) {
      byteString[i]=space;
    } else {
      byteString[i] = alphabet[string[i]-smallCharToArrayPos];
    }
  }  
}


/* This function will display the characters for the
 * written word one after the other on the matrix. 
 */
void writeToMatrix() {
  
  char* string = serialRead();
  
  buildByteString(string);
  
  /* now display them one by one with a small delay */
  for(int in = 0; in < inDataSize; ++in) {
    //iterate through character rows
    for(int jn = 0; jn < numOfRows; ++jn) {
      //insert byte row from "text" into matrix end
      matrix[(matrixSize-1)] = byteString[in][jn];  
      
      //display matrix to led8x8 matrix
      for (int kn = 0; kn < matrixSize; kn++) {
        lc.setRow(0, kn, matrix[kn]);
      }
      delay(delaytime);
      
      //shift entire matrix one row to the left
      for(int kn = 0; kn < matrixSize - 1; kn++) {
        matrix[kn] = matrix[kn+1]; 
      }
      matrix[matrixSize-1] = B00000000;
    }
  }
}

void setup() {
  /* The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  
  //Begin serial monitoring
  Serial.begin(9600);
  Serial.write("Begin  by writing a string of characters. They will be displayed on the LED 8x8 Matrix\n");
  Serial.write("This software reads all the data provided by Serial.read() and translates that data to\n");
  Serial.write("characters on the 8x8 LED matrix. This can result in  some unexpected characters being\n");
  Serial.write("shown on the matrix. However, your entered message should be shown after a short delay,\n");
  Serial.write("as   long as your  character string  is  less than the value  specified  in inDataSize.\n");
}

void loop() {
    writeToMatrix();
}
