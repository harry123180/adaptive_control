#include <Wire.h>
#include "FFT.h"
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object
sensors_event_t event;
//FFT 必須的變數
#define FFT_N 1024 // Must be a power of 2
#define TOTAL_TIME 0.22260 // This is equal to FFT_N/sampling_freq
float fft_input[FFT_N];
float fft_output[FFT_N];
float max_magnitude = 0;
float fundamental_freq = 0;
double fft_signal[FFT_N];
char print_buf[300];
//****計時中斷的變數****//
volatile int interruptCounter;//Main loop 與 ISR 共享之變數 要用volatile聲明 不然會被編譯器優化之後刪除
int totalInterruptCounter;//用以計數發生了幾次中斷
hw_timer_t * timer = NULL;//宣告一個指向硬體計時器的變量
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;//使用它來處理主循環與ISR之間的同步
 
//*******Task任務內容*********//
void taskOne( void * parameter ){
  /*taskone做i2c 讀取adxl的數值 
   * 並將數值存入fft_signal
   * 
   */
  while(1){
  
  
  
  //Serial.println("Core1");
  //delay(100);



          
  }
  Serial.println("Ending task 1");
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  while(1){
    /*
      fft_config_t *real_fft_plan = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
      for (int k = 0 ; k < FFT_N ; k++)
        real_fft_plan->input[k] = (float)fft_signal[k];
        */
      //Serial.println("Core2");
      //delay(200);
  }
  Serial.println("Ending task 2");
  vTaskDelete( NULL );
}
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  if(interruptCounter%1000 ==0)
      Serial.println(interruptCounter);
  if(interruptCounter>10000)
    interruptCounter=0;
  portEXIT_CRITICAL_ISR(&timerMux);
}


void setup() {
  Serial.begin(115200);
  delay(1000);
  //******計時中斷設定******//
  //為了達到指定sampling rate//
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
  //ADXL345尋找
  if(!accel.begin()){   // if ASXL345 sensor not found
      Serial.println("ADXL345 not detected");
      while(1);
    }
  //Task宣告及初期設定
  xTaskCreatePinnedToCore(
  taskOne, //本任務實際對應的Function
  "TaskOne", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  1); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）

  
xTaskCreatePinnedToCore(
  taskTwo, //本任務實際對應的Function
  "TaskTwo", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  0); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）
  /*
  xTaskCreate(
              taskOne,          ///*任务函数
              "TaskOne",       带任务名称的字符串
              10000,            堆栈大小，单位为字节
              NULL,             作为任务输入传递的参数
              1,                任务的优先级
              NULL);            任务句柄
  xTaskCreate(
              taskTwo,          /* Task function. 
              "TaskTwo",        /* String with name of task. 
              10000,            /* Stack size in bytes. 
              NULL,             /* Parameter passed as input of the task 
              1,                /* Priority of the task. 
              NULL);            /* Task handle. */

}
 
void loop(){
  delay(1000);
}
