#include<ESP8266WiFi.h>
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
  Serial.print("Device IP is:");
  Serial.println((WiFi.localIP().toString()));
  Serial.print("Gateway IP is :");
  Serial.println((WiFi.gatewayIP().toString().c_str()));
}

void loop() {
  // put your main code here, to run repeatedly:

}
