//lectre -09
//This code measures the distance between the cap of dustbin 
// and the garbage and notify via sms once the dustbin gets full

//Code provided by UrduITAcademy
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;


String request_string;

HTTPClient http;


const int trigPin = 2; //D4  //Wemos pin where we connect th trigger pin
const int echoPin = 0; //D3  //Wemos Pin where we connect echoPin 

long duration; 
int distance; 
//The Pin declaration and Wifi Connection part is made in setup function
void setup() {
  pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT); 
 Serial.begin(9600); 
 WiFi.disconnect();
   WiFi.begin("Learner","wilco@07");
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.println("Connecting to ...");
    delay(300);
}}

void loop() {
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2);       
 digitalWrite(trigPin, HIGH); //send two pulses of Ultrasonic waves
                            //with a delay of 10 microseconds
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW); 
//the echopin will automatically receive the pulse sent by trigger pin

 duration = pulseIn(echoPin, HIGH); //returns duration in microsecond
 //calculate the distance using speed of sound and time measured
 distance = (duration*.0343)/2; // speed of sound in cm per micro-second
 Serial.print("Distance: "); 
 Serial.println(distance); 

 //beginning to send data to Nexmo Cloud
 if (client.connect("api.thingspeak.com",80)) {
  //change the below API wih your own - you will get in your Nexmo account
      request_string ="http://api.thingspeak.com/apps/thinghttp/send_request?api_key=2TL7CJG8DAJMDSLF&distance=";
      request_string+="Dustbin is full";
      if (distance <= 10){
      http.begin(request_string);
      http.GET();
      http.end();
       Serial.println("request sent!");
      }
 delay(100); 
//The thingSpeak setup is shown in lecture-09 Video at UrduITAcademy
}}
