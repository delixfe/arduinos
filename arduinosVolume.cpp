#include "arduinos.h"

const char SONOS_TAG_VOLUME[]  PROGMEM = "RenderingControl:1#SetVolume";
const char VOL_START[]         PROGMEM = "<u:SetVolume xmlns:u=\"urn:schemas-upnp-org:service:RenderingControl:1\"><InstanceID>0</InstanceID><Channel>Master</Channel><DesiredVolume>";
const char VOL_END[]           PROGMEM = "</DesiredVolume></u:SetVolume>";

char const volume_max=12;
char const volume_min=0;
char volume=4; // Start index
#define DECIMAL 10

/*
 * Increase the volume
 */
void sonosVolPlus(){
    if (volume < volume_max) {
        volume++;
    }
    sonosVolume(sonosip_living_room);
    sonosVolume(sonosip_kitchen);
}
 
/*
 * Decrease the volume
 */
void sonosVolMinus(){
    if (volume > volume_min) {
        volume--;
    }
    sonosVolume(sonosip_living_room);
    sonosVolume(sonosip_kitchen);
}

/*
 * Map the volume to a value used by Sonos. Wrap up a 'volume' package and send it to 
 * all devices
 */
void sonosVolume(byte *pSonos)
{
    char volStr[4];

    char volArray[]={1, 3, 5, 8, 13, 21, 30, 40, 50, 60, 70, 80, 90};
    itoa(volArray[volume], volStr, DECIMAL);
  
    boolean connectionStatus = client.connect(pSonos, 1400);
  
    if (!connectionStatus) {
        ledFailure();
#ifdef DEBUG
        Serial.println(F("connection failed3"));
#endif
        return;
    }
  
    if (client.connected()) {
        ledCommunicating();
        readResponse = true;
        
#ifdef DEBUG
        Serial.println(F("connected2"));
#endif
     
        int packetLength = strlen_P(ENVELOPE_START) + strlen_P(VOL_START) + strlen(volStr) + strlen_P(VOL_END) + strlen_P(ENVELOPE_END);
        sendHeader(packetLength, SONOS_TAG_VOLUME, "RenderingControl", pSonos);
        
        bufferBigFill(ENVELOPE_START); out(bufferBig);
        bufferBigFill(VOL_START);      out(bufferBig);
        strcpy(bufferBig,volStr);      out(bufferBig);
        bufferBigFill(VOL_END);        out(bufferBig);
        bufferBigFill(ENVELOPE_END);   out(bufferBig);
    
        readHttpResponse();
        client.stop();
  
    } else {
        ledFailure();
#ifdef DEBUG
        Serial.println(F("connection failed4"));
#endif
    }
}

