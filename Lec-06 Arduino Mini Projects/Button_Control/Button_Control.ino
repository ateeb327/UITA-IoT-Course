//Arduino will check the state of button
// if the button is pressed, Arduino will turn on the LED

  int led = 9;   //At pin 9 we have attached an LED
  int button = 2; //At pin 2, we have attached a push button
void setup() {
  //setup code runs once
    pinMode(led,OUTPUT);//LED will provide output in the form of Light
                         //so we declared LED pin as an input
    pinMode(button,INPUT);  // button pin will take the input

}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(button)==HIGH){  //digialRead is a builtin function
         digitalWrite(led,HIGH);    //used to read from an Arduino pin
      }
      else{
         digitalWrite(led,LOW);   //digitalWrite is a builtin function
        }                         //used to write a digital signal to an Arduino pin
}
