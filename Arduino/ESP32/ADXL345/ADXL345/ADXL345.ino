#include <Wire.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library
#define SDA 0
#define SCL 2
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object
sensors_event_t event;
void setup() {
    Wire.begin(0,2);
  Serial.begin(115200);
  if(!accel.begin())   // if ASXL345 sensor not found
  {
    Serial.println("ADXL345 not detected");
    while(1);
  }

}

void loop() {
 //sensors_event_t event;

 accel.getEvent(&event);
 //Serial.print("X: ");
 Serial.print(event.acceleration.x);
 Serial.print("  ");
 //Serial.print("Y: ");
 Serial.print(event.acceleration.y);
 Serial.print("  ");
 //Serial.print("Z: ");
 Serial.print(event.acceleration.z);
 Serial.println("  ");
 //Serial.println("m/s^2 ");
 delay(1);

}
