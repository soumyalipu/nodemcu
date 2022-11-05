#include<ESP8266WiFi.h>
#include<AdafruitIO_WiFi.h>
///for wifi credentials
#define WIFI_SSID "rout-2g"
#define WIFI_PASS "Rout@1234"

//adafruit login credentials
#define IO_USERNAME  "soumya1234"
#define IO_KEY       "f59655943a284c748e2d6b9576cf691e"

AdafruitIO_WiFi io(IO_USERNAME,IO_KEY,WIFI_SSID,WIFI_PASS);
AdafruitIO_Feed *ledStatus =io.feed("nodemcu led");
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  io.connect();
  ledStatus->onMessage(handleMessage);
  while(io.status()<AIO_CONNECTED){
    Serial.print(".");
    delay(500);    
  }
  pinMode(D0,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  io.run();
//  int x=random(20,500);
//  data->save(x);
//  Serial.print("Data sent");
//  Serial.println(x);
//  delay(2000);
}
void handleMessage(AdafruitIO_Data *ledStatus) {
  Serial.print("received: ");
  Serial.println(ledStatus->toString());
  if(ledStatus->toString()=="ON"){
    digitalWrite(D0,LOW);  
  }
  if(ledStatus->toString()=="OFF"){
    digitalWrite(D0,HIGH);  
  }
}
