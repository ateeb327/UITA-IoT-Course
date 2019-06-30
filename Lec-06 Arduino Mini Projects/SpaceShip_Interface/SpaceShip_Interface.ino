/*
  Project 2 - Spaceship Interface

  This sketch is written to accompany Project 2 in the Lecture-06

  Parts required:
  - one green LED
  - two red LEDs
  - pushbutton
  - 10 kilohm resistor
  - three 220 ohm resistors

*/
//COde provided by UrduITAcademy
// Create a global variable to hold the state of the switch. This variable is
// persistent throughout the program. Whenever you refer to switchState, you’re
// talking about the number it holds
int led1 = 9;
int led2=10;
int led3 = 11;
int button = 2;

void setup() {
  // declare the LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // declare the button pin as an input
  pinMode(button, INPUT);
}

void loop() {
  // if the button is not pressed turn on the green LED and off the red LEDs
  if (digitalRead(button) == LOW) {
    digitalWrite(led1, HIGH); //turn the red LED on pin 9 ON
    digitalWrite(led2, LOW);  // turn the green LED on pin 10 off
    digitalWrite(led3, LOW);  // turn the yellow LED on pin 11 off
  }
  // this else is part of the above if() statement.
  // if the switch is not LOW (the button is pressed) turn off the red LED and
  // blink alternatively the red yellow and green LED
  else {
    digitalWrite(led1, LOW);  // turn the red LED on pin 9 off
    digitalWrite(led2, LOW);  // turn the green LED on pin 10 off
    digitalWrite(led3, HIGH); // turn the yellow LED on pin 11 on
    // wait for a quarter second before changing the light
    delay(250);
    digitalWrite(led2, HIGH); // turn the green LED on pin 10 on
    digitalWrite(led3, LOW);  // turn the yellow LED on pin 11 off
    // wait for a quarter second before changing the light
    delay(250);
  }
}
