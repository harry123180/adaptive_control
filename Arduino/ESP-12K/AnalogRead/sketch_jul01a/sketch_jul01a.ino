static const short int PinA =1;
static const short int OUTPUT_PIN =2;
const int freq = 5000;
const short int ledChannel = 0;
const short int resolution = 8;
int len = 100;
int avg[100]={0};
float total = 0;
bool ini_state = true;
void setup() {
Serial.begin(9600);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(OUTPUT_PIN, ledChannel);
}

void loop() {
if(ini_state ==true){
  ini_state = false;
  for(int i=0;i<len;i++){
    avg[i] = analogRead(PinA)*3300/8192;
    total = total+avg[i];
    }
  }
for(int i=0;i<len;i++){
  total= total-avg[i]+analogRead(PinA)*3300/8192;
  avg[i]=analogRead(PinA)*3300/8192;
  Serial.println(total/len);
}
for(int i=len-1;i>0;i--){
  total= total-avg[i]+analogRead(PinA)*3300/8192;
  avg[i]=analogRead(PinA)*3300/8192;
  Serial.println(total/len);
}

  
}
