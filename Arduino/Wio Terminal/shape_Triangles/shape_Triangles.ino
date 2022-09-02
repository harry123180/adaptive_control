#include"TFT_eSPI.h"
TFT_eSPI tft;
 int i=0;
void setup() {
    tft.begin();
    tft.setRotation(3);
 
    tft.fillScreen(TFT_WHITE); //Red background
    tft.drawTriangle(160,70,60,170,260,170,TFT_BLACK);
    //A triangle with points at (160, 70), (60, 170) and (260, 170)
}
 
void loop() {
  
  if(i>400)i=0;
  i++;
  //tft.fillScreen(TFT_WHITE); //Red background
  tft.drawTriangle(160+i,70,60,170,260,170,TFT_BLACK);
  delay(10);
  tft.drawTriangle(160+i,70,60,170,260,170,TFT_WHITE);
  
  }
