/*
Code Provided by UrduITAcademy

Install necessary Libraries First
This example demonstrates MQTT protocol. It takes values from 
DHT11 Temperature and humidity sensor and publish those to a MQTT broker. 
A subscriber MCU rceives the values and turn on an LED if values
exceed from a certain threshhold. 
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>;


//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
// Update these with values suitable for your network.

const char* ssid = "Learner";
const char* password = "wilco@07";
const char* mqtt_server = "m14.cloudmqtt.com";

void setup() {
  pinMode(12, OUTPUT);  // Initialize the 12 pin as an output-NodeMCu Pin D6
  Serial.begin(115200);
  dht.begin();             //initialize DHT sensor
  setup_wifi();
  client.setServer(mqtt_server, 16395);
  client.setCallback(callback);
}

//WiFi Setup Function
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
//Wifi Setup Function ends here


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(12, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else if ((char)payload[0] == '0') {
    digitalWrite(12, LOW);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266SubscriberClient","gqbybsmm","ziEEPqVW0rDH")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.subscribe("UITAtopic");
      
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
 

}


