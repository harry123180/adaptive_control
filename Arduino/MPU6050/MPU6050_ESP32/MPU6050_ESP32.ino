#include <Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;
float gForceX, gForceY, gForceZ;
float orgdata[3][150];

void dataReceiver(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,16,true);  // request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  processData();
}
void processData(){
  gForceX = AcX / 16384.0;
  gForceY = AcY / 16384.0; 
  gForceZ = AcZ / 16384.0;
}
void debugFunction(int16_t AcX, int16_t AcY, int16_t AcZ,uint8_t i){
  orgdata[0][i]=gForceX;
  orgdata[1][i]=gForceY;
  orgdata[2][i]=gForceZ;
  
  /*
  Serial.print(i);
  Serial.print(" ");
  Serial.print(orgdata[0][i]);
  Serial.print(" ");
  Serial.print(orgdata[1][i]);
  Serial.print(" ");
  Serial.println(orgdata[2][i]);  
  */
  
}

 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Wire.begin(21,22);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);



}
 
void loop() {
  for(int i=0;i<150;i++){
  dataReceiver();
  debugFunction(AcX,AcY,AcZ,i);
  }
  delay(20);
  
}
