#include <TimerOne.h>
#define encoder_1A  2
#define encoder_1B  3
#define LEFT1 5
#define LEFT2 6
int cmd_indx = 0;
String str;
char cmd[10];
char *name_ = NULL;
int error1=0,err1=0,ie1=0,de1=0,u1=0;//誤差
float ki1,kd1,f1;

float kp1;
int set_position=0;//位置設定值
float st1;
float ua1=0;//輸出值
volatile long Pos1 = 0;//1號實際值
volatile long Pos1last = 0;//儲存1號上次的實際值
float dt = 0.15;//時間   
float fac = 3/(dt*780);
void setup() {
  kp1=0.58;
  ki1=0.042,kd1=0.12,f1=0.45;
pinMode(encoder_1A, INPUT); 
digitalWrite(encoder_1A, HIGH);       // turn on pull-up resistor
pinMode(encoder_1B, INPUT); 
digitalWrite(encoder_1B, HIGH);       // turn on pull-up resistor
attachInterrupt(digitalPinToInterrupt(2), doEncoder1, CHANGE);  // enconder pin on interrupt 0-pin 2
Serial.begin (115200);
pinMode(LEFT1, OUTPUT);
pinMode(LEFT2, OUTPUT);
Timer1.initialize(150000);    // 0.15 sec interrupt once
Timer1.attachInterrupt(TimerSR); 
}
void TimerSR(void){
  
  error1 = set_position-Pos1;      
  u1= PID_control(kp1,ki1,kd1,error1,ie1,err1,f1);
  Pos1last = Pos1;//儲存實際值
  if(Pos1 >30000)
    {   Pos1 =0;//Pos1歸零
        Pos1last = Pos1last-30000;
    }
  else if(Pos1 < -30000)
    { Pos1 =0;//Pos1歸零
      Pos1last = Pos1last+30000;
    }
  motor_control(u1);
  Serial.print(set_position);
  Serial.print(" ");
  Serial.print(kp1);
  Serial.print(" ");
  Serial.print(ki1);
  Serial.print(" ");
  Serial.print(kd1);
  Serial.print(" ");
  Serial.print(u1);
  Serial.print(" ");
  Serial.println(Pos1);
}
void loop() {
if (Serial.available()) {
    cmd_indx = 0;
    // 讀取傳入的字串直到"\n"結尾
    str = Serial.readStringUntil('\n');
    str.toCharArray(cmd, 10);//str 轉char 存入cmd 大小為10
    name_ = strtok(cmd, ",");
    while(name_ != NULL)
    {
        cmd_indx++;
        /*Serial.print(cmd_indx);
        Serial.print("  ");
        Serial.println(name_);*/
        switch(cmd_indx) {
          case 1:
            set_position = String(name_).toInt();
            break;
          case 2:
            kp1 = String(name_).toFloat();
            break;
          case 3:
            ki1 = String(name_).toFloat();
            break;
          case 4:
            kd1 = String(name_).toFloat();
            break;
           default:
          Serial.println("Invalid number");
            
          
        }
        name_ = strtok(NULL, ","); 
    }
    //set_position = str.toInt();
  }
  
}
  void doEncoder1() {
  //Serial.println(Pos1);
  if (digitalRead(encoder_1A) == digitalRead(encoder_1B)) {   //高電位 低電位
    Pos1++; 
  } else {
    Pos1--;
  }
}
int PID_control(float kp, float ki, float kd, int error, int &ie, int &err,float f) {
  int de,ua,u;
  ie = ie + error*dt;         //ie=ie+e*daltT 計算積分的e
  //if (ie > 1280) ie=1280;
  //else if (ie<-1280) ie=-1280;  
  de = (error-err)/dt;              //微分的e
  ua = kp*error+ki*ie+kd*de;       //PID算法公式
  u = (int) (ua*f);           //u*=fac*u
  err = error;           //把這次的誤差存起來下次用
  if(u > 255) u = 255;     //如果u算出來大於255上限 就直接等於最大值255
  else if(u < -255) u = -255;//同上  
  return u;
}
void motor_control(int u11){
    if(u11>0){ 
    analogWrite(LEFT1,u11);
    analogWrite(LEFT2,0);
  }//直接丟入正轉副程式
  else if (u11<0){
    analogWrite(LEFT1,0);
    analogWrite(LEFT2,-u11);
  }//丟入反轉副程式(負負得正)
}
