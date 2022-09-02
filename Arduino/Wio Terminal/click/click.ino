#include"TFT_eSPI.h"
TFT_eSPI tft;
 
void setup() {
  tft.begin();
  tft.setRotation(3);
}
 
void loop() {
    //Looping through color R-G-B
    tft.fillScreen(TFT_RED);
    delay(10);
    digitalWrite(LCD_BACKLIGHT, LOW); // turn on the backligh
    digitalWrite(LCD_BACKLIGHT, HIGH); // turn on the backligh
    tft.fillScreen(TFT_GREEN);
    delay(10);
    digitalWrite(LCD_BACKLIGHT, LOW); // turn on the backligh
    digitalWrite(LCD_BACKLIGHT, HIGH); // turn on the backligh
    tft.fillScreen(TFT_BLUE);
    delay(10);
    digitalWrite(LCD_BACKLIGHT, LOW); // turn on the backligh
    digitalWrite(LCD_BACKLIGHT, HIGH); // turn on the backligh
}
 
