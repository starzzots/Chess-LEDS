/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

#include <FastLED.h>
#include <math.h>
// How many leds in your strip?
#define NUM_LEDS 256*4
#define BRIGHTNESS  5

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 16
int i = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];
//can definitly scale this somehow to account for more than 4 matrix'x will come back to later
int getLEDpos(int x, int y){ // for a serpentine raster
  int pos;
  int temp=0;
  //topleft starts of the matrix
  int matrix1_start = 0;
  int matrix2_start = 504;
  int matrix3_start = 512;
  int matrix4_start = 1016;
  if (y == 0 ||y == 8 ||y == 16 || y == 24){
    temp = 0;
  }
  else if (y == 1 ||y == 9 ||y == 17 || y == 25){
    temp = 1;
  }
  else if (y == 2 ||y == 10 ||y == 18 || y == 26){
    temp = 2;
  }
  else if (y == 3 ||y == 11 ||y == 19 || y == 27){
    temp = 3;
  }
  else if (y == 4 ||y == 12 ||y == 20 || y == 28){
    temp = 4;
  }
  else if (y == 5 ||y == 13 ||y == 21 || y == 29){
    temp = 5;
  }
  else if (y == 6 ||y == 14 ||y == 22 || y == 30){
    temp = 6;
  }
  else if (y == 7 ||y == 15 ||y == 23 || y == 31){
    temp = 7;
  }
  //in matrix4 even matrix equations are the same just different starts 
  if (y >= 0 && y <= 7){
    if(x & 0x1) { // is X odd
      pos = matrix4_start - ( x * 8 ) + 7 - temp;
    }else { // x is even
      pos = matrix4_start - ( x * 8 ) + temp;
    } 
  }
  //matrix3 odd matrix equations are the same
  else if (y >= 8 && y <= 15){
    if(x & 0x1) { // is X odd
      pos = matrix3_start + ( x * 8 ) + 7 + temp;
    }else { // x is even
      pos = matrix3_start + ( x * 8 ) - temp;
    }
  }
  //matrix2
  else if (y >= 16 && y <= 23){
    if(x & 0x1) { // is X odd
      pos = matrix2_start - ( x * 8 ) + 7 - temp;
    }else { // x is even
      pos = matrix2_start - ( x * 8 ) + temp;
    }
  }
  //matrix1
  else if (y >= 24 && y <= 31){
    if(x & 0x1) { // is X odd
      pos = matrix1_start + ( x * 8 ) + 7 + temp;
    }else { // x is even
      pos = matrix1_start + ( x * 8 ) - temp;
    }
  }
  return pos;
}



void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.setBrightness(BRIGHTNESS);
}
  

void loop() { 
  // //matrix 1, x = 0 (0,7)
  // //matrix 2, x = 0 (504-511)
  // //matrix 3, x = 0 (512,519)
  // //matrix 4, x = 0 (1016,1024)
  //testing grounds LOLOLOL :D
  leds[getLEDpos(16,16)] = CRGB(100,200,100);
  leds[getLEDpos(17,16)] = CRGB(100,200,100);
  leds[getLEDpos(18,16)] = CRGB(100,200,100);
  leds[getLEDpos(19,16)] = CRGB(100,200,100);
  leds[getLEDpos(16,17)] = CRGB(100,200,100);
  leds[getLEDpos(16,18)] = CRGB(100,200,100);
  leds[getLEDpos(16,19)] = CRGB(100,200,100);
  leds[getLEDpos(17,19)] = CRGB(100,200,100);
  leds[getLEDpos(18,19)] = CRGB(100,200,100);
  leds[getLEDpos(19,19)] = CRGB(100,200,100);
  leds[getLEDpos(19,18)] = CRGB(100,200,100);
  leds[getLEDpos(19,17)] = CRGB(100,200,100);
  leds[getLEDpos(18,17)] = CRGB(100,200,100);
  leds[getLEDpos(17,17)] = CRGB(100,200,100);
  leds[getLEDpos(18,18)] = CRGB(100,200,100);
  leds[getLEDpos(17,18)] = CRGB(100,200,100);


  FastLED.show();
}
