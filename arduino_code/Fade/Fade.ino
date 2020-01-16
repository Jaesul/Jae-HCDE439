/*
  Blink

  Blinks led sequentially faster and faster and switches direction at fastest 
  and slowest

*/

int BUTTON = 2; // Assigning button to pin 2                     
int LED1= 11;   // Assigning button to pin 2
int LED2= 10;   // Assigning button to pin 2
int LED3= 9;    // Assigning button to pin 2
int LED4= 6;    // Assigning button to pin 2         
int BUTTONSTATE = 0; 
double DELAY = 20;
boolean LEDON = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  BUTTONSTATE = digitalRead(BUTTON);
  if(BUTTONSTATE == HIGH) {
    if(!LEDON) {
      blinkAllForward();
      blinkAllForward();
      for(int i=0; i <= 255; i += 2.5) {
        analogWrite(LED1, i);
        analogWrite(LED2, i);
        analogWrite(LED3, i);
        analogWrite(LED4, i);
        delay(DELAY);
        LEDON = true;
      } 
      blinkAll();
      blinkAll();     
    } else {
      for(int i=255; i >= 0; i -= 15) {

        analogWrite(LED4, i);
        delay(DELAY);
      }
      for(int i=255; i >= 0; i -= 15) {
        analogWrite(LED3, i);
        delay(DELAY);
      }
      for(int i=255; i >= 0; i -= 15) {
        analogWrite(LED2, i);
        delay(DELAY);
      }
      for(int i=255; i >= 0; i -= 15) {
        analogWrite(LED1, i);
        delay(DELAY);
      }
      LEDON = false;
    }
  }
}

void blinkAll() {
      digitalWrite(LED4, LOW);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      delay(50);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);     
      digitalWrite(LED3, HIGH);  
      digitalWrite(LED4, HIGH);
      delay(50);
}

void blinkAllForward() {
      digitalWrite(LED1, HIGH);
      delay(60);
      digitalWrite(LED1, LOW);
      delay(60);
      digitalWrite(LED2, HIGH);
      delay(60);
      digitalWrite(LED2, LOW);
      delay(60);
      digitalWrite(LED3, HIGH);
      delay(60);
      digitalWrite(LED3, LOW);
      delay(60);
      digitalWrite(LED4, HIGH);
      delay(60);
      digitalWrite(LED4, LOW);
      delay(60);
}
