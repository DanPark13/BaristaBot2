#include <math.h>

int ledpin = 13;
int voltage_read = A0;
double temp;
void setup() {
  Serial.begin(9600);
  
}

void loop() {
   temp = convert_voltage(analogRead(A0));
   Serial.println((temp/1023.0)*5.0);
   if(temp < 100){
      digitalWrite(ledpin, HIGH);
   } else{
      digitalWrite(ledpin, LOW);
   }
}

double convert_voltage(int analog_read){
  double v_out = map(analog_read, 0, 1023, 0, 5);
  //Serial.println(v_out);
  double r_thermistor = v_out/((5-v_out)/10000);
  //Serial.println(r_thermistor);
  return 525672/(1764+149*log(r_thermistor/1000));
}
