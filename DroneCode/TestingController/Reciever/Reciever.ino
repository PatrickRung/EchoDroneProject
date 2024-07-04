//This will be the code for the reciever so the one with no pink

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

// Define a data structure
typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
} struct_message;

// Create a structured object
struct_message myData;
int motorOneSpeed, motorTwoSpeed, motorThreeSpeed, motorFourSpeed; 


// Callback function executed when data is received
void OnDataRecv(const esp_now_recv_info_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Character Value: ");
  Serial.println(myData.a);
  motorOneSpeed = myData.a;
  Serial.print("Integer Value: ");
  Serial.println(myData.b);
  motorTwoSpeed = myData.b;
  Serial.print("Float Value: ");
  Serial.println(myData.c);
  motorThreeSpeed = myData.c;
  Serial.print("Boolean Value: ");
  Serial.println(myData.d);
  motorFourSpeed = myData.d;
  Serial.println();
  analogWrite(26, motorOneSpeed);
  analogWrite(26, motorTwoSpeed);
  analogWrite(26, motorThreeSpeed);
  analogWrite(26, motorFourSpeed);
}

void setup() {
  motorOneSpeed = 0;
  motorTwoSpeed = 0;
  motorThreeSpeed = 0;
  motorFourSpeed = 0;
  // Set up Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else {
    Serial.println("ESP-NOW setup complete");
  }

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(26, OUTPUT);
}

void loop() {

}