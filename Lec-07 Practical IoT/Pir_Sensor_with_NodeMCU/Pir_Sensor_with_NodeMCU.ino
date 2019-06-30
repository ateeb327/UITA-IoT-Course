//Lecture 07
//Code Provided by UrduITAcademy
int sensor = 13; //digital pin D7 on NodeMCU

void setup() {
  pinMode(sensor, INPUT);
     Serial.begin(115200); //baud rate

}

void loop() {
  long state = digitalRead(sensor);
  if(state == HIGH){ 
      Serial.println("Motion Detected!"); //display "Motion detected"
      delay(1000);   //put the delay of 1 second
    }
   else if(state == LOW){
      Serial.println("Motion Absent!");  //display "Motion absent" on Serial
      delay(1000);    
    }
    //After uploading, Open 'Serial monitor' from 'Tools' menu
    //set baud rate to '115200' and observe the output
}
