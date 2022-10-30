#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL7m7Cn-M3"
#define BLYNK_DEVICE_NAME "testCopy"
#define BLYNK_AUTH_TOKEN "MSk22hO6o90iFmmOvjsvRq63I3zW_9EY"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "rout-2g";
char pass[] = "Rout@1234";

BlynkTimer timer; 
//void randomData(){
//    Serial.println(random(0,100));
//    Blynk.virtualWrite(V0, random(0,100));
// }
//BLYNK_WRITE(V1)
//{   
//  int value = param.asInt(); // Get value as integer
//  digitalWrite(D0,value);
//}
void dhtData(){
  float t=dht.readTemperature();
  float h=dht.readHumidity();
  if(isnan(t) || isnan(h)){
    Serial.println("Data is not available");
    return;
    }
  Serial.print("temperature:");
  Serial.print(t);
  Serial.print("  ");
  Serial.print("humidity:");
  Serial.println(h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, dhtData); 
  pinMode(D0,OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
}
