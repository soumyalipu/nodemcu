#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#include <ArduinoJson.h>
String URL="http://api.thingspeak.com/channels/1873271/fields/6.json?api_key=2JRIHZLS3N9Q34D4&results=1";

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
  dht.begin();
}
String dhtdata(){
    float t=dht.readTemperature();
    float h=dht.readHumidity();
    String newUrl=URL+String(t)+"&field3="+String(h);
    return newUrl;
  }
void loop() {
  // put your main code here, to run repeatedly:
  
  WiFiClient client;
  HTTPClient http;
  String newUrl=dhtdata();
  http.begin(client,URL);
  int responsecode=http.GET();
  String data=http.getString();
//Serial.println(data);
  DynamicJsonDocument doc(786);
  DeserializationError error = deserializeJson(doc, data);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
//  Serial.println(data);
  
  JsonObject feeds_0 = doc["feeds"][0];
  String feeds_0_field6 = feeds_0["field6"];
//  const char* feeds_0_created_at = feeds_0["created_at"]; // "2022-09-27T15:39:18Z"
//  int feeds_0_entry_id = feeds_0["entry_id"];
//  Serial.println(feeds_0_created_at);
//  Serial.println(feeds_0_entry_id);
  Serial.println(feeds_0_field6);
  http.end();
  delay(15000);
}
