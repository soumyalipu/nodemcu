void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
  for(int i=0;i<5;i++){
      digitalWrite(D0,1);
      delay(1000);
      digitalWrite(D0,0);
      delay(1000);
    }
   digitalWrite(D0,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
