#include "arduinos.h"

const char ENVELOPE_START[]    PROGMEM = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body>";
const char ENVELOPE_END[]      PROGMEM = "</s:Body></s:Envelope>";

EthernetClient client;

/*
 * Main method for assembling the POST message to the Sonos
 */
void sonos(const char *pTag, const char *pCmd, const char *pStart, const char *pEnd1, const char *pEnd2, const char *pStationName, const char *pEnd3, const char *pEnd4)
{
    boolean connectionStatus = client.connect(sonosip_living_room, 1400);

    if (!connectionStatus) {
        ledFailure();
#ifdef DEBUG
        Serial.println(F("connection failed1"));
#endif
        return;
    }

    if (client.connected()) {
        ledCommunicating();
        readResponse = true;

#ifdef DEBUG
        Serial.println(F("connected2"));
#endif
 
        int packetLength = strlen_P(ENVELOPE_START) + strlen_P(pCmd) + strlen_P(ENVELOPE_END);
        if (pStart != NULL) {
            packetLength += strlen_P(pStart);
        }
        if (pEnd1 != NULL) {
            packetLength += strlen_P(pEnd1);
        }
        if (pEnd2 != NULL) {
            packetLength += strlen_P(pEnd2);
        }
        if (pStationName != NULL) {
            packetLength += strlen_P(pStationName);
        }
        if (pEnd3 != NULL) {
            packetLength += strlen_P(pEnd3);
        }
        if (pEnd4 != NULL) {
            packetLength += strlen_P(pEnd4);
        }
        sendHeader(packetLength, pTag, "AVTransport", sonosip_living_room);
        
        bufferBigFill(ENVELOPE_START);    out(bufferBig);
        if (pStart != NULL) {
            bufferBigFill(pStart);        out(bufferBig);
        }
        bufferBigFill(pCmd);              out(bufferBig);
        if (pEnd1 != NULL) {
            bufferBigFill(pEnd1);         out(bufferBig);
        }
        if (pEnd2 != NULL) {
            bufferBigFill(pEnd2);         out(bufferBig);
        }
        if (pStationName != NULL) {
            bufferBigFill(pStationName);  out(bufferBig);
        }
        if (pEnd3 != NULL) {
            bufferBigFill(pEnd3);         out(bufferBig);
        }
        if (pEnd4 != NULL) {
            bufferBigFill(pEnd4);         out(bufferBig);
        }
        bufferBigFill(ENVELOPE_END);      out(bufferBig);
    
        readHttpResponse();
        client.stop();
    
    } else {
        ledFailure();
#ifdef DEBUG
        Serial.println(F("connection failed2"));
#endif
    }
}

/*
 * Wrapper for client.println
 */
void outln(const char *s)
{
    client.println(s);
#ifdef DEBUG
    Serial.println(s);
#endif
}

/*
 * Wrapper for client.print
 */
void out(const char *s)
{
    client.print(s);
#ifdef DEBUG
    Serial.print(s);
#endif
}

