#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


BlynkTimer timer; 

BLYNK_WRITE(V1)
{   
  int value = param.asInt(); // Get value as integer
  myservo.write(value);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, dhtData); 
  myservo.attach(2); 
}

void loop()
{
  Blynk.run();
  timer.run();
}
