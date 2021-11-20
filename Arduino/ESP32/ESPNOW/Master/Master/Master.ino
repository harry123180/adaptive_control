
#include <esp_now.h>
#include <WiFi.h>

// 放入接收器的MAC地址
uint8_t broadcastAddress1[] = {0xC4, 0x4F, 0x33, 0x7C, 0x56, 0x45};
uint8_t broadcastAddress2[] = {0xAC, 0x67, 0xB2, 0x29, 0x41, 0x64};
//uint8_t broadcastAddress3[] = {0x7C, 0x9E, 0xBD, 0x09, 0xE8, 0x00};

String cmd_msg;
int i =0;
typedef struct test_struct {
  int x;
  String y = "No";
} test_struct;

test_struct test;

// 數據發送時回調
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // 將發件人mac地址複製到一個字符串
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  /*
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  */
}
 
void loop() {
  test.x = random(0,20);
  i++;
  test.y = String(i);
  /*
  if(Serial.available() > 0)
     {
       cmd_msg = Serial.readStringUntil('\n');
       Serial.print("your input = ");
       test.y = cmd_msg;
       Serial.println(cmd_msg);
     }
     */
  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   /*
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }*/
  delay(1000);
}
