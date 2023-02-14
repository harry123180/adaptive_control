/* ESP01 is ESP8266 Core
*
*
*/
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;
float gForceX, gForceY, gForceZ;
float orgdata[3][150];
// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x84, 0xF7, 0x03, 0x7B, 0x1A, 0x1A};

typedef struct struct_message {
    int axis;//0=X 1=Y 2=Z
    int index;//0,60,120 一段傳60個float 分3次傳
    float data[50];
} struct_message;
struct_message myData;

void dataReceiver(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  processData();
}
void processData(){
  gForceX = AcX / 16384.0;
  gForceY = AcY / 16384.0; 
  gForceZ = AcZ / 16384.0;
}
void debugFunction(int16_t AcX, int16_t AcY, int16_t AcZ,uint8_t i){
  orgdata[0][i]=gForceX;
  orgdata[1][i]=gForceY;
  orgdata[2][i]=gForceZ;
  /*
  Serial.print(i);
  Serial.print(" ");
  Serial.print(orgdata[0][i]);
  Serial.print(" ");
  Serial.print(orgdata[1][i]);
  Serial.print(" ");
  Serial.println(orgdata[2][i]);  
  */
}
// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  //Serial.begin(115200);
  Wire.begin(0,2);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  for(int i=0;i<150;i++){
  dataReceiver();
  debugFunction(AcX,AcY,AcZ,i);
  }
  delay(20);
  for(int j=0;j<3;j++){
    for(int q=0;q<3;q++){
      for(int k=0;k<50;k++){
        myData.axis=j;
        myData.index =q*50;
        myData.data[k]=orgdata[j][q*50+k];  
      }
      
      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    }
    
  delay(20);
  }
}
