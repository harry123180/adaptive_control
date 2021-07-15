#include "WiFi.h"
//this is client
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//https://blog.csdn.net/qq_41868901/article/details/104677389
//********初期宣告************
const int potPin = 33;
int val=0;
int i =0;
const char* ssid = "兔田株式会社";//兔田株式会社
const char* password =  "pekopeko";//pekopeko
const uint16_t port = 8090;
const char * host = "10.1.1.10";//172.20.10.3

//****typedef struct 新用法，創建一個新的資料結構 自定義
typedef struct{int sender;
  int value;
}Data;
/* 这个变量保持队列句柄*/
xQueueHandle xQueue;
//參考網址:https://www.qutaojiao.com/6252.html
//************以上為FIFO設定
const uint16_t samping_rate = 1000;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const uint8_t sample =100;
uint16_t data_array[sample];
//********初期宣告************

const uint32_t wait_time = 1000000/samping_rate;
void taskOne( void * parameter ){
  BaseType_t xStatus;
  /*阻止任务的时间，直到队列有空闲空间 */const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  /* 创建数据以发送*/
  Data data;
  /* sender 1的id为1 */
  data.sender = 1;
  
  for(;;){
    /* 将数据发送到队列前面 */
        data.value = analogRead(potPin);//ADC之後的電壓值塞入value
        Serial.println(data.value);
        xStatus = xQueueSendToFront( xQueue, &data, xTicksToWait );//發送~
        delayMicroseconds(wait_time);
                                          
          }
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  BaseType_t xStatus;
  /* 阻止任务的时间，直到数据可用*/const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  Data data;
  for(;;){
     WiFiClient client;
     //Serial.print("使用核心編號AAAAAAA：");
     //Serial.println(xPortGetCoreID());
     if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
                                     }
     Serial.println(data.value);
     xStatus = xQueueReceive( xQueue, &data, xTicksToWait );
     if(xStatus == pdPASS && !client.connect(host, port)){
        client.print(data.value);
        Serial.println(data.value);
                          }
  }
  //Serial.println("Ending task 2");
  vTaskDelete( NULL );
}
 
void taskThree( void * parameter){
  //oled線程
  while(1){ 
    i++;
  if(i>10000)i=0;
  //Serial.println("working");
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 10);
  display.println("RMS="+String(i));
  display.display();
  delay(100);
  }
  
  vTaskDelete( NULL );
}
 
 
void setup() {
 Serial.begin(115200);
  //pinMode(potPin,INPUT);
  //**********OLED 設定 *************
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  //*********FIFO設定
  xQueue = xQueueCreate(sample, sizeof(Data));//創一個Queue
  
  /*
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // Display static text
  display.println("Hello, world!");
  display.display(); 
  */
  //**********OLED 設定 *************
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...");
    delay(500);
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  //ADC線程
  xTaskCreatePinnedToCore(
  taskOne, //本任務實際對應的Function
  "TaskOne", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  1); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）

 //WIFI線程
  xTaskCreate(
              taskTwo,          // Task function. 
              "TaskTwo",        // String with name of task. 
              10000,            // Stack size in bytes. 
              NULL,             // Parameter passed as input of the task 
              1,                // Priority of the task. 
              NULL);            // Task handle. 
              
 //OLED線程
 /*
  xTaskCreatePinnedToCore(
              taskThree,          //Task function. 
              "taskThree",        // String with name of task. 
              10000,            // Stack size in bytes. 
              NULL,             // Parameter passed as input of the task 
              1,                // Priority of the task. 
              NULL,
              0);            // Task handle. 
              */
}
 
void loop(){

}
