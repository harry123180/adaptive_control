#define encoder_1A  2
#define encoder_1B  4
volatile long Pos = 0;//實際值
void setup() {
Serial.begin (115200);
pinMode(encoder_1A, INPUT); 
digitalWrite(encoder_1A, HIGH);       // turn on pull-up resistor
pinMode(encoder_1B, INPUT);
attachInterrupt(digitalPinToInterrupt(2), doEncoder1, CHANGE);  // enconder pin on interrupt 0-pin 2
}
void loop() {
  
}
void doEncoder1() {
  Serial.println(Pos);
  if (digitalRead(encoder_1A) == digitalRead(encoder_1B)) {   //高電位 低電位
    Pos++; //角度遞增1
  } else {
    Pos--; //角度遞減1
  }
}
