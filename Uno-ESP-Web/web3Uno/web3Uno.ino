#include "DHT.h"
#include <SoftwareSerial.h>
#define DHTPIN A0

#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

SoftwareSerial espSerial(5,6);

DHT dht(DHTPIN, DHTTYPE);
String str;

void setup(){
Serial.begin(9600);
espSerial.begin(9600);
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
//str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
//espSerial.println(str);

//str = String(t);
espSerial.println(t);


delay(1000);
}
