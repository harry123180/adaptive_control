#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int16_t results;
  bool btn_state;
  int angle;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print(myData.results);
  Serial.print(" ");
  Serial.print(myData.btn_state);
  Serial.print(" ");
  Serial.println(myData.angle);
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {

}
