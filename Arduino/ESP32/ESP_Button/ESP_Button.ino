
int P =23;

void setup()
{

pinMode(P, INPUT);
Serial.begin(115200);
}

void loop()
{
//int Push_button_state =;
Serial.println( digitalRead(P));

/*
else 
{
//digitalWrite(LEDPIN, LOW); 
}
*/
}
