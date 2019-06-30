/*
  Fade means LED will slowly start glowing and will reach to its maximum 
  brightness level. 
  After reaching its max brightness level, it will continue to slowly
  lose its brightness until the brightness will become zero. 

  LED must be attached to PWM(Pulse width modulation) supported pin.
*/
//Ccde provided by UrduITAcademy

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is at the start
int fadeAmount = 5;    // amount by which the fading will occur

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
//When the loop method runs 1st time the brightness will become 0+5 =5
  
  // reverse the direction of the fading at the ends of the fade:
  //i-e when LED will reach its ma brightness level it will now
  //start to lose its brightness
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);   //delay is the function use to pause our code for the 
               //given milliseconds
}
