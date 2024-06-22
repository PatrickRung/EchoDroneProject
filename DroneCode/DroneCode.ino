#include <Servo.h>

Servo ESC;
void setup() {
  Serial.begin(9600);
  Serial.println("started!");
  //sets up and arms the ESC using PWM frequencies meaning that we are using 1000 as
  //min throttle and 2000 as max. The 9 represents the pin that we use as a signal.
  //THIS MUST BE THE FIRST LINE IN SETUP AND MUST BE FOLLOWED BY 5000 DELAY. Why idk
}


void loop() {
  while (Serial.available() > 0) {
    int val = Serial.parseInt();
    if (val == 1) {
      Serial.println("arming sequence initiated");
      ESC.attach(9, 1000, 2000);
      ESC.writeMicroseconds(2000);
      delay(1000);
      ESC.writeMicroseconds(1000);
      delay(5000);
      Serial.println("done");

    } else if (val == 2) {
      Serial.println("spin at 20% speed");
      ESC.writeMicroseconds(1200);
      delay(5000);
      Serial.println("done");
      ESC.write(1000);
    } 
    else if(val == 3){
      Serial.println("detatching");
      ESC.detach();
    }

  }
}
