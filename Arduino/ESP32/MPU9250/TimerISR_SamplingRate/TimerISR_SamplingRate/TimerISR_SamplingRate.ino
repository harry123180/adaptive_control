#include <MPU9250_asukiaaa.h>
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt;
volatile int interruptCounter;//Main loop 與 ISR 共享之變數 要用volatile聲明 不然會被編譯器優化之後刪除
int totalInterruptCounter;//用以計數發生了幾次中斷
 
hw_timer_t * timer = NULL;//宣告一個指向硬體計時器的變量
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;//使用它來處理主循環與ISR之間的同步
 
void IRAM_ATTR onTimer() {
  //portENTER_CRITICAL_ISR(&timerMux);

  
  //interruptCounter++;
  //portEXIT_CRITICAL_ISR(&timerMux);
}
 
void setup() {
   Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
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
  timerAlarmWrite(timer, 1020000, true);
  timerAlarmEnable(timer);
 
}
 
void loop() {
 
  //if (interruptCounter > 0) {
 
    //portENTER_CRITICAL(&timerMux);
    //interruptCounter--;
    //portEXIT_CRITICAL(&timerMux);
  mySensor.accelUpdate();
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  Serial.print(aX);
  Serial.print(" ");
  Serial.print(aY);
  Serial.print(" ");
  Serial.println(aZ);
    //totalInterruptCounter++;
 
 
 // }
}
