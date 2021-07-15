#include "WiFi.h"

const char* ssid = "兔田株式会社";//兔田株式会社iPhone
const char* password =  "pekopeko";//pekopekoqqqqqqqq
const uint16_t port = 8090;
const char * host = "10.1.1.10";//10.1.1.10/172.20.10.2

//參考網址:https://www.qutaojiao.com/6252.html
/* *保存数据的结构**/
typedef struct{int sender;
  int counter;
}Data;
const int potPin = 33;
/* 这个变量保持队列句柄*/
xQueueHandle xQueue;
 
void setup() {
 
  Serial.begin(112500);
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  /* 创建队列，其大小可包含5个元素Data */
  xQueue = xQueueCreate(100, sizeof(Data));
  xTaskCreate(
      sendTask1,           // 任务函数 
      "sendTask1",        // 任务名称 
      10000,                    // 任务的堆栈大小 
      NULL,                     // 任务的参数 
      2,                        // 任务的优先级 
      NULL);                    // 跟踪创建的任务的任务句柄 
   xTaskCreate(
      receiveTask,           
      "receiveTask",        
      10000,                    
      NULL,                     
      1,                       
      NULL);                  
}
 
void loop() {
 
}
 
void sendTask1( void * parameter )
{
  /* 保持发送数据的状态 */
  BaseType_t xStatus;
  /*阻止任务的时间，直到队列有空闲空间 */const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  /* 创建数据以发送*/
  Data data1;
  /* sender 1的id为1 */
  data1.sender = 1;
  data1.counter = 1;
  for(;;){
    /* 将数据发送到队列前面 */
    xStatus = xQueueSendToFront( xQueue, &data1, xTicksToWait );
    /*检查发送是否正常*/if( xStatus == pdPASS ) {
      /*增加发送方1的计数器 */
      data1.counter = analogRead(potPin);//ADC之後的電壓值塞入value
      //data1.counter = data1.counter + 1;
    }
    /*我们在这里延迟，以便receiveTask有机会接收数据 */
    delay(1);
  }
  vTaskDelete( NULL );
}
/* 这个任务类似于sendTask1  */

void receiveTask( void * parameter )
{
  /* 保持接收数据的状态 */
  BaseType_t xStatus;
  /* 阻止任务的时间，直到数据可用*/const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  Data data;
  for(;;){
    WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.print("Connection to host failed");
        delay(1);
    }
        //                              }
    /* 从队列接收数据 */
    xStatus = xQueueReceive( xQueue, &data, xTicksToWait );
    /* 检查接收是否正常 */if(xStatus == pdPASS){
      /* 将数据打印到终端 */
      //Serial.print("receiveTask got data: ");
      //Serial.print("sender = ");
      //Serial.print(data.sender);
      client.print(data.counter);
        Serial.println(data.counter);
    }
  }
  vTaskDelete( NULL );
} 
