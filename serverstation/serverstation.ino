#include<ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
WiFiServer server(80);
String message="";
void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
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
  server.begin();
  dht.begin();
}
String data="";
void loop() {
  float t=dht.readTemperature();
  float h=dht.readHumidity();
//  if(isnan(t) || isnan(h)){
//    Serial.println("Data is not available");
//    return;
//    }
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client) { return; }
  while(!client.available()){  delay(1); }
  message=(client.readStringUntil('\r'));
  message.remove(0,5);
  message.remove(message.length()-9,9);
  Serial.println(message);
  if(message=="ON"){
      Serial.println("led is ON");
      digitalWrite(D0,0);
    }
  if(message=="OFF"){
      Serial.println("led is OFF");
      digitalWrite(D0,1);
  }
  if(message=="temp"){
      data= String(t,2);
    }
  if(message=="Humi"){
      data= String(h,2);
    }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("</head>");
    client.println("<body>");
      client.println("<h1 style=""color:#000099"">");
      client.println("Control Pannel");
      client.println("</h1>");
      client.println("<h3>");
      client.println(data);
      client.println("</h3>");
      client.println("<a href=");
      client.println("ON");
      client.println("><button>");
      client.println("ON");
      client.println("</button></a>");
      client.println("<a href=");
      client.println("OFF");
      client.println("><button>");
      client.println("OFF");
      client.println("</button></a>");
      client.println("<a href=");
      client.println("temp");
      client.println("><button>");
      client.println("Temperature");
      client.println("</button></a>");
      client.println("<a href=");
      client.println("Humi");
      client.println("><button>");
      client.println("HUmidity");
      client.println("</button></a>");
      
      
    client.println("</body>");
    client.println("</html>");
  
  delay(1);
  client.flush();
}
