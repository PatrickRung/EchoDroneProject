#include <Servo.h>


Servo ESC;


void setup() {
Serial.begin(9600);
}


void loop() {
  while (Serial.available() > 0) {
    int val = Serial.parseInt();
    if (val == 1) {
      Serial.println("arming sequence initiated");
      ESC.attach(A1, 1000, 2000);
      delay(500);
      ESC.writeMicroseconds(2000);
      delay(500);
      ESC.writeMicroseconds(1000);
      delay(5000);
      ESC.writeMicroseconds(1000);
      Serial.println("done");

    } else if (val == 2) {
      Serial.println("spin at 10% speed");
      ESC.writeMicroseconds(1100);
      delay(1000);
      Serial.println("spin at 20% speed");
      ESC.writeMicroseconds(1200);
      delay(1000);
      Serial.println("spin at 30% speed");
      ESC.writeMicroseconds(1300);
      delay(5000);
      Serial.println("spin at 40% speed");
      ESC.writeMicroseconds(1400);
      delay(5000);
      ESC.writeMicroseconds(1000);
      Serial.println("done");
    } 
    else if(val == 3){
      Serial.println("detatching");
      ESC.detach();
    }
    
  }
}