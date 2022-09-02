#include"TFT_eSPI.h"
TFT_eSPI tft;
 int i=0;
 int x=0;
 int y=0;
void setup() {
    tft.begin();
    tft.setRotation(3);
    Serial.begin(115200);
    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    tft.fillScreen(TFT_WHITE); //Red background
    tft.drawTriangle(160,70,60,170,260,170,TFT_BLACK);
    //A triangle with points at (160, 70), (60, 170) and (260, 170)
    
}
 
void loop() {
  if (digitalRead(WIO_5S_UP) == LOW) {
    y--;
    Serial.println("5 Way Up");
   }
   else if (digitalRead(WIO_5S_DOWN) == LOW) {
    Serial.println("5 Way Down");
    y++;
   }
   else if (digitalRead(WIO_5S_LEFT) == LOW) {
    Serial.println("5 Way Left");
    x--;
   }
   else if (digitalRead(WIO_5S_RIGHT) == LOW) {
    Serial.println("5 Way Right");
    x++;
   }
   
  if(i>400)i=0;
  i++;
  //tft.fillScreen(TFT_WHITE); //Red background
  tft.drawTriangle(160+x,70+y,60+x,170+y,260+x,170+y,TFT_BLACK);
  delay(10);
  tft.drawTriangle(160+x,70+y,60+x,170+y,260+x,170+y,TFT_WHITE);
  
  }
