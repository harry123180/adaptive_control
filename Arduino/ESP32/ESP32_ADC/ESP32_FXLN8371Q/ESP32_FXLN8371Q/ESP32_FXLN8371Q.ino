static const short int FXLN8371Q_X = 36;
static const short int FXLN8371Q_Y = 39;
static const short int FXLN8371Q_Z = 34;
const float sensitivity = 54;// mv/g
const float num2mvolt = 3300/4096;
const float num2g = 0.01491970486; //adc_max_vlot(mv)/adc_resolution(2^bit).sensitivity(mv/g)
float arr[3]={1,2,3};
void f(float arr1[]){
  arr[0] *= 9;
}
float xn1[3] = {0};
float yn1[3] = {0};
int k = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float xn[3] = {num2g*(analogRead(FXLN8371Q_X)-810),
                 num2g*(analogRead(FXLN8371Q_Y)-810),
                 num2g*(analogRead(FXLN8371Q_Z)-810)};

  // Compute the filtered signal
  float yn[3] = {(0.969*yn1[0] + 0.0155*xn[0] + 0.0155*xn1[0]),
                 (0.969*yn1[1] + 0.0155*xn[1] + 0.0155*xn1[1]),
                 (0.969*yn1[2] + 0.0155*xn[2] + 0.0155*xn1[2])};

  delay(1);
  for(int i=0;i<3;i++){
  xn1[i] = xn[i];
  yn1[i] = yn[i];
  }
  if(k % 3 == 0){
    // This extra conditional statement is here to reduce
    // the number of times the data is sent through the serial port
    // because sending data through the serial port
    // messes with the sampling frequency
  
    // Output
    Serial.print(2*yn[0]);
    Serial.print(" ");
    Serial.print(2*yn[1]);
    Serial.print(" ");
    Serial.print(2*yn[2]);
    Serial.print(" ");
    Serial.print(2*xn[0]);
    Serial.print(" ");
    Serial.print(2*xn[1]);
    Serial.print(" ");
    Serial.println(2*xn[2]);
    //Serial.print(" ");
    //Serial.println(2*yn);
  }
  k = k+1;
//Serial.print(num2g*(analogRead(FXLN8371Q_X)-810));
//Serial.print(" ");
//Serial.print(num2g*(analogRead(FXLN8371Q_Y)-810));
//Serial.print(" ");
//Serial.println(num2g*(analogRead(FXLN8371Q_Z)-810));

}
