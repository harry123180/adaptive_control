#include <WiFi.h>
#include <WiFiAP.h>
#include <Wire.h>
#include <Adafruit_SH1106.h>
#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SH1106 display(OLED_SDA, OLED_SCL);
char print_buf[20];
char print_buf2[20];
const char* ssid = "iot";
const char* passphrase = "00000000";
IPAddress local_ip(192,168,100,1);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);
WiFiAPClass WiFiAP;
void setup() {
  Serial.begin(115200);
  setupAP();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
}
 
void loop() {

  display.setTextSize(0.1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  sprintf(print_buf,"connect device: %d",  WiFiAP.softAPgetStationNum());
  display.println(print_buf);
  display.setCursor(0,10);
  display.println("AP Mobile Tool Ver1.0");
  display.display();
  delay(2000);
  display.clearDisplay();
}
 
void setupAP(void) {
  WiFi.softAP(ssid, passphrase, 6);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  Serial.println("run softap");
  
}
