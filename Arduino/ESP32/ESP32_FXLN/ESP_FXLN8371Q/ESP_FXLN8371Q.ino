const short int FXLN8371Q_X = 36;
const short int FXLN8371Q_Y = 39;
const short int FXLN8371Q_Z = 34;
float K = 0.01407273471;//0.01491970486
int val=0;
void setup() {
  //pinMode(
  Serial.begin(115200);
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.print((analogRead(FXLN8371Q_X)-900)*K);
  //Serial.print(" ");
  Serial.print((analogRead(FXLN8371Q_Y)-960)*K);
  Serial.print(" ");
  Serial.println((analogRead(FXLN8371Q_Z)-930)*K);
  //delayMicorsec(1);
}
