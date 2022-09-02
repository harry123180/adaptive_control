#include"TFT_eSPI.h"
#include"Free_Fonts.h" //include the header file
TFT_eSPI tft;
int count=0;
void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK); //Black background
 
  tft.setFreeFont(&FreeSansBoldOblique12pt7b); //select Free, Sans, Bold, Oblique, 12pt.
  //tft.drawString("Hello World!",70,80);//prints string at (70,80)
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
 /*
  tft.setFreeFont(FF10); //select Free, Mono, Oblique, 12pt.
  tft.drawString("Mono 12pt",70,110);//prints string at (70,110)
 
  tft.setFreeFont(FS12); //select Free, Serif, 12pt.
  tft.drawString("Serif 12pt",70,140);//prints string at (70,140)
 */
}
void loop() {
  
   //tft.fillScreen(TFT_BLACK); //Black background
   if (digitalRead(WIO_5S_UP) == LOW) {
    count++;
   }
   tft.drawString(String(count),70,80);//prints string at (70,80)
   delay(200);
   //tft.fillScreen(TFT_BLACK); //Black background
   }
  
  
