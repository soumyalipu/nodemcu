#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include <ArduinoJson.h>
String URL="http://api.thingspeak.com/update?api_key=PB4J7UVO5MXE3JZJ&field1=";
const int trig=5;
const int echo=4;
long duration=0;
int distance=0;
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
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  HTTPClient http;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration= pulseIn(echo,HIGH);
  distance=duration*0.034 /2;
  Serial.println(distance);
  String newUrl=URL+String(distance);
  http.begin(client,newUrl);
  int responsecode=http.GET();
  String data=http.getString();
  Serial.println(data);
  http.end();
  delay(15000);
  
}
