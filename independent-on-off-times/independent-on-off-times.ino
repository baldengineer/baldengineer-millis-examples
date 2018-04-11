// On and Off Times (as int, max=32secs)
const unsigned int onTime = 1000;
const unsigned int offTime = 500;
 
// Tracks the last time event fired
unsigned long previousMillis=0;
 
// Interval is how long we wait
int interval = onTime;
 
// Used to track if LED should be on or off
boolean LED13state = true;
 
// Usual Setup Stuff
void setup() {
  pinMode(13, OUTPUT);
}
 
void loop() {
  // Set Pin 13 to state of LED13state each timethrough loop()
  // If LED13State hasn't changed, neither will the pin
  digitalWrite(13, LED13state);
 
  // Grab snapshot of current time, this keeps all timing
  // consistent, regardless of how much code is inside the next if-statement
  unsigned long currentMillis = millis();
 
  // Compare to previous capture to see if enough time has passed
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {

    // Change wait interval, based on current LED state
    if (LED13state) {
      // LED is currently on, set time to stay off
      interval = offTime;
    } else {
      // LED is currently off, set time to stay on
      interval = onTime;
    }
    // Toggle the LED's state, Fancy, eh!?
    LED13state = !(LED13state);
 
    // Save the current time to compare "later"
    previousMillis = currentMillis;
  }
  
}

// Independent On-Off Times
// Blink an LED (or control a reply) with different "on" and "off" times
// More Info: https://baldengineer.com/millis-ind-on-off-times.html
// Created by James Lewis (@baldengineer)