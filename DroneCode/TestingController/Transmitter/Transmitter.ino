#include <WiFi.h>
#include <esp_now.h>
//Pink Address: E4:65:B8:DA:34:04
//Non Collored Address: D8:13:2A:73:9B:60
//Replacement NonCollored reciever because the last one burned:
//e4:65:b8:d8:bc:e0

//Transmitter code/ Initiator 
//this will be the pink esp32

int int_value;
float float_value;
bool bool_value = true;

uint8_t broadcastAddress[] = {0xE4, 0x65, 0xB8, 0xD8, 0xBC, 0xE0}; //reciever MAC address

//In order to send data they must be structured in a struct
//change the struct to change the data that we want to send in our case it will prob just be 4 integers
//represenitng the 4 motors
typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

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
 
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  delay(1000);
}
 
 int PotOne, PotTwo, PotThree, PotFour;
 int minThrottleDuty = 30; //this represents the signal that emulates the 1000ms pwm signal that creates min throttle


void loop() {

  PotOne = analogRead(36);
  PotTwo = analogRead(39);
  PotThree = analogRead(34);
  PotFour = analogRead(35);
  //converts from regular potentiometer values (0 - 4095) to PWM duty cycle percentages (0 - 255)
  myData.a = map(PotOne, 0, 4095, minThrottleDuty, 255);
  myData.b = map(PotTwo, 0, 4095, minThrottleDuty, 255);
  myData.c = map(PotThree, 0, 4095, minThrottleDuty, 255);
  myData.d = map(PotFour, 0, 4095, minThrottleDuty, 255);
  Serial.print(myData.a);
  Serial.print(" ");
  Serial.print(PotTwo);
  Serial.print(" ");
  Serial.print(PotThree);
  Serial.print(" ");
  Serial.print(PotFour);
  Serial.println(" ");
  
  //Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(100);
}
