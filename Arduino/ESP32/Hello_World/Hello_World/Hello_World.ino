#define pin A0
int  val ;
void setup() {
pinMode(pin,INPUT);  
Serial.begin(9600);//開啟Serial 設定boardrate 9600
}

void loop() {
  val = analogRead(pin);
  Serial.println(val);//顯示
  delay(1);

}
