void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char val = Serial.read();

    if(val == 'r'){
      Serial.println("Button 1 Pressed");
    }
    if(val == 'b'){
      Serial.println("Button 2 Pressed");
    }
    if(val == 'y'){
      Serial.println("Button 3 Pressed");
    }
  }
}
