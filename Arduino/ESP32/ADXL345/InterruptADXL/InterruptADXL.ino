#include <Wire.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library
float xn1 = 0;
float yn1 = 0;
int k = 0;
float gf=0;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object
#define SENSORS_GRAVITY_EARTH (9.80665F)
volatile double interruptCounter;//Main loop 與 ISR 共享之變數 要用volatile聲明 不然會被編譯器優化之後刪除
int totalInterruptCounter;//用以計數發生了幾次中斷
 
hw_timer_t * timer = NULL;//宣告一個指向硬體計時器的變量
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;//使用它來處理主循環與ISR之間的同步
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  //interruptCounter=accel.getX()*0.004*SENSORS_GRAVITY_EARTH;
  //Serial.println(interruptCounter);
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void setup() {
 
  Serial.begin(115200);
  /* timerBegin(計數器編號,分頻器值,true:遞增計數flase:遞減計數)
  ESP32 計數器使用的基本信號的頻率通常為80 MHz（FireBeetle 板也是如此）。該值等於80 000 000 Hz，
  這意味著該信號將使定時器計數器每秒增加 80 000 000 次。
  雖然我們可以使用這個值進行計算來設置產生中斷的計數器編號，
  但我們將利用預分頻器來簡化它。因此，
  如果我們將該值除以80（使用 80 作為預分頻器值），
  我們將得到一個頻率為 1 MHz 的信號，該信號將使定時器計數器每秒增加 1 000 000 次。
  */
  timer = timerBegin(0, 80, true);
  
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
 if(!accel.begin())   // if ASXL345 sensor not found
  {
    Serial.println("ADXL345 not detected");
    while(1);
  }
  accel.setDataRate(ADXL345_DATARATE_1600_HZ);
  
}
 
void loop() {
  //sensors_event_t event;
  //accel.getEvent(&event);
  //Serial.println(interruptCounter);
  //Serial.print(" ");
  //Serial.println(accel.getX()*0.004*SENSORS_GRAVITY_EARTH);
  float xn = accel.getX()*0.004*SENSORS_GRAVITY_EARTH;
  float yn = 0.992*yn1 + 0.0039*xn + 0.00391*xn1;
  Serial.print(xn);
  Serial.print(" ");
  //Serial.print(gf); 
  //Serial.print(" ");
  Serial.println(yn);
  gf = gf+0.125*yn;
  delayMicroseconds(1250);
  xn1 = xn;
  yn1 = yn;
}
