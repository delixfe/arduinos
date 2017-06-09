#include "arduinos.h"
//#include <Key.h>
#include <Keypad.h>


//TODO: we do not have a 4x4 keyboard...
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
byte rowPins[ROWS] = {D2, D3, D4, D5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D6, D7, D8}; //connect to the column pinouts of the keypad

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/*
 * Configure ports used for the keyboard matrix
 */
void setupKeyboard() {
  
}

/*
 * Main keyboard scan which is performed on every loop
 */
char loopKeyboard() {
    char key = keypad.getKey();

#ifdef DEBUG
    if(key) {
      Serial.print(F("Key pressed:"));
      Serial.print(key);
    }
#endif
    
    return key;
}








