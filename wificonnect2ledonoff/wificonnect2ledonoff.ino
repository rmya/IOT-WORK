#include <ESP8266WiFi.h>

// Add wifi access point credentiaals
const char* ssid     = "******";     //your wifi name
const char* password = "*******";     //your password

WiFiServer server(80);// Set port to 80


String header; // This storees the HTTP request

// Declare the pins to which the LEDs are connected 
int greenled = D1;
int redled = D2; 

String greenstate = "off";// state of green LED
String redstate = "off";// state of red LED


void setup() {
  Serial.begin(115200);
 // Set the pinmode of the pins to which the LEDs are connected and turn them low to prevent flunctuations
  pinMode(greenled, OUTPUT);
  pinMode(redled, OUTPUT);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
  //connect to access point
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// this will display the Ip address of the Pi which should be entered into your browser
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /green/on") >= 0) {
              Serial.println("green on");
              greenstate = "on";
              digitalWrite(greenled, HIGH);
            } else if (header.indexOf("GET /green/off") >= 0) {
              Serial.println("green off");
              greenstate = "off";
              digitalWrite(greenled, LOW);
            } else if (header.indexOf("GET /red/on") >= 0) {
              Serial.println("red on");
              redstate = "on";
              digitalWrite(redled, HIGH);
            } else if (header.indexOf("GET /red/off") >= 0) {
              Serial.println("red off");
              redstate = "off";
              digitalWrite(redled, LOW);
            }
       
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>green - State " + greenstate + "</p>");
            // If the green LED is off, it displays the ON button       
            if (greenstate == "off") {
              client.println("<p><a href=\"/green/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/green/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>red - State " + redstate + "</p>");
            // If the red LED is off, it displays the ON button       
            if (redstate == "off") {
              client.println("<p><a href=\"/red/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/red/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
