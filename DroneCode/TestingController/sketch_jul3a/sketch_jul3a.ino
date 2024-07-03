
#include "WiFi.h"
//Pink Address: E4:65:B8:DA:34:04
//Non Collored Address: D8:13:2A:73:9B:60

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);

  delay(1000);
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {


}
