static const short int PinA =1;
static const short int OUTPUT_PIN =2;
const int freq = 5000;
const short int ledChannel = 0;
const short int resolution = 8;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
char buf[100];
int percentage =0;
int pwm_val= 0;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void taskOne( void * parameter ){
  while(1){
    display.setTextSize(4);
    display.setCursor(20, 10);
    sprintf(buf, "%d", percentage);
    display.println(buf);
    display.display();
    delay(100);
    display.clearDisplay();
  }
  vTaskDelete( NULL );
}
 
void taskTwo( void * parameter){
  while(1){
    pwm_val = map(analogRead(PinA),0,8191,0,255);
    ledcWrite(ledChannel,pwm_val);
    percentage = map(pwm_val,0,255,0,100);
  }
  vTaskDelete( NULL );
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(OUTPUT_PIN, ledChannel);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Start");
  display.display(); 
  delay(2000);
  display.clearDisplay();
  xTaskCreate(
              taskOne,          /*任务函数*/
              "TaskOne",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              1,                /*任务的优先级*/
              NULL);            /*任务句柄*/
  xTaskCreate(
              taskTwo,          /* Task function. */
              "TaskTwo",        /* String with name of task. */
              10000,            /* Stack size in bytes. */
              NULL,             /* Parameter passed as input of the task */
              1,                /* Priority of the task. */
              NULL);            /* Task handle. */
}

void loop() {

delay(1);

}
