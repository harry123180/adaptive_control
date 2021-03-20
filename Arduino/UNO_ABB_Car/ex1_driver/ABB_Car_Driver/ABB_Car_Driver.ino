#include <Servo.h>
Servo left_wheel;
Servo righ_wheel;
void setup() {
left_wheel.attach(10);
righ_wheel.attach(11);
}
void loop() {
left_wheel.writeMicroseconds(1340);//前進
righ_wheel.writeMicroseconds(1740);
delay(1000);
left_wheel.writeMicroseconds(1540);//停車
righ_wheel.writeMicroseconds(1528);
}
