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

void setup() {
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

// Callback function executed when data is received
void OnDataRecv(const esp_now_recv_info_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(len);
  Serial.print("Character Value: ");
  Serial.println(myData.a);
  Serial.print("Integer Value: ");
  Serial.println(myData.b);
  Serial.print("Float Value: ");
  Serial.println(myData.c);
  Serial.print("Boolean Value: ");
  Serial.println(myData.d);
  Serial.println();
  analogWrite(26, myData.a);
  analogWrite(26, myData.b);
  analogWrite(26, myData.c);
  analogWrite(26, myData.d);
}

void loop() {

}