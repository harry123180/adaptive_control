#include <esp_now.h>
#include <WiFi.h>
//ESP 12 接收器
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int axis;//0=X 1=Y 2=Z
    int index;//0,60,120 一段傳60個float 分3次傳
    float data[50];//大小要50個float 不然會超過payload的限制
} struct_message;

// Create a struct_message called myData
struct_message myData;
int count=0;//計算收訊息的次數
float orgdata[3][150];//儲存原始數據的array
// callback function that will be executed when data is received
void print_data(){
  for(int indx=0 ;indx<150;indx++){
    Serial.print(orgdata[0][indx]);
    Serial.print(" ");
    Serial.print(orgdata[1][indx]);
    Serial.print(" ");
    Serial.println(orgdata[2][indx]);
  }
}
void debug(int i){
  Serial.println(myData.data[i]);//發現150個data 從128開始值為0 用以debug顯示128以後函數
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  if(len==208){//訊息大小208才對。
    for(int i=0;i<50;i++){
    orgdata[myData.axis][myData.index+i]=myData.data[i];
    }
    count++;
    if(myData.axis==2 and myData.index==100){
      print_data();
      count=0;
    }
  }
  /*
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("axis: ");
  Serial.println(myData.axis);
  Serial.print("index: ");
  Serial.println(myData.index);
  Serial.print("data: ");
  */
  for(int i=0;i<50;i++){
  //Serial.println(myData.data[i]);
  }
}


void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
