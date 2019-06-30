/*
  Project 3 - PIR motion sensor

  This sketch is written to accompany Project 3 in the Lecture-06

*/
//COde provided by UrduITAcademy

int ledpin = 9;
int inputpin = 2;
int val = 0;

void setup() {
  // declare the LED pins as outputs
  pinMode(ledpin, OUTPUT);  //declare ledpin as output
  pinMode(inputpin, INPUT);   //declare inputpin as input

}

void loop() {
   val = digitalRead(inputpin); //Read from inputPin and save the result in val
   if(val == HIGH){
    digitalWrite(ledpin,HIGH );//if there is HIGH in val, make the ledpin high
    }
    else {
      digitalWrite(ledpin,LOW); // if the val is LOW, that means no motion 
      }                        //is detected , keep the LED off by making
}                             //ledpin as LOW
