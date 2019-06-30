//Lecture-07
//This code read the Pir Motion sensor state and 
//sends it to thingspeak cloud

//Code provided by UrduITAcademy

//include necessary Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  
WiFiClient client;

int sensor = 13;  // Digital pin D7
int var; 
String request_string;
String thingSpeakAddress= "http://api.thingspeak.com/update?"; //Save the api 
//link in this variable

HTTPClient http;

void setup() {
  pinMode(sensor, INPUT); //declare sensor pin as input
    Serial.begin(115200); 
    WiFi.disconnect();
   WiFi.begin("Nerd","wilco@07");  //enter wifi credentials to which the NodeMCU will connect
  while ((!(WiFi.status() == WL_CONNECTED))){  //if wifi gets connected 
    delay(300);                //make a delay of 300ms in order to Obtain IP Address
}
}
void loop() {
  long state = digitalRead(sensor);
    if(state == HIGH) {   //if the motion is detected, make the var=1
       var = 1;
      Serial.println("Motion detected!");
     thingspeakupdate();  //custom function written below
      delay(1000);
    }
    else if(state == LOW) {
      var = 0;
      Serial.println("Motion absent!");  //display on Serial monitor
      thingspeakupdate();
      delay(1000);
      }

}
//Below function will call the api and update thingspeak channel. 
//It can be called anywhere in loop function
void thingspeakupdate(){
     if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "api_key="; //https://api.thingspeak.com/update?api_key=
 //Be sure to change below with your OWN thingSpeak Write API Key
      request_string += "PG6387BGGA6GOM5P"; //https://api.thingspeak.com/update?api_key=PG6387BGGA6GOM5P
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += var;
      http.begin(request_string); //begin sending HTTP reuest
      http.GET(); //use http get method
      http.end();  //close http connection once the request is made
      delay(1000);

    }
}
