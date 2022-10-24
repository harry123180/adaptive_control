#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_ADS1X15.h>
#include <Servo.h> 
Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
Servo myservo;
int servo_pin=18;
int pos = 0;    // 定義舵機轉動位置
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0x89, 0xAF, 0x38};
int cnt =0;
bool befor_state = false;
int timer =0;
#define btn_pin 13
#define bee_pin 25
#define led_pin 14

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int16_t results;
  bool btn_state;
  int angle;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void cutt(bool cut_state){
   if(myData.btn_state){
    timer = timer+1;
    if(timer>10){
      tone(bee_pin, 262, 500);
    }
    if(cnt%2==0){
      myservo.write(0);
    }
    else if(cnt%2!=0){
      myservo.write(57);
    }
   myData.angle=0;
  }
  else if (!(myData.btn_state)){
    timer = 0;
    Serial.println("relaxing");
    myData.angle=57;
  }
}
void setup() {
  Serial.begin(115200);
   if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  pinMode(bee_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(btn_pin,INPUT_PULLUP);
  myservo.attach(servo_pin);  // 設置舵機控制腳位
  myservo.write(57);//57度放鬆
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
void loop() {
  myData.results = ads.readADC_Differential_0_1();
  myData.btn_state = digitalRead(btn_pin);
  digitalWrite(led_pin,myData.btn_state);
  Serial.println(myData.btn_state);
  if(myData.btn_state && !befor_state){
    cnt++;
  }
  cutt(myData.btn_state);
  befor_state = myData.btn_state;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(1000);
}
