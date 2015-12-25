#include "arduinos.h"

const char SONOS_TAG_PAUSE[]   PROGMEM = "AVTransport:1#Pause";
const char SONOS_TAG_PLAY[]    PROGMEM = "AVTransport:1#Play";

const char SONOS_PAUSE[]       PROGMEM = "<u:Pause xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID></u:Pause>";
const char SONOS_PLAY[]        PROGMEM = "<u:Play xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><Speed>1</Speed></u:Play></s:Body></s:Envelope>";

/*
 * Send 'pause' message to Sonos
 */
void sonosPause() {
    sonos(SONOS_TAG_PAUSE, SONOS_PAUSE, NULL, NULL, NULL, NULL, NULL, NULL);
}

/*
 * Send 'play' message to Sonos
 */
void sonosPlay() {
    sonos(SONOS_TAG_PLAY, SONOS_PLAY, NULL, NULL, NULL, NULL, NULL, NULL);
}

