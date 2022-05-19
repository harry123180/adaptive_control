#define R 8
#define G 9
#define B 10

void setup() {

pinMode(R,OUTPUT);
pinMode(G,OUTPUT);
pinMode(B,OUTPUT);
}

void loop() {
for(int i=0 ;i<255;i++){
for(int j=0 ;j<255;j++){
for(int k=0 ;k<255;k++){
analogWrite(R,i);
analogWrite(G,j);
analogWrite(B,k);
}}}
for(int i=255 ;i<0;i--){
for(int j=255 ;j<0;j--){
for(int k=255 ;k<0;k--){
analogWrite(R,i);
analogWrite(G,j);
analogWrite(B,k);
}}}
}
