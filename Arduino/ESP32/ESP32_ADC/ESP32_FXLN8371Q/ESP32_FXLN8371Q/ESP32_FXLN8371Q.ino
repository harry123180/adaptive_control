const short int FXLN8371Q_X = 4;
const short int FXLN8371Q_Y = 2;
const short int FXLN8371Q_Z = 15;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(FXLN8371Q_Z));
}
