void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(D0,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int x=analogRead(A0);
//  Serial.println(x);
  if(x>=550){
      Serial.println("Turn off street light");
      digitalWrite(D0,1);//for turn of led
    }
  else{
    Serial.println("Turn on street light");
    digitalWrite(D0,0);
    }

}
