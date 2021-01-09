#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP8266 Kart MAC Adresi:  ");
  Serial.println(WiFi.macAddress());
}
 
void loop(){
  
    Serial.print("ESP8266 Kart MAC Adresi:  ");
  Serial.println(WiFi.macAddress());
}
// esp 1 mac : 40:f5:20:35:b7:2c
//esp 2 mac 40:f5:20:37:9e:0f
