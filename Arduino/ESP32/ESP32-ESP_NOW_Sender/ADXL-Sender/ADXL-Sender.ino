
#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library
 
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object
long int count =0;
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x09, 0xE8, 0x00};

const int buffer_size = 10;
typedef struct struct_message {
  double x[buffer_size];
  double y[buffer_size];
  double z[buffer_size];//設定自訂義的數據包格式
  int count;
 
} struct_message;

// Create a struct_message called myData
struct_message myData; //宣告一個自訂義數據包格式的變量

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    if(!accel.begin())   // if ASXL345 sensor not found
  {
    Serial.println("ADXL345 not detected");
    while(1);
  }
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  //strcpy(myData.a, "THIS IS A CHAR");
  //myData.b = random(1,20);
  //myData.c = 1.2;
  //myData.d = false;
  for(int i =0;i<buffer_size;i++){
    sensors_event_t event;
    accel.getEvent(&event);
    myData.x[i]=event.acceleration.x;
    myData.y[i]=event.acceleration.y;
    myData.z[i]=event.acceleration.z;
    
  }
  myData.count+=1;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    
    Serial.println("Sent with success");
    
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1);
}
