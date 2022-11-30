#include<ESP8266WiFi.h>
#include<AdafruitIO_WiFi.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
///for wifi credentials
#define WIFI_SSID ""
#define WIFI_PASS ""

//adafruit login credentials
#define IO_USERNAME  ""
#define IO_KEY       ""

AdafruitIO_WiFi io(IO_USERNAME,IO_KEY,WIFI_SSID,WIFI_PASS);
AdafruitIO_Feed *tempData =io.feed("temp nodemcu");
AdafruitIO_Feed *humiData =io.feed("humi nodemcu");
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
  tempData->save(t);
  humiData->save(h);
  }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  io.connect();
  while(io.status()<AIO_CONNECTED){
    Serial.print(".");
    delay(500);    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  io.run();
  dhtData();
  delay(15000);

}
