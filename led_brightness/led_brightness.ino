void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  analogWrite(2,255);
//  delay(500);
//  analogWrite(2,125);
//  delay(500);
//  analogWrite(2,0);
//  delay(500);
  for(int i=0;i<256;i++){
      analogWrite(2,i);
      delay(5);
      Serial.println(i);
    }
  for(int i=255;i>0;i--){
      analogWrite(2,i);
      delay(5);
      Serial.println(i);
    } 
}
