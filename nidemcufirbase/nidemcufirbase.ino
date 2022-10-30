#include<ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define API_KEY "AIzaSyBiRAwqTyqm5v_jGo9pBgCDHF88qIPwJB0"
#define DATABASE_URL "http://testnodemcu-c4086-default-rtdb.firebaseio.com/"
//Define Firebase Data object
FirebaseData fbdo;
#include<DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK=false;
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
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  pinMode(D0,OUTPUT);
  dht.begin();
}

int intData1=0;
String stringData1="";
float floatData1=0;
float t;
float h;
void loop() {
  if(Firebase.ready() && signupOK){
      t=dht.readTemperature();
      h=dht.readHumidity();
      if(isnan(t) || isnan(h)){
        Serial.println("Data is not available");
        return;
        }
      Serial.print("temperature:");
      Serial.print(t);
      Serial.print("  ");
      Serial.print("humidity:");
      Serial.println(h);
    //for sending Temperature data
      Firebase.RTDB.setFloat(&fbdo, "DHT11/temperature", t);
      Firebase.RTDB.setFloat(&fbdo, "DHT11/Humidity", h);






/////////for control led and set int and string data
//      Firebase.RTDB.setInt(&fbdo, "text/int", count);
//      Firebase.RTDB.setString(&fbdo, "nodemcu/string", "Hello from NodeMCU");



//        if (Firebase.RTDB.getFloat(&fbdo, "/random/data")) {
//        if (fbdo.dataType() == "float") {
//          floatData1 = fbdo.floatData();
////          Serial.print(floatData1);
////          Serial.print("  ");
//        }
//      }
//      if (Firebase.RTDB.getInt(&fbdo, "/text/int")) {
//        if (fbdo.dataType() == "int") {
//          intData1 = fbdo.intData();
////          Serial.print(intData1);
////          Serial.print("  ");
//        }
//      }
      if (Firebase.RTDB.getString(&fbdo, "/nodemcu/string")) {
        if (fbdo.dataType() == "string") {
          stringData1 = fbdo.stringData();
          Serial.println(stringData1);
          
        }
      }
      if(stringData1=="ON"){
          Serial.println("LED is ON");
          digitalWrite(D0,1);
        }
      if(stringData1=="OFF"){
          Serial.println("LED is OFF");
          digitalWrite(D0,0);
        }
    }
  delay(1000);
}
