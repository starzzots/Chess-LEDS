
// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 16
int i = 0;
int color1[] = {0,200,0};
int color2[] = {200,0,200};
int blue[] = {0,0,250};
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
  if (y == 0 || y == 8 ||y == 16 || y == 24){
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
  else if (y == 7 || y == 15 ||y == 23 || y == 31){
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
      pos = matrix3_start + ( x * 8 ) - temp + 7;
    }else { // x is even
      pos = matrix3_start + ( x * 8 ) + temp;
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
      pos = matrix1_start + ( x * 8 ) - temp + 7;
    }else { // x is even
      pos = matrix1_start + ( x * 8 ) + temp;
    }
  }
  return pos;
}
void border(int red, int green, int blue){ 

  for (int rows = 0; rows <= 31; rows++){
    for (int cols = 0; cols <= 31; cols++){
      if (cols % 31 == 0){
        leds[getLEDpos(rows,cols)] = CRGB(red,green,blue);
      }
      if (rows % 31 == 0){
        leds[getLEDpos(rows,cols)] = CRGB(red,green,blue);
      }
    }
  }
}
void square_maker(int *start, int temp1,int temp2, int *color){
  for (int i = start[0]; i <= start[1]; i++){
    for (int j = temp1; j <= temp2; j++){
      leds[getLEDpos(i,j)] = CRGB(color[0],color[1],color[2]);
    }
  }
}
void board(int x, int y){
  int start[] = {0,0};
  int color1[] = {200,0,200};
  int color2[] = {0,200,0};
  
  if (x == 1){
    start[0] = 1;
    start[1] = 4;
  }else if(x == 2){
    start[0] = 5;
    start[1] = 8;
  }else if(x == 3){
    start[0] = 9;
    start[1] = 11;
  }else if(x == 4){
    start[0] = 12;
    start[1] = 15;
  }else if(x == 5){
    start[0] = 16;
    start[1] = 19;
  }else if(x == 6){
    start[0] = 20;
    start[1] = 22;
  }else if(x == 7){
    start[0] = 23;
    start[1] = 26;
  }else if(x == 8){
    start[0] = 27;
    start[1] = 30;
  }
  if (y == 1 && x % 2 == 0){
    square_maker(start,1,4,color1);
  }else if(y == 2 && x % 2 == 0){
    square_maker(start,5,8,color2);
  }else if(y == 3 && x % 2 == 0){
    square_maker(start,9,11,color1);
  }else if(y == 4 && x % 2 == 0){
    square_maker(start,12,15,color2);
  }else if(y == 5 && x % 2 == 0){
    square_maker(start,16,19,color1);
  }else if(y == 6 && x % 2 == 0){
    square_maker(start,20,22,color2);
  }else if(y == 7 && x % 2 == 0){
    square_maker(start,23,26,color1);
  }else if(y == 8 && x % 2 == 0){
    square_maker(start,27,30,color2);
  }else if (y == 1 && x % 2 != 0){
    square_maker(start,1,4,color2);
  }else if(y == 2 && x % 2 != 0){
    square_maker(start,5,8,color1);
  }else if(y == 3 && x % 2 != 0){
    square_maker(start,9,11,color2);
  }else if(y == 4 && x % 2 != 0){
    square_maker(start,12,15,color1);
  }else if(y == 5 && x % 2 != 0){
    square_maker(start,16,19,color2);
  }else if(y == 6 && x % 2 != 0){
    square_maker(start,20,22,color1);
  }else if(y == 7 && x % 2 != 0){
    square_maker(start,23,26,color2);
  }else if(y == 8 && x % 2 != 0){
    square_maker(start,27,30,color1);
  }
}
void row(int x){
  for (int i = 0; i <= 8; i++ ){
    board(x, i);
  }
}
void default_template(){
  row(1);
  row(2);
  row(3);
  row(4);
  row(5);
  row(6);
  row(7);
  row(8);
}
int pieces(){
  //can determine the piece after I get the magnetic reeds working
}
void user_move(int x, int y, int piece, int piece_color, int *color){
  int start[]={0,0};
  int legal_move = 0;
  if (piece == 0 && piece_color == 1){
    legal_move = 1;
    y+=legal_move;
  }
  if (x == 1){
    start[0] = 1;
    start[1] = 4;
  }else if(x == 2){
    start[0] = 5;
    start[1] = 8;
  }else if(x == 3){
    start[0] = 9;
    start[1] = 11;
  }else if(x == 4){
    start[0] = 12;
    start[1] = 15;
  }else if(x == 5){
    start[0] = 16;
    start[1] = 19;
  }else if(x == 6){
    start[0] = 20;
    start[1] = 22;
  }else if(x == 7){
    start[0] = 23;
    start[1] = 26;
  }else if(x == 8){
    start[0] = 27;
    start[1] = 30;
  }
  if (y == 1 && x % 2 == 0){
    square_maker(start,1,4,color);
  }else if(y == 2 && x % 2 == 0){
    square_maker(start,5,8,color);
  }else if(y == 3 && x % 2 == 0){
    square_maker(start,9,11,color);
  }else if(y == 4 && x % 2 == 0){
    square_maker(start,12,15,color);
  }else if(y == 5 && x % 2 == 0){
    square_maker(start,16,19,color);
  }else if(y == 6 && x % 2 == 0){
    square_maker(start,20,22,color);
  }else if(y == 7 && x % 2 == 0){
    square_maker(start,23,26,color);
  }else if(y == 8 && x % 2 == 0){
    square_maker(start,27,30,color);
  }
}

void chess_board_logic(){
  border(255,0,0);
  default_template();
  FastLED.show();
};
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
  chess_board_logic();
}
