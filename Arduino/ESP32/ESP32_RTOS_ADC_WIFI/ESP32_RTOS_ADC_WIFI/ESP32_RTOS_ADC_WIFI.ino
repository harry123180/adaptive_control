#include "WiFi.h"
//https://blog.csdn.net/qq_41868901/article/details/104677389

const int potPin = 12;
int val=0;
const char* ssid = "iPhone";
const char* password =  "qqqqqqqq";
const uint16_t port = 8090;
const char * host = "172.20.10.3";
void taskOne( void * parameter ){
  while(1){
   delay(20);
   val = analogRead(potPin);
  Serial.print("val  = ");
  Serial.println(val);
  }
  Serial.println("Ending task 1");
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  while(1){
     WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        //return;
    }
    client.print(val);
  }
  Serial.println("Ending task 2");
  vTaskDelete( NULL );
}
 
void taskThree( void * parameter){
  while(1){
    delay(800);S
    Serial.println("3");
  }
  Serial.println("Ending task 3");
  vTaskDelete( NULL );
}
 
 
void setup() {
  Serial.begin(115200);
  //pinMode(potPin,INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  xTaskCreate(
              taskOne,          /*任务函数*/
              "TaskOne",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              1,                /*任务的优先级*/
              NULL);            /*任务句柄*/
  xTaskCreate(
              taskTwo,          /* Task function. */
              "TaskTwo",        /* String with name of task. */
              10000,            /* Stack size in bytes. */
              NULL,             /* Parameter passed as input of the task */
              1,                /* Priority of the task. */
              NULL);            /* Task handle. */
  xTaskCreate(
              taskThree,          /* Task function. */
              "taskThree",        /* String with name of task. */
              10000,            /* Stack size in bytes. */
              NULL,             /* Parameter passed as input of the task */
              1,                /* Priority of the task. */
              NULL);            /* Task handle. */
}
 
void loop(){
  delay(1000);
}
