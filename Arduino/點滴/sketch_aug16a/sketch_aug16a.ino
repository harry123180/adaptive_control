#include <Servo.h> 
 
Servo myservo;
int servoPin=21;
 
int pos = 0;    // 定義舵機轉動位置
 
void setup()
{
      myservo.attach(servoPin);  // 設置舵機控制腳位
      pinMode(22,OUTPUT);
      digitalWrite(22,HIGH);
      pinMode(39,INPUT);
      pinMode(3,INPUT);
      Serial.begin(115200);
}
 
void loop()
{ 
      pos = map(analogRead(36),0,4095,0,180);
      
      Serial.println(analogRead(39));
     delay(15);
}
