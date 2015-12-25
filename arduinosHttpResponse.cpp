#include "arduinos.h"

static int smallest(int a, int b) {
  if (a < b) return a;
  return b;
}

/*
 * Read the response from Sonos. This is only used as a sanity check of the ethernet connection.
 */
void readHttpResponse(void) {

    if (client.connected()) {
  
        if (readResponse) {
            readResponse = false;
        
#ifdef DEBUG
            Serial.println("");
            Serial.println(F("<client.read start ----------------------------------------------------------------------"));
#endif
  
#ifdef UIPE //-------------- UIPE --------------
            int size = 0;
            for (int attempts=0; attempts<10; attempts++) {
                size = client.available();
                if (size==0) {
                    delay(200);
                } else {
                    break;
                }
            }
  
            for (int stopThis=0; stopThis<20; stopThis++) {
                if (size>0) {
                    int read = client.read((unsigned char *)bufferBig, smallest(size, SIZE_BIG));
#ifdef DEBUG
                    Serial.write(bufferBig, read);  
#endif
                }
                size = client.available();        
            }
#else       //-------------- non-UIPE --------------
            while (client.available()) {
                char c = client.read();
#ifdef DEBUG
                Serial.print(c);
#endif
            } 
#endif      //--------------------------------------
  
#ifdef DEBUG    
            Serial.println("");
            Serial.println(F("----------------------------------------------------------------------- client.read end>"));
#endif
            ledSuccess();
        }
    } else {
#ifdef DEBUG    
        Serial.println(F("connection failed5")); 
#endif
        ledFailure();
    }
}

