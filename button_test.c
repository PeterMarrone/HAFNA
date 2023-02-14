void setup() {
  
  Serial.begin(9600);

  pinMode(54, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  int button = digitalRead(54);

  if(button == LOW) {
    Serial.print("Button Pressed\n");
  }

}