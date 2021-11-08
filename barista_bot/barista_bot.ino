#include <Servo.h>

Servo container1;
int ledpin = 11;
int voltage_read = A0;
int c1ButtonPin = 12;
int container1_pos = 0;
bool backwards = false;
int v_out;
long pushTime = 0;

void setup() {
  Serial.begin(9600);
  container1.attach(2);
  container1.write(container1_pos);
  delay(1000);
}

void loop() {
   v_out = analogRead(A0);
   //Serial.print(digitalRead(c1ButtonPin) == HIGH);
   //Serial.println(500+pushTime <= millis());
  Serial.println(v_out);
   if(digitalRead(c1ButtonPin) == HIGH &&  500+pushTime <= millis()) {
      Serial.println("button pressed");
      if (backwards){
        container1_pos -= 60;
      } else{
        container1_pos += 60;
      }
      container1.write(container1_pos);
      pushTime = millis();
      if (container1_pos >= 180){
        backwards = true;
        container1_pos = 180;
      }
      if (container1_pos <= 0) {
        backwards = false;
        container1_pos = 0;
      }
   }
   // 200 for demo
   if(v_out > 250){
    // analog reading of 80 is when the water temp is slightly less than 94 deg C
      digitalWrite(ledpin, HIGH);
   } else{
      digitalWrite(ledpin, LOW);
   }
   
}
