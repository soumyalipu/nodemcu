#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
//  float t=dht.readTemperature();
//  float h=dht.readHumidity();
//  if(isnan(t) || isnan(h)){
//    Serial.println("Data is not available");
//    return;
//    }
//  Serial.print("temperature:");
//  Serial.print(t);
////  Serial.print("  ");
////  Serial.print("humidity:");
//  Serial.print(h);
  if(t<=28){
    Serial.println("Turn off alaram");  
  }
  if(t>=29){
    Serial.println("Turn on Alaram");
  }
}
