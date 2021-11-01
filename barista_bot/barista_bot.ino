int ledpin = 13;
int voltage_read = A0;
double temp;
void setup() {
  Serial.begin(9600);
  
}

void loop() {
   temp = analogRead(A0);
   Serial.println(analogRead(A0));
   if(temp > 80){
    // analog reading of 80 is when the water temp is slightly less than 94 deg C
      digitalWrite(ledpin, HIGH);
   } else{
      digitalWrite(ledpin, LOW);
   }
}
