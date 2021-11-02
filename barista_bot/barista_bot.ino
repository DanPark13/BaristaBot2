#include <Servo.h>

Servo container1;
int ledpin = 13;
int voltage_read = A0;
int c1ButtonPin = 12;
int container1_pos = 0;

int v_out;
int pushTime;

void setup() {
  Serial.begin(9600);
  container1.attach(2);
  container1.write(container1_pos);
  delay(1000);
}

void loop() {
   v_out = analogRead(A0);
   if(digitalRead(c1ButtonPin) == HIGH && pushTime <= 2000+millis()) {
      container1_pos += 20;
      container1.write(container1_pos);
      pushTime = millis();
   }
   Serial.println(container1_pos);
   if(v_out > 80){
    // analog reading of 80 is when the water temp is slightly less than 94 deg C
      digitalWrite(ledpin, HIGH);
   } else{
      digitalWrite(ledpin, LOW);
   }
   
}
