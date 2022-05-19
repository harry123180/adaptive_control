
#include <TimerOne.h>
#define encoder_1A  2
#define encoder_1B  3
#define LEFT1 5
#define LEFT2 4
int error1=0,err1=0,ie1=0,de1=0,u1=0;//誤差
float ki1,kd1,f1;
int kp1=4;
int Vrx1=15;//速度設定值
float st1;
float ua1=0;//輸出值
volatile long Pos1 = 0;//1號實際值
volatile long Pos1last = 0;//儲存1號上次的實際值
float dt = 0.15;//時間   
float realspeedwheel_1 =0; //輪1的真實轉速
float V1y = 0; //1號實際速度
float fac = 3/(dt*780);
int t_indx=0;
int tt_indx=0;
int ctrl_end = 0;
void setup() {
  // put your setup code here, to run once:
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

t_indx ++;   //每計時中斷一次+1 
  if ( t_indx > 1000 ) t_indx = 0;  //若計時中斷超過1000時歸0
  
  realspeedwheel_1 = (Pos1-Pos1last)*fac;//輪1的真實轉速(rps)
  //Serial.println(realspeedwheel_1);
  //if(Vrx1<=780) 
  ki1=1.02,kd1=0.09,f1=1;
  //if(Vrx1>780) ki1=0.01,kd1=0.09,f1=0.09;
  if((Pos1-Pos1last)<-20000) {realspeedwheel_1 = (Pos1+30000-Pos1last)*fac;}
  else if ((Pos1-Pos1last)>20000){realspeedwheel_1 =(Pos1-30000-Pos1last)*fac;}
  error1 = Vrx1-realspeedwheel_1;      //誤差=設定速度-實際速度(rps)
  u1= PID_control(kp1,ki1,kd1,error1,ie1,err1,f1);
  Pos1last = Pos1;//儲存實際值
  if(Pos1 >30000) Pos1 =0;//Pos1歸零
  else if(Pos1 < -30000) Pos1 =0;//Pos1歸零
  motor_control(u1);
  
  Serial.print(Vrx1);
  Serial.print(" ");
  Serial.println(realspeedwheel_1);
  
}

void loop() {
  // put your main code here, to run repeatedly:

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
  ie = ie + error*dt;         //ie=ie+e*daltE 計算積分的e
  if (ie > 1280) ie=1280;
  else if (ie<-1280) ie=-1280;  
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
