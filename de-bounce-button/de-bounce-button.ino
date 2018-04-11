// Buttons with Pull-Ups are "backwards"
// Some DEFINEs to make reading code easier
#define PUSHED false
#define NOT_PUSHED true
#define WATCH_BUTTON true
#define IGNORE_BUTTON false
 
// Time to wait for bounce, in MICROsconds
const int buttonWaitInterval = 6000;
// Pins for LED and Button
const int LEDpin = 13;
const int BUTTONpin = 2;
 
// Used to track how long between "bounces"
unsigned long previousMicros = 0;
 
// Used to track state of button (high or low)
boolean previousButtonState = NOT_PUSHED;
 
// Variable reporting de-bounced state.
boolean debouncedButtonState = NOT_PUSHED;
 
// Tracks if we are waiting for a "bounce" event
boolean bounceState = false;
 
// Nothing surprising here
void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(BUTTONpin, INPUT_PULLUP);
}
 
void loop() {
  // This needs to be called periodically to
  // update the timers and button status
  updateButton();
  // This replaces: digitalRead(BUTTONpin);
  digitalWrite(LEDpin, debouncedButtonState);
}
 
// All of the magic happens here
void updateButton() {
  // We are waiting for any activity on the button
  if (bounceState == WATCH_BUTTON) {
    // Get and store current button state
    boolean currentButtonState = digitalRead(BUTTONpin);
    // Check to see if a transition has occured (and only one)
    if (previousButtonState != currentButtonState) {
      // A transition was detected, ignore the others for a while
      bounceState = IGNORE_BUTTON;
      // Store current time (start the clock)
      previousMicros = micros();
    }
    // Keep storing existing button state, if we're watching
    previousButtonState = currentButtonState;
  }
  // We are waiting for the buttonWaitInterval to elapse
  if (bounceState == IGNORE_BUTTON) {
    // Compare current value of micros to previously stored, enough time yet?
    unsigned long currentMicros = micros();
    if ((currentMicros - previousMicros) >= buttonWaitInterval) {
      // Store the state of the button/pin to debouncedButtonState, which "reports"
      // the correct value. This allows for the code to handle active high or low inputs
      debouncedButtonState = digitalRead(BUTTONpin);
      // Go back to watching the button again.
      bounceState = WATCH_BUTTON;
    }
  }
}

// Debounce A Button
// Use either millis() or micros() to debounce a button
// More Info: https://baldengineer.com/arduino-de-bounce-a-button-with-micros.html
// Created by James Lewis (@baldengineer)