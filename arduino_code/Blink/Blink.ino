/*
  Blink

  Blinks led sequentially faster and faster and switches direction at fastest 
  and slowest

*/

int LED1 = 13;            // Assigning variable to LED
int LED2 = 12;            // Assigning variable to LED
int LED3 = 11;            // Assigning variable to LED
boolean restart = false;  // Creating a restart flag

double time = 800;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);   // Sets pin on LED 1 to on
  delay(time);                // Waits a set period of time         
  digitalWrite(LED1, LOW);    // Sets pin on LED 1 to off 
  delay(time);                // Waits a set period of time
  digitalWrite(LED2, HIGH);   // Sets pin on LED 1 to on 
  delay(time);                // Waits a set period of time         
  digitalWrite(LED2, LOW);    // Sets pin on LED 1 to off 
  delay(time);                // Waits a set period of time
  digitalWrite(LED3, HIGH);   // Sets pin on LED 1 to on
  delay(time);                // Waits a set period of time          
  digitalWrite(LED3, LOW);    // Sets pin on LED 1 to off
  delay(time);                // Waits a set period of time
  if(time > 30 && !restart) { // Goes into block with correct delay time and restart is not true
    time = time/2;            // Delay time is halved
  }
  else {
    if(time >= 800) {         // Goes into block if time is greater than 800
      restart = false;        // Makes the restart not happen
      LED1 = 13;              // Reassigns the first led
      LED3 = 11;              // Reassigns the last led
    } else if(time < 800 && restart) {  // Goes into block if time is less than 800 and is reset
      time = time * 2;        // Time delay starts to double 
    } else {
      restart = true;         // Makes the restart happen
      LED1 = 11;              // Assigns LED1 to last LED
      LED3 = 13;              // Assigns LED3 to first LED
    }
  }
}
