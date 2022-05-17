//https://youyouyou.pixnet.net/blog/post/121065836-esp32%E9%A1%9E%E6%AF%94%E8%BC%B8%E5%87%BAsg90
void setup()
{  
  Serial.begin(115200);
  ledcSetup(1, 50, 8); // 使用PWM頻道1,輸出頻率50Hz,8bit 解析度
  ledcAttachPin(17, 1);  //GPIO17與頻道1綁定
}
void loop()
{
  for(int angle = 0; angle <= 180; angle++)
  {
    int value=map(angle,0,180,6.4,30.72);
    ledcWrite(1, value);//輸出到頻道1
    Serial.println("角度=" + String(angle) + ",value=" + String(value));
    delay(70);    
  }
delay(1000);
}
