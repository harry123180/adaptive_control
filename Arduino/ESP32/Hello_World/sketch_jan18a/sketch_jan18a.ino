String cmd;//String Char int float 
void setup() {
   Serial.begin(9600);

}

void loop() {
  if(Serial.available()){
   cmd = Serial.readStringUntil('\n');//讀取指令字串直到換行鍵(Enter)為止
   if(cmd == "Hello"){
    Serial.println("你好");
   }
   
  }
  //Serial.println("Hello World!");
 delay(1000);
}
