#include<ESP8266WiFi.h>
#include<AdafruitIO_WiFi.h>
///for wifi credentials
#define WIFI_SSID ""
#define WIFI_PASS ""

//adafruit login credentials
#define IO_USERNAME  ""
#define IO_KEY       ""

AdafruitIO_WiFi io(IO_USERNAME,IO_KEY,WIFI_SSID,WIFI_PASS);
AdafruitIO_Feed *data =io.feed("random data");
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  io.connect();
  while(io.status()<AIO_CONNECTED){
    Serial.print(".");
    delay(500);    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  io.run();
  int x=random(20,500);
  data->save(x);
  Serial.print("Data sent");
  Serial.println(x);
  delay(2000);

}
