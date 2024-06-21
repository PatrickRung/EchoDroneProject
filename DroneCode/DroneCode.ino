#include <Servo.h>


Servo ESC;

  
void setup() {
  ESC.attach(9, 1000, 2000); //sets up and arms the ESC using PWM frequencies meaning that we are using 1000 as min throttle and 2000 as max. The 9 represents the pin that we use as a signal. THIS MUST BE THE FIRST LINE IN SETUP AND MUST BE FOLLOWED BY 5000 DELAY. Why idk
  //arming sequence
  Serial.begin(9600);
  Serial.println("Max throttle");
  delay(5000);
  ESC.writeMicroseconds(2000);
  delay(1000);
  Serial.println("Min throttle");
  ESC.writeMicroseconds(0);
  delay(5000);

  
  //This was all testing to see which settings were real and which ones were lies but 1100 - 1200 should be the range of signals that work.
   ESC.writeMicroseconds(1100);
   //Serial.println("Testing 1100");
  // delay(5000);
  // ESC.writeMicroseconds(1200);
  // Serial.println("Testing 1200");
  // delay(5000);
  // ESC.writeMicroseconds(1300);
  // Serial.println("Testing 1300");
  // delay(5000);
  // ESC.writeMicroseconds(1400);
  // Serial.println("Testing 1400");
  // delay(5000);
  // ESC.writeMicroseconds(1500);
  // Serial.println("Testing 1500");
  // delay(5000);
  // ESC.writeMicroseconds(1600);
  // Serial.println("Testing 1600");
  // ESC.writeMicroseconds(1700);
  // Serial.println("Testing 1700");
 


}


void loop() {
  
}
