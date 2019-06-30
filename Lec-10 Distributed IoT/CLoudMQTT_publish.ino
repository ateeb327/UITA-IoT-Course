/*
Code Provided by UrduITAcademy

Install necessary Libraries First
This example demonstrates MQTT protocol. It takes values from 
DHT11 Temperature and humidity sensor and publish those to a MQTT broker. 
A subscriber MCU rceives the values and turn on an LED if values
exceed from a certain threshhold. 
*/
//This code publishes 1 to the topic "UITAtopic" if the temp or
// humidity exceeds a specific value 

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>;

//constants
#define DHTPIN 2     // what pin we're connected to -Wemos Pin D4
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor 

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
WiFiClient espClient;
PubSubClient client(espClient);
// Update these with values suitable for your network.

const char* ssid = "Learner";
const char* password = "wilco@07";
const char* mqtt_server = "broker.hivemq.com";

void setup() {  // Initialize the 12 pin as an output-NodeMCu Pin D6
  Serial.begin(115200);
  dht.begin();             //initialize DHT sensor
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

//WiFi Setup Function
void setup_wifi() {
  WiFi.mode(WIFI_STA);
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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) { //cloud mqtt: gqbybsmm,ziEEPqVW0rDH
      Serial.println("connected");
      // Once connected, publish an announcement...
      if(temp >= 15 || hum >= 100){
      client.publish("UITAtopic", "1");//publish 1 if temp or humidity increases
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//function to read temperature and humidity from DHT sensor
void dht_read(){
  hum = dht.readHumidity();
    temp= dht.readTemperature();
  }
//DHT function ends here


void loop() {
  dht_read();
  print_dht();
  
  if (!client.connected()) {
    reconnect();
  }
  //client.loop();
  
    Serial.print("Published message");
    //Serial.println(msg);
    if(temp >= 15 || hum >= 100){
    client.publish("UITAtopic", "1");  //publish message on specific topic
  }
}

//Function to print DHT values to Serial monitor
void print_dht(){
  Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(1000);
  }
