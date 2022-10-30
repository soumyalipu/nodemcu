#include<ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.softAP("nodemcu","12345678");
  Serial.print("Device IP is:");
  Serial.println(WiFi.softAPIP());
  pinMode(D0,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Number of device is :");
 
  if(WiFi.softAPgetStationNum()>0){
      digitalWrite(D0,1);
    }
  if(WiFi.softAPgetStationNum()==0){
      digitalWrite(D0,0);
    }
  
 
}
