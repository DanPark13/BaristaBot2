#include <Servo.h>

Servo creamer;
Servo bottom_spin;
Servo sugar;
Servo actuator_servo;


int creamer_pin = 9;
int solenoid_pin = 2;
int relay_pin = 4;
int bottom_pos = 0;
int bottom_spin_pin = 5;
int sugar_pin = 3;
int thermistor_read;
int motorPin = 11;
int actuator_pin = 13;

bool started = false;
bool second_run = false;
bool water_pouring = false;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);
  creamer.attach(creamer_pin);
  sugar.attach(sugar_pin);
  bottom_spin.attach(bottom_spin_pin);
  actuator_servo.attach(actuator_pin);
  actuator_servo.write(180);
  bottom_spin.write(0);
  sugar.write(0);
  creamer.write(0);
  Serial.begin(9600);
}

void loop() {
  // code to read the button input
  if (analogRead(A1) > 1000 && !started){
    Serial.println("Hit the button!");
    started = true;
  }
  while (started) {
    while(!water_pouring){
      Serial.println("Pouring Creamer");
      creamer.write(50);
      delay(200);
      creamer.write(0);
      delay(1000);
      Serial.println("spin to sugar");
      for (bottom_pos = 0; bottom_pos <= 90; bottom_pos ++) {
        bottom_spin.write(bottom_pos);
        Serial.println("move!");
        delay(50);
      }
      delay(1000);
      Serial.println("Pour Sugar");
      sugar.write(30);
      delay(300);
      sugar.write(0);
      delay(1000);
      Serial.println("Spin to coffee");
      for (bottom_pos = 90; bottom_pos <= 180; bottom_pos ++) {
        bottom_spin.write(bottom_pos);
        Serial.println("move!");
        delay(50);
      }
      water_pouring = true;
    }
    delay(1000);
    while (water_pouring){
      // boil water
      thermistor_read = analogRead(A0);
      Serial.println(thermistor_read);
      digitalWrite(relay_pin, HIGH);
      if (thermistor_read > 80){
        continue;
      } else{
        digitalWrite(relay_pin, LOW);
        water_pouring = false;
      }        
    }

    // pour water
    digitalWrite(solenoid_pin, HIGH);
    Serial.println("Solenoid High");
    delay(20000);
    digitalWrite(solenoid_pin, LOW);
    started = false;
  }
}
