#include "arduinos.h"

const byte OFF   = 0;
const byte GREEN = 1;
const byte RED   = 2;

const long GREEN_ON_TIME = 1000;
const long RED_ON_TIME   = 3000;

static long switchOffTime = 0;

/*
 * Set a time stamp for switching of the LEDs
 */
void ledStartTimer(int duration) {
  switchOffTime = millis() + duration;  
}

/*
 * Reset the LED "timer"
 */
void ledStopTimer() {
  switchOffTime = millis();  
}

/*
 * Initialize the LED pins
 */
void ledInit(void) {
  pinMode(6, OUTPUT); 
  digitalWrite(6, LOW);  // Green

  pinMode(7, OUTPUT); 
  digitalWrite(7, LOW);  // Red
}

/*
 * LED "state machine"
 */
void led(byte colour) {
  switch (colour) {
    case RED:
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      //Serial.println("R");
      ledStartTimer(RED_ON_TIME);
      break;
    case GREEN:
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      //Serial.println("G");
      ledStartTimer(GREEN_ON_TIME);
      break;
    case OFF:
    default:
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      //Serial.println("X");
      ledStopTimer();
      break;
  }
}

/*
 * Periodically check if LED should be switched off
 */
void ledCheckTimeout(void) {
  if (millis() > switchOffTime) {
    led(OFF);
  }
}

/*
 * Switch on the "communication ongoing" LED
 */
void ledCommunicating() {
  led(GREEN);
}

/*
 * Switch on the "successful outcome" LED
 */
void ledSuccess() {
  led(GREEN);
}

/*
 * Switch on the "error detected" LED
 */
void ledFailure(void) {
  led(RED);
}

