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
  Serial.begin(9600);

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
  //ledc attatch parameters: pin num, freq, resolution
  //sets up the pwm signal on all 4 esc
  //must be 24000 frequency to work with bl_heli_s ESC
  ledcAttach(26, 24000, 8);
  ledcAttach(25, 24000, 8);
  ledcAttach(33, 24000, 8);
  ledcAttach(32, 24000, 8);
}

// Callback function executed when data is received
void OnDataRecv(const esp_now_recv_info_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(len);
  //group controled
  //writes a duty cycle of 30 to 255 to each pin
  //30 is min throttle frequency
  ledcWrite(26, myData.a);
  ledcWrite(25, myData.a);
  ledcWrite(33, myData.a);
  ledcWrite(32, myData.a);


  //individually controlled by potentiometer
  // ledcWrite(26, myData.a);
  // ledcWrite(25, myData.b);
  // ledcWrite(35, myData.c);
  // ledcWrite(34, myData.d);
}

void loop() {
}