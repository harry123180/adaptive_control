#include <Servo.h>
const int trig = 13;
const int echo = 12;
Servo left_wheel;
Servo righ_wheel;
int duration,cm;
void setup() {

left_wheel.attach(10);
righ_wheel.attach(11);
Serial.begin(9600);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);

}

void loop() {
//先歸零
digitalWrite(trig,LOW);
delayMicroseconds(5);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

duration = pulseIn(echo,HIGH);
cm = (duration /2)/74;
if(cm >10)
{
left_wheel.writeMicroseconds(1340);//前進
righ_wheel.writeMicroseconds(1740);
}
else if(cm<10){
  left_wheel.writeMicroseconds(1540);//停車
righ_wheel.writeMicroseconds(1528);
}

Serial.println(cm);
}
