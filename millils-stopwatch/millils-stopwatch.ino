void setup() {
  // Give some time to open serial monitor after programming
  delay(2500);
  Serial.begin(9600);
 
  // Store the current time (start the clock)
  unsigned long millisNoFlushStart = millis();
  // Transmit some psuedo-random text
  Serial.println(F("How long will it take to transmit the following:"));
  Serial.println(F("abcdefghijklmnopqrstuvwxyz"));
  Serial.println(F("done"));
  // Store the current time (stop the clock)
  unsigned long millisNoFlushStop = millis();
 
  // Wait until TX buffer is empty and print a seperator
  Serial.flush();
  Serial.println(F("---"));
  Serial.flush();
 
   // Store the current time (start the clock)
  unsigned long millisWithFlushStart = millis();
  // Transmit the same psuedo-random text as before
  Serial.println(F("How long will it take to transmit the following:"));
  Serial.println(F("abcdefghijklmnopqrstuvwxyz"));
  Serial.println(F("done"));
  // This time, let TX buffer flush before "stopping" the clock
  Serial.flush();
  // Store the current time (stop the clock)
  unsigned long millisWithFlushStop = millis();
 
  Serial.println();  Serial.println();  Serial.println();
 
  // Print Results for the non-flush calls
  Serial.print(F("Without flush, Serial.println()s return control in: "));
  Serial.print( millisNoFlushStop - millisNoFlushStart);
  Serial.println(F(" milliseconds."));
 
  Serial.println();
 
  // Print results for flushed calls
  Serial.print(F("WITH flush, Serial.println()s return control in: "));
  Serial.print( millisWithFlushStop - millisWithFlushStart);
  Serial.println(F(" milliseconds."));
 
  // Stop the code.
  while(1);
 
}
 
// This will never get executed.
void loop() {
}

// millis() Stopwatch
// Use millis() to time how long chunks of code take to execute
// More Info: https://baldengineer.com/arduino-timing-code-with-millis-as-a-stopwatch.html
// Created by James Lewis (@baldengineer)