#include "arduinos.h"

const byte PIN_GREEN = D11;
const byte PIN_RED = D12;

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
  pinMode(PIN_GREEN, OUTPUT); 
  digitalWrite(PIN_GREEN, LOW);  // Green

  pinMode(PIN_RED, OUTPUT); 
  digitalWrite(PIN_RED, LOW);  // Red
}

/*
 * LED "state machine"
 */
void led(byte colour) {
  switch (colour) {
    case RED:
      digitalWrite(PIN_GREEN, LOW);
      digitalWrite(PIN_RED, HIGH);
      //Serial.println("R");
      ledStartTimer(RED_ON_TIME);
      break;
    case GREEN:
      digitalWrite(PIN_GREEN, HIGH);
      digitalWrite(PIN_RED, LOW);
      //Serial.println("G");
      ledStartTimer(GREEN_ON_TIME);
      break;
    case OFF:
    default:
      digitalWrite(PIN_GREEN, LOW);
      digitalWrite(PIN_RED, LOW);
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

