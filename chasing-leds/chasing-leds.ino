// Simple macros to remember which direction to shift LEDs
#define UP true
#define DOWN false
 
// Will be used to track how long since last event "fired"
unsigned long previousMillis = 0;
 
// Delay to determine when we see the next LED
unsigned long interval = 250;
 
// Array with Arduino pins containing LEDs in sequence
byte LEDpins[] = {2,3,4,5,6,7};
 
// Variable to track which LED to turn on, start at 000001
int LEDstate = 0x01;
 
// State variable to know which direction to shift
boolean direction = UP;
 
void setup() {
  // Optional: Push Button to turn on all LEDs (to test)
  pinMode(12, INPUT_PULLUP);
 
  // Set Pins with LEDs to OUTPUT
  for (int x=0; x < 6; x++)
    pinMode(LEDpins[x], OUTPUT);
}
 
void loop() {
  // Set the pins of each LED during each iteration
  // You'll only see something change when "LEDpins" gets updated
  for (int x=0; x < 6; x++)
    digitalWrite(LEDpins[x], bitRead(LEDstate,x));
 
  // Test Funciton to turn on all LEDs with pushbutton
  if (digitalRead(12) == LOW)
    turnOnAll();
 
  // Get current time and determine how long since last check
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval) {
    // We've waited "interval" amount of time, so let's do some stuff!
 
    // "Reset" our clock
    previousMillis = currentMillis;
 
    if (direction == UP) {
      // Use "<<" to "bit-shift" everything to the left once
      LEDstate = LEDstate << 1;
      // 0x20 is the "last" LED, another shift makes the value 0x40
      if (LEDstate == 0x40) {
        // turn on the one before "0x20" and reverse direction
        LEDstate = 0x10;
        direction = DOWN;
      }
    }
    else {
      // use ">>" to "bit-shift" all bits in LEDstate once to the right
      LEDstate = LEDstate >> 1;
      // This means we ran out of bits!
      if (LEDstate == 0x00) {
        // set one ahead so no extra delay
        LEDstate = 0x02;
        direction = UP;
      }
    }
  }
}
 
void turnOnAll() {
  // Simple code to turn on all LEDs, this "blocks"
  // so when code returns, the same LED in LEDstate will be "saved"
  while (digitalRead(12)==LOW) {
    for (int x=0; x< 6; x++)
      digitalWrite(LEDpins[x], HIGH);
  }
}

// Chasing LED Pattern
// Create a similar larson scanner, that can run along side other code
// More Info: https://baldengineer.com/arduino-chasing-leds-with-millis.html
// Created by James Lewis (@baldengineer)
