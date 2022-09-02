#include <MPU9250_asukiaaa.h>
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt;
unsigned long lastTime=0;
void setup() {
  
  Serial.begin(115200);
  Wire.begin();
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
}

void loop() {
  
  mySensor.accelUpdate();
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  //Serial.print(aX);
  //Serial.print(" ");
  //Serial.print(aY);
  //Serial.print(" ");
  //Serial.print(aZ);
  //Serial.print(" ");
  Serial.println(micros()-lastTime);
  lastTime = micros();
  aSqrt = mySensor.accelSqrt();
  // Do what you want
}
