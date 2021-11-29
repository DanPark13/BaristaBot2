#include <Stepper.h>
#include <Servo.h>
#define STEPS_PER_REV 513

// Defining pins 9-12 for stepper control
Stepper motor(STEPS_PER_REV, 9, 10, 11, 12);
Servo creamer;
Servo sugar;
Servo bean;

int solenoid_state = 1;   // on/of logic for the NMOS circuit for solenoid valve
int motor_state = 2;      // on/off logic for the NMOS circuit for bean grinding motor
int coil_state = 3;       // on/off logic for the NMOS circuit for heating coil
int stir_height = 5;      // Pin for stir servo responsible for lowering stirrer into the cup
int stir_rot = 6;         // Pin for the stir servo responsible for stirring the cup
int bean_pin = 7;         // Pins for the three servos
int sugar_pin = 8;
int creamer_pin = 9;

// stepper variables
int creamer_pos = 0;      // pins initializing positions of the servos
int sugar_pos = 0; 
int bean_pos = 0;
bool backwards = false;   // check whether to reverse direction of servo (might become obsolete?)

// Thermistor read variables
int thermistor_read = A0; // Pin to read the state of the thermistor
int v_out;


// Interface read variables
int interface_start = A1;
int interface_creamer = A2;
int interface_sugar = A3;

// declaring booleans based on interface readings
bool started;
bool dispense_creamer;
bool dispense_sugar;

// states of coffee making
bool water_heating = true;
bool coffee_brewing = false;

void setup() {
  // pinmodes :/
  pinMode(solenoid_state, OUTPUT);
  pinMode(motor_state, OUTPUT);
  pinMode(coil_state, OUTPUT);
  Serial.begin(9600);
  // Initialize servos and set position to neutral
  creamer.attach(creamer_pin);
  sugar.attach(sugar_pin);
  bean.attach(bean_pin);
  creamer.write(creamer_pos);
  sugar.write(sugar_pos);
  bean.write(bean_pos);
  delay(2000);
  // run function for stepper alignment
}

void loop() {
  // Begin water heating stage
  while (water_heating) {
    // heating coil activation/deactivation feedback
    thermistor_read = analogRead(A0);
    digitalWrite(coil_state, HIGH);
    if (thermistor_read > 80){
      continue;
    } else{
      digitalWrite(coil_state, LOW);
      water_heating = false;
      coffee_brewing = true;
    }
  }

  while (coffee_brewing) {
    // stage 1 of brewing
    for (int i = 0; i < 3; i ++){
      digitalWrite(solenoid_state, HIGH);
      delay(5000);
      digitalWrite(solenoid_state, LOW);
      delay(20000); // determine this and the above delay by testing how long it takes to fill the filter/how long it takes for water to drip drop
    }
    coffee_brewing = false;
  }
  
  dispense_creamer = analogRead(A2) > 0;
  while(dispense_creamer){ // check this whole thing because dispensing might be different
    motor.step(STEPS_PER_REV);
    delay(1000);// Step clockwise one whole revolution
    int cream_mult = 1;
    if (backwards_c1){
      container1_pos -= 60;
    } else{
      container1_pos += 60;
    }
    if (container1_pos >= 180){
      backwards = true;
      container1_pos = 180;
    }
    if (container1_pos <= 0) {
      backwards = false;
      container1_pos = 0;
    }
    dispense_creamer = false;
  }

  dispense_sugar = analogRead(A3) > 0;
  while(dispense_sugar){
    // same as above
    motor.step(STEPS_PER_REV);
    delay(1000);// Step clockwise one whole revolution
  }

  // routine to recenter (use stepper calibration function)
}
