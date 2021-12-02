#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_now.h>
uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x29, 0x41, 0x64};
//set SDA =ESP32 D21
//set SCL =ESP32 D22
int P =23;
int last_state = HIGH;
bool chose = false;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
typedef struct struct_message {
  bool msg;
} struct_message;
struct_message myData;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  WiFi.mode(WIFI_STA);

// Init ESP-NOW
if (esp_now_init() != ESP_OK) {
  Serial.println("Error initializing ESP-NOW");
  return;
}
esp_now_register_send_cb(OnDataSent);
  
// Register peer
esp_now_peer_info_t peerInfo;
memcpy(peerInfo.peer_addr, broadcastAddress, 6);
peerInfo.channel = 0;  
peerInfo.encrypt = false;

// Add peer        
if (esp_now_add_peer(&peerInfo) != ESP_OK){
  Serial.println("Failed to add peer");
  return;
}
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
pinMode(P, INPUT);
Serial.begin(115200);
}

void loop()
{
int button_state =digitalRead(P);
Serial.println(button_state);
if(button_state ==LOW and last_state ==HIGH){
 if(chose){
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Button is pressed");
  display.display();
 }
  else if(!chose){
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Button is relaxing");
  display.display();
 }
 myData.msg = chose;
 chose = !chose;
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
}

last_state = button_state;
}
