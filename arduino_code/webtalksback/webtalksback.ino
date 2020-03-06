
// Arduino pin numbers
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
const int ledPins[5] = {11,10,9,6,5}; // LED pins
int LEDSTATE = 2; // LED lights on 
int LEDBRIGHTNESS = 25; // LED brightness

void setup() {
  for (int i = 0; i < 5; i++) { // Setup outputs
      pinMode(ledPins[i], OUTPUT);
  }

  // Printing current status
  Serial.begin(9600);
  Serial.print('[');
  Serial.print(LEDSTATE);
  Serial.print(',');
  Serial.print(LEDBRIGHTNESS / 25);
  Serial.print("]");
  Serial.print("\r\n");
}

// Updating the brightness 
void updateBrightness() {
  for (int i = 0; i < LEDSTATE; i++) {
    analogWrite(ledPins[i], LEDBRIGHTNESS);
  }
}

// updating the led state 
void updateLedState() {
  for (int i = 0; i < LEDSTATE; i++) {
    analogWrite(ledPins[i], LEDBRIGHTNESS);
  }
  for(int i = LEDSTATE; i < 5; i++) {
    analogWrite(ledPins[i], 0);
  }
}

void loop() {

  int turnOff = Serial.read(); // reading in input from websocket
  if (turnOff == 1) { // if response is 1 turn off led's
    LEDBRIGHTNESS = 0;
  }
  int y = analogRead(Y_pin);  // read in joystick y value
  int x = analogRead(X_pin);  // read in joystick X value
  int pastState[2] = {LEDSTATE, LEDBRIGHTNESS}; // Record past state 
  switch (y) { // if joystick was flicked up then make brighter flick down vise versa
    case 0 :
      if (LEDBRIGHTNESS > 0) {
        LEDBRIGHTNESS = LEDBRIGHTNESS - 25;     
      } 
      break;
    case 1023:
      if (LEDBRIGHTNESS < 250) {
        LEDBRIGHTNESS = LEDBRIGHTNESS + 25; 
      }
      break; 
  }

  switch (x) { // if joystick was flicked right then make more leds on flick left vise versa
    case 0:
      if (LEDSTATE > 0) {
        LEDSTATE = LEDSTATE - 1;
      } 
      break;
    case 1023:
      if (LEDSTATE < 5) {
        LEDSTATE = LEDSTATE + 1;
      } 
      break;
  }

  // update led states
  updateLedState(); 
  updateBrightness(); 

  // Send to websocket the state of the system
  if (LEDSTATE != pastState[0] || LEDBRIGHTNESS != pastState[1]) {
    Serial.print('[');
    Serial.print(LEDSTATE);
    Serial.print(',');
    Serial.print(LEDBRIGHTNESS / 25);
    Serial.print("]");
    Serial.print("\r\n");
  }

  delay(150);
}
