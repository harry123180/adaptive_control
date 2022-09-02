#include <WiFi.h>
const char* ssid = "SHC";
const char* password =  "datadata";
const uint16_t port = 8090;
const char * host = "192.168.0.228";
int GPIOPin = 23;
bool state=1;
void IRAM_ATTR ISR() {
    state = !state;
}
void taskOne( void * parameter ){
  while(1){
   /* do anyting where you want */
   WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
    Serial.println("Connected to server successful!");
    client.print(state);
    //Serial.println("Disconnecting...");
    client.stop();
    delay(100);
  }
  vTaskDelete( NULL );
}

void taskTwo( void * parameter){
  while(1){
   /* do anyting where you want */
  }
  vTaskDelete( NULL );
}
void setup()
{
  attachInterrupt(GPIOPin, ISR, FALLING);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  xTaskCreate(
      taskOne,          /*任務函數*/
      "TaskOne",        /*任務名稱的字符串*/
      10000,            /*堆棧大小，單位為Byte*/
      NULL,             /*任務輸入的參數*/
      1,                /*任務的優先級*/
      NULL);            /*任務句柄*/
  xTaskCreate(
      taskTwo,          /* Task function. */
      "TaskTwo",        /* String with name of task. */
      10000,            /* Stack size in bytes. */
      NULL,             /* Parameter passed as input of the task */
      1,                /* Priority of the task. */
      NULL);            /* Task handle. */
  }     
void loop()
{
    
}
