//========================= Configuration start =============================
#define notDEBUG // Set this to DEBUG if you want support for serial interface

//Use this if it is NANO+SHIELD
#include <UIPEthernet.h>
#define UIPE

//Use this for UNO+SHIELD
//#include <SPI.h>
//#include <Ethernet.h>

#define CLIENT_MAC           {0xBE, 0xEF, 0xEE, 0x00, 0x20, 0x09}
#define CLIENT_IP            { 192, 168, 1, 83 } 
#define SONOS_IP_LIVING_ROOM { 192, 168, 1, 82 }
#define SONOS_IP_KITCHEN     { 192, 168, 1, 80 }

//========================= Configuration end =============================

#if defined ( ESP8266 )
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif

#include <Arduino.h>

// arduinos.ino
extern boolean readResponse;
extern byte sonosip_living_room[];
extern byte sonosip_kitchen[];

// arduinosBuffer.cpp
#define SIZE_SMALL 40
#define SIZE_BIG 330
extern char bufferSmall[];
extern char bufferBig[]; 
extern char *bufferSmallFill(const char *pProgmem);
extern char *bufferBigFill(const char *pProgmem);

// arduinosKeyboard.cpp
extern void setupKeyboard(void);
extern char loopKeyboard(void);

// arduinosLed.cpp
extern void ledStopTimer(void);
extern void ledCommunicating(void);
extern void ledSuccess(void);
extern void ledFailure(void);
extern void ledCheckTimeout(void);
extern void ledInit(void);

// arduinosRadio.cpp
extern void sonosRadioStation(const char *pProgmem, const char *pProgmemStationName);

// arduinosVolume.cpp
extern const char ENVELOPE_START[];
extern const char ENVELOPE_END[];
extern void sonosVolPlus();
extern void sonosVolMinus();
extern void sonosVolume(byte *pSonos);

// arduinosPlayPause.cpp
extern void sonosPause(); 
extern void sonosPlay();

// arduinosHttpPost.cpp
extern EthernetClient client;
extern void outln(const char *s);
extern void out(const char *s);
extern void sonos(const char *pTag, const char *pCmd, const char *pStart, const char *pEnd1, const char *pEnd2, const char *pStationName, const char *pEnd3, const char *pEnd4);

// arduinosHttpResponse.cpp
extern void readHttpResponse(void);

// arduinosHttpHeader.cpp
extern void sendHeader(int packetLength, const char *pTag, char *pTag2, byte *pSonos);

 


