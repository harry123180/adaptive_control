#include"TFT_eSPI.h"
TFT_eSPI tft;
#include"Free_Fonts.h" //include the header file
void setup() {
  pinMode(WIO_BUZZER, OUTPUT);
  Serial.begin(115200);
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  
  tft.begin();
  tft.setRotation(3);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft.fillScreen(TFT_BLACK);
   tft.setFreeFont(&FreeSansBoldOblique12pt7b); //select Free, Sans, Bold, Oblique, 12pt.
  tft.drawString("Sans Serif 12pt",70,80);//prints string at (70,80)
 
  tft.setFreeFont(FF10); //select Free, Mono, Oblique, 12pt.
  tft.drawString("Mono 12pt",70,110);//prints string at (70,110)
 
  tft.setFreeFont(FS12); //select Free, Serif, 12pt.
  tft.drawString("Serif 12pt",70,140);//prints string at (70,140)
}
 
void loop() {
  // put your main code here, to run repeatedly:
   if (digitalRead(WIO_KEY_A) == LOW) {
    Serial.println("A Key pressed");
    analogWrite(WIO_BUZZER, 130);
   }
   else if (digitalRead(WIO_KEY_B) == LOW) {
    Serial.println("B Key pressed");
    analogWrite(WIO_BUZZER, 0);
   }
   else if (digitalRead(WIO_KEY_C) == LOW) {
    Serial.println("C Key pressed");
   }
   delay(200);
}
