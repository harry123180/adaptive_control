#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
// Replace the next variables with your SSID/Password combination
const char* ssid = "K108-2";
const char* password = "datadata";
// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "https://lwcjacky.myds.me/";//免註冊MQTT伺服器
const unsigned int mqtt_port = 18084;
#define MQTT_USER               "test"             //本案例未使用
#define MQTT_PASSWORD           "vcAnn8GZ"         //本案例未使用
WiFiClient espClient; 
PubSubClient client(espClient);
long lastMsg = 0;
//char msg[50];
int value = 0;
float temperature = 0;
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
    WiFi.mode(WIFI_STA);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client",MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      // Subscribe
      //client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    temperature = random(10);   
    char tempString[8];
    Serial.print("Temperature: ");
    tempString[0] = '1';
    tempString[1] = '.';
    tempString[2] = '2';
    tempString[3] = '3';
    
    //tempString[4] = '4';
    //tempString[5] = '5';
    //tempString[6] = '6';
    //tempString[7] = '7';
    Serial.print(tempString);
    dtostrf(temperature, 1, 2, tempString);
    
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("dd", tempString);
    //client.publish("test_node1", tempString);
  }
}
