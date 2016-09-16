#include <ESP8266WiFi.h>
#include <String.h>
// Timeout
#define TIME_OUT 5000

// Authentication
const char* ssid = "m2mk";
const char* pass = "@star1234@";

// Host and Path
const char* host = "api.twitch.tv";
const char* path = "/kraken/channels/arteezy";





void setup() {
  // Initialize Serial
  Serial.begin(115200);

  // Delay 10ms
  delay(10);

  // Notifying User
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);
  

  // Start Wifi
  WiFi.begin(ssid,pass);

  // WiFi Status
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");    
  }

  // After Connection 
  Serial.println("");
  Serial.print("WiFi Connected ");
  Serial.print(ssid);
  Serial.print(" with IP ");
  Serial.println(WiFi.localIP());

  // Wait
  delay(100);
  

   

}

void loop() {
  // WiFi client use WiFiClientSecure for SSL with PORT = 443
  WiFiClientSecure client;

  // Port
  const int port = 443;
  
  // Connect The Client To The Host
  if(!client.connect(host,port))
  {
    Serial.println("Connection failed");
    return;    
  }

  // Sending Request To The Server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: "       + host + "\r\n"          +
               "Connection: close\r\n\r\n"             );

  // Setting Client Timeout
  unsigned long timeout = millis();
  while(client.available() == 0)
  {
    if(millis() - timeout > TIME_OUT)
    {
      Serial.println("Client Timeout");
      client.stop();
      return; 
    }
  }

  // Read The Response 
  while(client.available())
  {
    String line = client.readString();
    Serial.println(line.substring(line.lastIndexOf('\r')));
  }
  
  // Delay 10 sec
  delay(10000);
  
}













