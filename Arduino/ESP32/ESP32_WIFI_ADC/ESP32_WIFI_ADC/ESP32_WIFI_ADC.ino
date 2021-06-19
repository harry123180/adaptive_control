//BUG未修! 2021.6.14
/*BUG修復
 * 造成原因:WiFi.h與ADC2發生衝突
 * GPIO33屬於ADC1所以可以正常使用
 * 參考:https://github.com/espressif/arduino-esp32/issues/102
 */
#include "WiFi.h"
const int potPin = 33;
int val=0;
const char* ssid = "iPhone";
const char* password =  "qqqqqqqq";
 
const uint16_t port = 8090;
const char * host = "172.20.10.3";
 
void setup()
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        //return;
    }
 
    //Serial.println("Connected to server successful!");
    
    //client.print("Hello from ESP32!");
    val = analogRead(potPin);
    Serial.println(val);
    client.print(val);
    //Serial.println("Disconnecting...");
    //client.stop();
 
    delay(10);
}
