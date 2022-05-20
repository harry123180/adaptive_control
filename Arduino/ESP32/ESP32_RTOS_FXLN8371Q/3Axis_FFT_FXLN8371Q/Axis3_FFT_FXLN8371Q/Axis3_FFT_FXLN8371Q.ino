#include <Wire.h>
#include "FFT.h"
//****FFT 必須的變數****//
#define FFT_N 1024 // Must be a power of 2
#define TOTAL_TIME 0.0512 // This is equal to FFT_N/sampling_freq
float fft_input[FFT_N];
float fft_output[FFT_N];
float max_magnitude = 0;
float fundamental_freq = 0;
double fft_signal_X[FFT_N];
double fft_signal_Y[FFT_N];
double fft_signal_Z[FFT_N];
char print_buf[300];
bool flag =false;
//***FXLN變數****//
const short int FXLN8371Q_X = 4;
const short int FXLN8371Q_Y = 2;
const short int FXLN8371Q_Z = 15;
//****計時中斷的變數****//
int t0Counter=0;
int t1Counter=0;
int t2Counter=0;
hw_timer_t * timer_0 = NULL;//宣告一個指向硬體計時器的變量
hw_timer_t * timer_1 = NULL;
hw_timer_t * timer_2 = NULL;
//portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;//使用它來處理主循環與ISR之間的同步
//*******Task任務內容*********//
void taskOne( void * parameter ){
  /*taskone做i2c 讀取adxl的數值 
   * 並將數值存入fft_signal
   * 
   */
  while(1){
        fft_config_t *real_fft_plan_0 = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
        fft_config_t *real_fft_plan_1 = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
        fft_config_t *real_fft_plan_2 = fft_init(FFT_N, FFT_REAL, FFT_FORWARD, fft_input, fft_output);
        if(flag){
          flag = false;
          for (int k = 0 ; k < FFT_N ; k++){
            real_fft_plan_0->input[k] = (float)fft_signal_X[k];//將fft_signal填入輸入槽位
            real_fft_plan_1->input[k] = (float)fft_signal_Y[k];//將fft_signal填入輸入槽位
            real_fft_plan_2->input[k] = (float)fft_signal_Z[k];//將fft_signal填入輸入槽位  
          }
          fft_execute(real_fft_plan_0);
          fft_execute(real_fft_plan_1);
          fft_execute(real_fft_plan_2);
          for (int k = 1 ; k < real_fft_plan_0->size / 2 ; k++){
            //The real part of a magnitude at a frequency is followed by the corresponding imaginary part in the output
            float mag_0 = sqrt(pow(real_fft_plan_0->output[2*k],2) + pow(real_fft_plan_0->output[2*k+1],2))/1;
            float mag_1 = sqrt(pow(real_fft_plan_1->output[2*k],2) + pow(real_fft_plan_1->output[2*k+1],2))/1;
            float mag_2 = sqrt(pow(real_fft_plan_2->output[2*k],2) + pow(real_fft_plan_2->output[2*k+1],2))/1;
            float freq = k*1.0/TOTAL_TIME;
            //sprintf(print_buf,"%1f %1f %1f", mag_0,mag_1,mag_2);
            //Serial.println(print_buf);
            if(mag_0 > max_magnitude){
                max_magnitude = mag_0;
                fundamental_freq = freq;
            }     
          }
          //sprintf(print_buf,"Fundamental Freq : %f Hz\t Mag: %f g\n", fundamental_freq, (max_magnitude/10000)*2/FFT_N);
          //Serial.println(print_buf);
          flag = false;//將fft_sginal填充完畢 flag復位     
        }
        fft_destroy(real_fft_plan_0);//釋放fft記憶體
        fft_destroy(real_fft_plan_1);
        fft_destroy(real_fft_plan_2);
  }
  Serial.println("Ending task 1");
  vTaskDelete( NULL );
}
void IRAM_ATTR onTimer_0() {
  t0Counter++;
  fft_signal_X[t0Counter] = analogRead(FXLN8371Q_X);
  if(t0Counter>FFT_N){
    t0Counter=0;
    //Serial.println("Reset Sampling Flag");
    flag = true; //把flag打開 通知fft可以進行了
  }
  //portEXIT_CRITICAL_ISR(&timerMux);
}
void IRAM_ATTR onTimer_1() {
  t1Counter++;
  fft_signal_Y[t1Counter] = analogRead(FXLN8371Q_Y);
  if(t1Counter>FFT_N){
    t1Counter=0;
    //flag = true; //把flag打開 通知fft可以進行了
  }
}
void IRAM_ATTR onTimer_2() {
  t2Counter++;
  fft_signal_Z[t2Counter] = analogRead(FXLN8371Q_Z);
  if(t2Counter>FFT_N){
    t2Counter=0;
    //flag = true; //把flag打開 通知fft可以進行了
  }
}
void setup() {
  Serial.begin(115200);
  delay(1000);
  //******計時中斷設定******//
  //為了達到指定sampling rate//
  timer_0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_0, &onTimer_0, true);
  timerAlarmWrite(timer_0, 60, true);
  timerAlarmEnable(timer_0);
  timer_1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_1, &onTimer_1, true);
  timerAlarmWrite(timer_1, 60, true);
  timerAlarmEnable(timer_1);
  timer_2 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_2, &onTimer_2, true);
  timerAlarmWrite(timer_2, 60, true);
  timerAlarmEnable(timer_2);
  //
  //Task宣告及初期設定
  xTaskCreatePinnedToCore(
  taskOne, //本任務實際對應的Function
  "TaskOne", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  tskNO_AFFINITY); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）

  /*
xTaskCreatePinnedToCore(
  taskTwo, //本任務實際對應的Function
  "TaskTwo", //任務名稱（自行設定）
  10000, //所需堆疊空間（常用10000）
  NULL, //輸入值
  0, //優先序：0為最低，數字越高代表越優先
  NULL, //對應的任務handle變數
  0); //指定執行核心編號（0、1或tskNO_AFFINITY：系統指定）
  
  xTaskCreate(
              taskOne,          ///*任务函数
              "TaskOne",       带任务名称的字符串
              10000,            堆栈大小，单位为字节
              NULL,             作为任务输入传递的参数
              1,                任务的优先级
              NULL);            任务句柄
  xTaskCreate(
              taskTwo,          /* Task function. 
              "TaskTwo",        /* String with name of task. 
              10000,            /* Stack size in bytes. 
              NULL,             /* Parameter passed as input of the task 
              1,                /* Priority of the task. 
              NULL);            /* Task handle. */

}
 
void loop(){
  delay(1);
}
