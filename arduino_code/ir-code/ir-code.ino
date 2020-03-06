#include <IRremote.h> // lib import 

int RECV_PIN = 11; // input from ir sensor
int led1 = 10; // control for mosfet
int power = 100; // power level for mosfet
int change = 50; // step for intensity
boolean on = false; // if the light is on or off 

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
  if (irrecv.decode(&results)) {    // execute if new input is received 
    Serial.println(results.value);  // printing for debugging
    switch(results.value ) {        // enter switch statement with the value of the ir sensor 
      case 0xFFA25D:                // when the on button is pressed
        if (on) {                   // if the led strip is already on turn it off
          Serial.println("Power Off"); // debugging
          analogWrite(led1, 0);     // turn off
          power = 100;              // reset power
        } else {  
          Serial.println("Power on"); // debugging
          analogWrite(led1, power);   // turn on 
        }
        on = !on;                     // set to opposite flag
      break;
      case 0xFF906F:                // when up is pressed
        Serial.println("up");
        if (on) {
          if (power <= 200) {       // if the power is not maxed
            power = power + change; // increment power counter
            analogWrite(led1, power); // increase voltage to mosfet 
          }
        } 
      break;
      case 0xFFE01F:                // when down is pressed
        Serial.println("down");     // debugging
        if (on) {                   
          if (power >= change) {    // if power is not too low
            power = power - change; // lower power level
            analogWrite(led1, power); // change mosfet power
          }
        } 
      break;
    }
    Serial.println(power);                // debugging 
    Serial.println("Delay not working");  // debugging 
    irrecv.resume(); // Receive the next value
  }
}
