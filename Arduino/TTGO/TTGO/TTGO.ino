#include <TFT_eSPI.h>        //LCD函式庫
#include <Button2.h>        //Button2函式庫
#include<WiFi.h>
#include <Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;
float gForceX, gForceY, gForceZ;
float orgdata[3][128];
float ireserX,ireserY,ireserZ;

const char ssid[]="SHC"; //修改為你家的WiFi網路名稱
const char pwd[]="datadata"; //修改為你家的WiFi密碼

TFT_eSPI tft = TFT_eSPI(); 
#define BUTTON_A_PIN  0  //按鍵A，PIN 0
#define BUTTON_B_PIN  35 //按鍵B，PIN 35
Button2 buttonA = Button2(BUTTON_A_PIN);
Button2 buttonB = Button2(BUTTON_B_PIN);
short int page=0;//儲存當前頁數
#include "img1.h"   //載入兩個圖檔，已轉C Array
#include "img2.h"
#include "STUST.h"

void dataReceiver(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,16,true);  // request a total of 16 registers
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
void taskOne( void * parameter ){
  while(1){
    for(int i=0;i<128;i++){
    dataReceiver();
    debugFunction(AcX,AcY,AcZ,i);
    }
  }
  Serial.println("Ending task 1");
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  while(1){
   
    Page_Manager(page);
    //Serial.print("page = ");
    //Serial.println(page);
  }
  Serial.println("Ending task 2");
  vTaskDelete( NULL );
}
void initial_event(){
  Serial.begin(115200);
  tft.begin();               // 初始化LCD
  tft.setRotation(1);  // landscape
  tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕
  tft.setSwapBytes(true);
  Serial.println("display STUST");
  buttonA.setPressedHandler(press);   //建立A按鍵按下Pressed的事件
  buttonA.setReleasedHandler(release);//建立A按鍵放開Released的事件
  buttonB.setPressedHandler(press);   //建立B按鍵按下Pressed的事件
  buttonB.setReleasedHandler(release);//建立B按鍵放開Released的事件
  Serial.println("Set up Complete");
  WiFi.mode(WIFI_STA); //設置WiFi模式
  
  WiFi.begin(ssid,pwd); 
  Wire.begin(21,22);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void RTOS_Setup(){
   xTaskCreatePinnedToCore(
  taskOne, //本任務實際對應的Function
  "TaskOne", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  1, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  1); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）

  xTaskCreatePinnedToCore(
  taskTwo, //本任務實際對應的Function
  "taskTwo", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  0); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）
}
void Page_Manager(int page){
  switch (page) {
    case 0:
      page0();
      //Serial.println("do page0");
      break;
    case 1:
      page1();
      //Serial.println("do page1");
      break;
    case 2:
      page2();
      //Serial.println("do page2");
      break;
    case 3:
      page3();
      //Serial.println("do page3");
      break;
  }
}
void setup()
{
  initial_event();
  RTOS_Setup();
}

void loop()
{
    buttonA.loop();  //重複按鍵的觸發設定
    buttonB.loop(); //一定要放在loop()裡面
}

void press(Button2& btn) {
    page++;
    Serial.println("press");
    if(page>3)page=0;
}

void release(Button2& btn) {
    Serial.println("release");
}
const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}
void page0(){
  tft.pushImage(0, 0, 240, 135, STUST);  //顯示圖檔STUST
}
void page1(){
  char buf[10];
  tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕
  tft.setFreeFont(&FreeSerifBold12pt7b);                            
  tft.setCursor(0, 20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.printf("Page1");
  tft.setCursor(0, 50);
  tft.printf(wl_status_to_string(WiFi.status()));
  tft.setCursor(0, 80);
  tft.printf(WiFi.localIP().toString().c_str());
  tft.setCursor(0, 110);
  sprintf(buf, "RSSI :%d", WiFi.RSSI());
  tft.printf(buf);
}
void page2(){
  char buf[20];
  ireserX = gForceX;
  ireserY = gForceY;
  ireserZ = gForceZ;
  tft.setFreeFont(&FreeSerifBold12pt7b);                            
  tft.setCursor(30, 30);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  sprintf(buf, "X:%f", ireserX);
  tft.printf(buf);
  tft.setCursor(30, 60);
  sprintf(buf, "Y:%f", ireserY);
  tft.printf(buf);
  tft.setCursor(30, 90);
  sprintf(buf, "Z:%f", ireserZ);
  tft.printf(buf);
  vTaskDelay(100);
  tft.setFreeFont(&FreeSerifBold12pt7b);                            
  tft.setCursor(30, 30);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  sprintf(buf, "X:%f", ireserX);
  tft.printf(buf);
  tft.setCursor(30, 60);
  sprintf(buf, "Y:%f", ireserY);
  tft.printf(buf);
  tft.setCursor(30, 90);
  sprintf(buf, "Z:%f", ireserZ);
  tft.printf(buf);
}
void page3(){
  tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕
  tft.setFreeFont(&FreeSerifBold24pt7b);                            
  tft.setCursor(30, 60);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.printf("Page3");
}