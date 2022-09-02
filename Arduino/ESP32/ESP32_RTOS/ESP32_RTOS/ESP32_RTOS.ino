
#include <WiFi.h>
 
#define LED1 19
#define LED2 22
#define LED1_OFF   digitalWrite(LED1, HIGH)//关灯
#define LED1_ON    digitalWrite(LED1, LOW)//开灯
#define LED1_PWM   digitalWrite(LED1, !digitalRead(LED1))//灯闪烁
#define LED2_OFF   digitalWrite(LED2, HIGH)//关灯
#define LED2_ON    digitalWrite(LED2, LOW)//开灯
#define LED2_PWM   digitalWrite(LED2, !digitalRead(LED2))//灯闪烁
 
void taskOne( void * parameter ){
  while(1){
    delay(200);
    Serial.println("1");
    LED1_PWM;
  }
  Serial.println("Ending task 1");
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  while(1){
    delay(400);
    LED2_PWM;
    Serial.println("2");
  }
  Serial.println("Ending task 2");
  vTaskDelete( NULL );
}
 
void taskThree( void * parameter){
  while(1){
    delay(800);
    Serial.println("3");
    LED1_PWM;
    LED2_PWM;
  }
  Serial.println("Ending task 3");
  vTaskDelete( NULL );
}
 
 
void setup() {
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  LED1_OFF;
  LED2_OFF;
  delay(1000);
  xTaskCreate(
              taskOne,          /*任務函數*/
              "TaskOne",        /*任務名稱的字符串*/
              10000,            /*堆棧大小，單位為Byte*/
              NULL,             /*任務輸入的參數*/
              1,                /*任務的優先級*/
              NULL);            /*任務句柄*/
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
