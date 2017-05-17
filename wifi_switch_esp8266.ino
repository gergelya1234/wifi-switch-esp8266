#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266Ping.h>

#define relay_pin  0

const char* ssid     = "<YOUR_SSID>";
const char* password = "<YOUR_PASSWORD>";
boolean st = false;

// Address of your wifi router
const IPAddress remote_ip(192, 168, 0, 1);


ESP8266WebServer server(80);

String webString = "";
int counter = -32767;

void handle_root() {  
  server.send(200, "text/plain", "Hello\nESP8266 webserver, commands: /on, /off, or /st");
  delay(100);
}

void setup(void) {
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(9600);  // Serial connection from ESP-01 via 3.3v console cable
  
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, HIGH);

  connect();
  
  server.on("/", handle_root);

  server.on("/on", []() { // if you add this subdirectory to your webserver call, you get text below :)
    digitalWrite(relay_pin, LOW);
    st = true;
    webString = "ON";
    Serial.println("ON\r\n");    
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });
  
  server.on("/off", []() {
    digitalWrite(relay_pin, HIGH);
    webString = "OFF";
    st = false;
    Serial.println("OFF\r\n");
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });

 server.on("/st",[](){
    if(st) {
        Serial.println("ON\r\n");
        server.send(200, "text/plain", "ON");            // send to someones browser when asked
      } else {
        Serial.println("OFF\r\n");
        server.send(200, "text/plain", "OFF");            // send to someones browser when asked
      }
  });
  
   server.on("/color", []() {                             // in case if you are connected with an arduino which controlls RGB
    String message="Null";                                // The URL should be http://<YOUR_IP>/color?c=<RGB CODE>
    if(server.argName(0)=="c") {
      message = "COLOR=" + server.arg(0);  
      Serial.println(message);
    }
    server.send(200, "text/plain", message);
  });
  server.begin();
}

void loop(void)
{
  counter = counter + 1;
  server.handleClient();
  if(counter > 32766) { //Check if still connected to your network on every 65534th cycle
    if(!Ping.ping(remote_ip, 3)) { // if not connected
      connect(); // do connect
    }
    counter = -32767;
  }
}

void connect() 
{  
  Serial.print("Connect to WiFi ");
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("");
}
