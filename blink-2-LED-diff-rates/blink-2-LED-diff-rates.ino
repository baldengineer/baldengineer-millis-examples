// each "event" (LED) gets their own tracking variable
unsigned long previousMillisLED12 = 0;
unsigned long previousMillisLED13 = 0;
 
// different intervals for each LED
int intervalLED12 = 500;
int intervalLED13 = 1000;
 
// each LED gets a state varaible
boolean LED13state = false;     // the LED will turn ON in the first iteration of loop()
boolean LED12state = false;     // need to seed the light to be OFF
 
void setup() {
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
}

void loop() {
   // get current time stamp
   // only need one for both if-statements
   unsigned long currentMillis = millis();
 
   // time to toggle LED on Pin 12?
   if ((currentMillis - previousMillisLED12) >= intervalLED12) {
      LED12state = !LED12state;
      digitalWrite(12, LED12state);

      // save current time to pin 12's previousMillis
      previousMillisLED12 = currentMillis;
   }
 
// time to toggle LED on Pin 13?
  if ((currentMillis - previousMillisLED13) >= intervalLED13) {
      LED13state = !LED13state;
      digitalWrite(13, LED13state);
      
      // save current time to pin 12's previousMillis
      previousMillisLED13 = currentMillis;
  }
}

// millis() blink 2 LEDs
// Extends Blink Without Delay to include 2 LEDs
// More Info: https://baldengineer.com/millis-tutorial.html
// Created by James Lewis (@baldengineer)