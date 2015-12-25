#include "arduinos.h"

/*
 * Configure ports used for the keyboard matrix
 */
void setupKeyboard() {
    // Keyboard column
    pinMode(A0, INPUT); digitalWrite(A0, HIGH);
    pinMode(A1, INPUT); digitalWrite(A1, HIGH);
    pinMode(A2, INPUT); digitalWrite(A2, HIGH);
    pinMode(A3, INPUT); digitalWrite(A3, HIGH);
    // Keyboard row
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}

/*
 * When keyboard scan is done, set all rows low
 */
void setAllOutputLow() {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

/*
 * Detect which column that has been asserted
 */
int getColumn() {
    int columns[] = {A0, A1, A2, A3};
    for (int i=0; i<(sizeof(columns)/sizeof(int)); i++) {
        int a = columns[i];
        if (digitalRead(a) == 0) {
            return a;
        }
    }
    return 0;
}  

/*
 * Detect which row that has been asserted
 */
int getRow(int column) {
    int row = 0;
    for (int r=2; r<=5; r++) {
        digitalWrite(r, HIGH); 
        delay(1); 
        int c = digitalRead(column);
        if (c == 1) {
            row = r;
            break;
        }
    }  
    return row;
}

/*
 * Based on row & column, determine which key has been pressed
 */
char getKey(int row, int column) {
    char keyPressed = 0;
    switch (row) {
        case 2:
            switch (column) {
                case A0: keyPressed = 'A'; break;
                case A1: keyPressed = '3'; break;
                case A2: keyPressed = '2'; break;
                case A3: keyPressed = '1'; break;
                default:  break;
            }
            break;
        case 3:
            switch (column) {
                case A0: keyPressed = 'B'; break;
                case A1: keyPressed = '6'; break;
                case A2: keyPressed = '5'; break;
                case A3: keyPressed = '4'; break;
                default: break;
            }
            break;
        case 4:
            switch (column) {
                case A0: keyPressed = 'C'; break;
                case A1: keyPressed = '9'; break;
                case A2: keyPressed = '8'; break;
                case A3: keyPressed = '7'; break;
                default:  break;
            }
            break;
        case 5:
            switch (column) {
                case A0: keyPressed = 'D'; break;
                case A1: keyPressed = '#'; break;
                case A2: keyPressed = '0'; break;
                case A3: keyPressed = '*'; break;
                default:  break;
            }
            break;
        default:
            break;
    }
    return keyPressed;
}

/*
 * Perform a single keyboard scan
 */
char scanKeyboard() {
    setAllOutputLow();
    char k = 0;
    int c = getColumn();
    if (c != 0) {
        int r = getRow(c);
        if (r != 0) {
            k = getKey(r, c);
        }
    }
    return k;
}

/*
 * Debouncing of keys. The same key must be detected twice to be accepted. 
 * 
 * So far there has not been a need for a delay between the two detections, nor for more than 2 detections
 */
char debouncedKey() {
    char key1 = scanKeyboard();
    if (key1 != 0) {
        char key2 = scanKeyboard();
        if (key1 != key2) {
            key1 = 0;
        }
    }
    return key1;
}

/*
 * Main keyboard scan which is performed on every loop
 */
char loopKeyboard() {
    static char kPrev = 0;
    
    char k = debouncedKey();
    if (k != kPrev) {
        // Something changed
        if (k == 0) {
            // Key released
#ifdef DEBUG
            Serial.print(F(" - released:"));
            Serial.println(kPrev);
#endif
            kPrev = k;
        } else {
            // Key held down
            if (kPrev == 0) {
#ifdef DEBUG
                Serial.print(F("Key pressed:"));
                Serial.print(k);
#endif
              kPrev = k;
            } else {
                k = 0; // Ignore the keypress
            }
        }
    } else {
        k = 0; // Ignore the keypress
    }
    return k;
}








