long t = 0;
float value;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  t++;
  
  // put your main code here, to run repeatedly:
  value = sin(t);
Serial.println(value);
if(t==360)t=0;
delay(1);
}