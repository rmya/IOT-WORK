//worked***************************************************
#include "DHT.h"            //including the dht22 library
#include "LiquidCrystal.h"
#define DHTPIN 9                //Declaring pin 9 of arduino for the dht22
#define DHTTYPE DHT22         //Defining which type of dht22 we are using (DHT22 or DHT11)
DHT dht(DHTPIN, DHTTYPE);    //Declaring a variable named dht 
LiquidCrystal lcd(7,6,5,4,3,2); // Initializing the LCD pins.
void setup() { //Data written in it will only run once
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
dht.begin(); //This command will start to receive the values from dht22
}
void loop() { //Data written in it will run again and again
lcd.clear();
float hum = dht.readHumidity(); //Reading the humidity and storing in hum
float temp = dht.readTemperature(); //Reading the temperature as Celsius and storing in temp
// Check if any reads failed and exit early (to try again).
if (isnan(hum) || isnan(temp)) {
lcd.print("Failed to read");
delay(1000);
return;
}
lcd.setCursor(0,0); //Setting the cursor at the start of the LCD
lcd.print("Temp.: "); //Writing the temperature on the LCD
lcd.print(temp); //Writing the value of temperature on the LCD
lcd.print(" C");
lcd.setCursor(0,1); //setting the cursor at next line
lcd.print("Humi.: "); //Writing the humidity on the LCD display
lcd.print(hum); //Writing the humidity value stored in hum on the LCD display
lcd.print(" %");
delay(2000);
}
