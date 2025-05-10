#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin

int currentXAngle;
int totalAdjustment;

void setup() {
  // Attach the ESC on pin 9
  currentXAngle = 0;
  totalAdjustment = 0;
  Serial.begin(115200);
  ESC.attach(9,1000,1500); // (pin, min pulse width, max pulse width in microseconds) 
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  // if (!mpu.begin()) {
  //   Serial.println("Failed to find MPU6050 chip");
  //   while (1) {
  //     delay(10);
  //   }
  // }

  // mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  // mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  // mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("done");
  delay(100);
}

void loop() {
  
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 1000, 1500);   // scale it to use it with the servo library (value between 0 and 180)
  //the actual value for this esc is 35 = min puls and max is something idk (temp is 215)
  //in microseconds it is def above 1000
     // Send the signal to the ESC

  
  /* Get new sensor events with the readings */
  // sensors_event_t a, g, temp;
  // mpu.getEvent(&a, &g, &temp);


  Serial.print("Angle:");
  // currentXAngle = a.acceleration.y;
  

  // if(currentXAngle < -5) {
  //   totalAdjustment += currentXAngle;
  // }
  // else if(currentXAngle > 5) {
  //   totalAdjustment += currentXAngle;
  // }
  // potValue += totalAdjustment;
  // if(potValue > 995 && potValue < 1005) {
  //   potValue = 1000;
  // }
  ESC.writeMicroseconds(potValue); 

  // Serial.print(currentXAngle);
  // Serial.print(" totalAdjustment:");
  // Serial.print(totalAdjustment);
  // Serial.print(" Freqeuncy: ");
  Serial.println(potValue);

  //if this is too fast then the board might burnout
  delay(100);
}