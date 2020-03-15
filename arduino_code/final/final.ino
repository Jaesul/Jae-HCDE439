#include <IRremote.h> // lib import 

int RECV_PIN = 11; // input from ir sensor
int led1 = 10; // control for mosfet
int power = 100; // power level for mosfet
int change = 50; // step for intensity
boolean on = true; // if the light is on or off 

#define code1 "FFA25D" // power
#define code2 "FF906F" // up
#define code3 "FFE01F" // down 

IRrecv irrecv(RECV_PIN); // recieve sig from ir sensor 

decode_results results; // results from the sensor 

void setup()
{
  Serial.begin(9600); // you can ommit this line
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT); // set the mosfet pin to output 
}

void loop() {
  irBegin();
  recieveWeb();
  sendStatus();
  delay(20);
}

void recieveWeb() {
  int data = Serial.read();
  if (data == 0) {
    turnOff();
  } else if (data == 1) {
    turnOn();
  } else if (data > 0 && data < 255) {
    power = data;
    analogWrite(led1, power);
  }
}

void irBegin() {
    if (irrecv.decode(&results)) {    // execute if new input is received 
    switch(results.value ) {        // enter switch statement with the value of the ir sensor 
      case 0xFFA25D:                // when the on button is pressed
        togglePower(); 
      break;
      case 0xFF906F:                // when up is pressed
        if (on) {
          if (power <= 200) {       // if the power is not maxed
            power = power + change; // increment power counter
            analogWrite(led1, power); // increase voltage to mosfet 
          }
        } 
      break;
      case 0xFFE01F:                // when down is pressed
        if (on) {                   
          if (power >= change) {    // if power is not too low
            power = power - change; // lower power level
            analogWrite(led1, power); // change mosfet power
          }
        } 
      break;
    }
    irrecv.resume(); // Receive the next value
  }
}

void turnOn() {
  analogWrite(led1, power);     // turn off
  on = true; 
}

void turnOff() {
  analogWrite(led1, 0);     // turn off
  power = 100;  
  on = false;
}

void togglePower() {
    if (on) {                   // if the led strip is already on turn it off
      analogWrite(led1, 0);     // turn off
      power = 100;              // reset power
    } else {  
      analogWrite(led1, power);   // turn on 
    }
    on = !on; // set to opposite flag
}

void sendStatus() {
    Serial.print('[');
    Serial.print(power);
    Serial.print(',');
    Serial.print(on);
    Serial.print("]");
    Serial.print("\r\n");
}
