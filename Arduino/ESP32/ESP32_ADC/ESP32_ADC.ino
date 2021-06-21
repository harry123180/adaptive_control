const int potPin = 33;
int val=0;
void setup() {
  //pinMode(
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(potPin);
  Serial.println(val);
  //delayMicorsec(1);
}
