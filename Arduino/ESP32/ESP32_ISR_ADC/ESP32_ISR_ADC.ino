volatile int interruptCounter;
int val=0;
const int potPin = 13; //Ref Pin 
hw_timer_t * timer = NULL; 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  val = analogRead(potPin);
  Serial.println(val);
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup() {
 
  //Serial.begin(115200);
  Serial.begin(1000000);
 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100, true);//單位:微秒
  timerAlarmEnable(timer);
 
}
 
void loop() {

}
