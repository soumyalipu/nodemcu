#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL7m7Cn-M3"
#define BLYNK_DEVICE_NAME "testCopy"
#define BLYNK_AUTH_TOKEN "MSk22hO6o90iFmmOvjsvRq63I3zW_9EY"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "rout-2g";
char pass[] = "Rout@1234";

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
