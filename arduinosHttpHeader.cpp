#include "arduinos.h"

const char LINE2[]             PROGMEM = "Connection: close";
const char LINE3[]             PROGMEM = "ACCEPT-ENCODING: gzip";
const char LINE5[]             PROGMEM = "USER-AGENT: Linux UPnP/1.0 Sonos/29.5-90191 (WDCR:Microsoft Windows NT 6.1.7601 Service Pack 1)";
const char LINE7[]             PROGMEM = "Content-Type: text/xml; charset=\"utf-8\"";

/*
 * Method to send header information before sending information about the desired radio station
 */
void sendHeader(int packetLength, const char *pTag, char *pTag2, byte *pSonos) {
    bufferSmallFill(pTag);
 
    sprintf(bufferBig,"POST /MediaRenderer/%s/Control HTTP/1.1",pTag2);                        outln(bufferBig);
    bufferBigFill(LINE2);                                                                      outln(bufferBig);
    bufferBigFill(LINE3);                                                                      outln(bufferBig);
    sprintf(bufferBig, "Host: %d.%d.%d.%d:1400", pSonos[0], pSonos[1], pSonos[2], pSonos[3]);  outln(bufferBig);
    bufferBigFill(LINE5);                                                                      outln(bufferBig);
    sprintf(bufferBig, "Content-Length: %d", packetLength);                                    outln(bufferBig);
    bufferBigFill(LINE7);                                                                      outln(bufferBig);
    sprintf(bufferBig, "Soapaction: \"urn:schemas-upnp-org:service:%s\"", bufferSmall);        outln(bufferBig);
    outln("");
}

