#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
typedef struct struct_message {
    bool d;
} struct_message;
struct_message myData;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int P =23;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.d);
}
 
void setup() {
  pinMode(P, OUTPUT);
  // Initialize Serial Monitor
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
}
 
void loop() {
digitalWrite(P,myData.d);
  display.clearDisplay();
  display.setCursor(0, 10);
  if(myData.d){
    display.println("Fan");
    display.println("START");
  }
  else if(!myData.d){
    display.println("Fan");
    display.println("STOP");
  }
  display.display();
}
