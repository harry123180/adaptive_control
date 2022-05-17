int trigPin = 8;                  //Trig Pin
int echoPin = 7;                  //Echo Pin
int duration,cm;
int motor = 9;
int pushButton = 2;  // 按鈕 腳位7
int buttonState = 0;  //假設為按鈕狀態，先設定0
int beforeState = 0;   //假設之前的狀態
int presstime = 0;  //假設按下的次數
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
  pinMode(motor,OUTPUT);
  pinMode(pushButton,INPUT);
}

void loop() {
  buttonState = digitalRead(pushButton);
  Serial.print(buttonState);
  Serial.print("  ");
  Serial.println(presstime);  //輸出狀況 傳訊號給電腦
  if(buttonState==1 and beforeState==0){
     presstime = presstime+1;
     
     
  }
  if (beforeState !=beforeState){
      delay(20);
    }
  beforeState=buttonState;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);             // 讀取 echo 的電位
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  if(presstime%2==0){
    digitalWrite(motor,LOW);
  }
  else if(presstime%2!=0){
    digitalWrite(motor,HIGH);
  }
  if (cm <40){
    digitalWrite(motor,LOW);
  }
  delay(250);
}
