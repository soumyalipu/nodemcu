#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include <ArduinoJson.h>
String URL="http://api.thingspeak.com/channels/1873271/fields/4.json?api_key=2JRIHZLS3N9Q34D4&results=1";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.disconnect();
  delay(2000);
  Serial.print("Start connection");
  WiFi.begin("rout-2g","Rout@1234");
  while((!(WiFi.status()== WL_CONNECTED))){
      delay(200);
      Serial.print("..");
    }
  Serial.println("Connected");
  pinMode(D0,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  HTTPClient http;
  http.begin(client,URL);
  int responsecode=http.GET();
  String data=http.getString();
//  Serial.println(data);
  DynamicJsonDocument doc(768);
  DeserializationError error = deserializeJson(doc, data);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  JsonObject feeds_0 = doc["feeds"][0];
  String led_status = feeds_0["field4"];
//  Serial.print("Led status is");
//  Serial.println(led_status);
  if(led_status=="1"){
      Serial.println("Turn On led");
      digitalWrite(D0,0);
    }
  if(led_status=="0"){
      Serial.println("Turn OFF led");
      digitalWrite(D0,1);
    }
  http.end();
//  delay(15000);
}
