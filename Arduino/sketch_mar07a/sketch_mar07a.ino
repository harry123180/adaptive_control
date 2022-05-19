
#include <TimerOne.h>
#include <string.h> // strtok
String str;
char strchar[10] ;//= "Hello world, nice to meet you";
const char* d = ",";
char *p;

void setup() {
  Serial.begin(115200);
  Timer1.initialize(1500000);    // 0.15 sec interrupt once
Timer1.attachInterrupt(TimerSR); 
}
void TimerSR(void){
Serial.println("TImer");
}
void loop() {
  if (Serial.available()) {
    // 讀取傳入的字串直到"\n"結尾
    str = Serial.readStringUntil('\n');
    str.toCharArray(strchar, 10);
    p = strtok(strchar, d);
    while (p != NULL) {
        Serial.println(p);
        p = strtok(NULL, d);     
    }
  }
}
