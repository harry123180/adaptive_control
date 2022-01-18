#define DAC1 25
#define DAC2 26
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  

}

void loop() { // Generate a Sine wave
  int Value = 100; //255= 3.3V 128=1.65V

  dacWrite(DAC1, Value-5);
  dacWrite(DAC2, 0);
  //digitalWrite(DAC2,LOW);
 //  display.clearDisplay();
 // display.setCursor(0, 10);
 // display.println("V="+String(i));
  //display.display();
  delay(3000);
  dacWrite(DAC1, 0);
  dacWrite(DAC2, Value-10);
  delay(3000);
  }
