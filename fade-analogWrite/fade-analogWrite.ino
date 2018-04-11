const byte pwmLED = 5;
 
 
// define directions for LED fade
#define UP 0
#define DOWN 1
 
// constants for min and max PWM
const int minPWM = 0;
const int maxPWM = 255;
 
// State Variable for Fade Direction
byte fadeDirection = UP;
 
// Global Fade Value
// but be bigger than byte and signed, for rollover
int fadeValue = 0;
 
// How smooth to fade?
byte fadeIncrement = 5;
 
// millis() timing Variable, just for fading
unsigned long previousFadeMillis;
 
// How fast to increment?
int fadeInterval = 50;
 
void setup() {
  // put pwmLED into known state (off)
  analogWrite(pwmLED, fadeValue); 
}
 
void doTheFade(unsigned long thisMillis) {
  // is it time to update yet?
  // if not, nothing happens
  if (thisMillis - previousFadeMillis >= fadeInterval) {
    // yup, it's time!
    if (fadeDirection == UP) {
      fadeValue = fadeValue + fadeIncrement;  
      if (fadeValue >= maxPWM) {
        // At max, limit and change direction
        fadeValue = maxPWM;
        fadeDirection = DOWN;
      }
    } else {
      //if we aren't going up, we're going down
      fadeValue = fadeValue - fadeIncrement;
      if (fadeValue <= minPWM) {
        // At min, limit and change direction
        fadeValue = minPWM;
        fadeDirection = UP;
      }
    }
    // Only need to update when it changes
    analogWrite(pwmLED, fadeValue);  
 
    // reset millis for the next iteration (fade timer only)
    previousFadeMillis = thisMillis;
  }
}
 
void loop() {
  // get the current time, for this time around loop
  // all millis() timer checks will use this time stamp
  unsigned long currentMillis = millis();
    
  doTheFade(currentMillis);
 
}

// Non-blocking analogWrite() Fading
// Keep a smooth fade happening without blocking with delay()
// More Info: https://baldengineer.com/fading-led-analogwrite-millis-example.html
// Created by James Lewis (@baldengineer)