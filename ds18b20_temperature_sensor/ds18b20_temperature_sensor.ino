#include<DallasTemperature.h>
#include<OneWire.h>
#define temperaturePin 4
OneWire onewire(temperaturePin);
DallasTemperature sensor(&onewire);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.requestTemperatures();
  Serial.print("Temperature is :");
  Serial.println(sensor.getTempCByIndex(0));
  delay(1000);
}
