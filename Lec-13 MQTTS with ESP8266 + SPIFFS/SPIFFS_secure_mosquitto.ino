#include "FS.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Learner";
const char* password = "wilco@07";
const char* mqtt_server = "test.mosquitto.org"; //MQTT broker ip 
//IPAddress server(172, 16, 0, 95);
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}
WiFiClientSecure espClient;
//SPIFFS.begin();
//File ca = SPIFFS.open("/mosquitto_or.der", "r");
//if(!ca) {
//  Serial.println("FIle not Found!");
//  return;  
//}
//

PubSubClient client(mqtt_server,8883,callback,espClient); //set  MQTT port number to 8883 as per //standard
long lastMsg = 0;
char msg[50];
int value = 0;




void setup_wifi() {
  delay(10);
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


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
 
    File ca = SPIFFS.open("/mosquitto_or.der", "r"); //replace ca.crt eith your uploaded file name
  if (!ca) {
   Serial.println("Failed to open ca file");
  }
  else
 Serial.println("Success to open ca file");


    
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client1")) {
      Serial.println("connected");
      if(espClient.loadCACert(ca))
  Serial.println("loaded");
  else
 Serial.println("not loaded");
      
      // Once connected, publish an announcement...
      client.publish("outTopic", "Hello from UITA!");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  setup_wifi();
  delay(1000);
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

//File ca = SPIFFS.open("/mosquitto_or.der", "r"); //replace ca.crt eith your uploaded file name
//  if (!ca) {
//   Serial.println("Failed to open ca file");
//  }
//  else
// Serial.println("Success to open ca file");
//
//if(espClient.loadCertificate(ca))
//  Serial.println("loaded");
//  else
// Serial.println("not loaded");


  client.setServer(mqtt_server, 8883);
client.setCallback(callback);

}



void loop() {

  if (!client.connected()) {
    reconnect(); 
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Hello from UITA #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
