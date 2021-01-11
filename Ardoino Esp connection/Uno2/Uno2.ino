//https://www.hackster.io/RoboticaDIY/send-data-from-arduino-to-nodemcu-and-nodemcu-to-arduino-17d47a#
#include "DHT.h"
#include <SoftwareSerial.h>
#define DHTPIN 2

#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

SoftwareSerial espSerial(5, 6);
DHT dht(DHTPIN, DHTTYPE);
String str;
void setup(){
Serial.begin(115200);
espSerial.begin(115200);
dht.begin();
delay(2000);
}
void loop()
{
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
Serial.print("H: ");
Serial.print(h);
Serial.print("% ");
Serial.print(" T: ");
Serial.print(t);
Serial.println("C");
str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
espSerial.println(str);
delay(1000);
}
