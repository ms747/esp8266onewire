#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingSpeak.h>

#define ONE_WIRE_BUS            D4      

char ssid[] = "@@@@@";
char password[]  = "@@@@@";
WiFiClient  client;

unsigned long myChannelNumber = 89003;
const char * myWriteAPIKey = "J0CJ60OGXRQ982JF";  


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  DS18B20.begin();
  ThingSpeak.begin(client);
}

void loop() {
  DS18B20.requestTemperatures();
  float f = DS18B20.getTempCByIndex(0);
  ThingSpeak.writeField(myChannelNumber, 2, f,myWriteAPIKey);
  delay(20000);
}
