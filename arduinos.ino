#include "arduinos.h"

/* 
      
    
*/
uint8_t arduino_mac[6]       = CLIENT_MAC;
uint8_t arduino_ip[4]        = CLIENT_IP; 
byte sonosip_living_room[]   = SONOS_IP_LIVING_ROOM; // Type: Connect
byte sonosip_kitchen[]       = SONOS_IP_KITCHEN;     // Type: Play1

 
/* 
 *  Radio stations
 */
const char RADIO_P1[]          PROGMEM = "live-icy.gss.dr.dk/A/A03H.mp3.m3u";            const char RADIO_P1_NAME[]          PROGMEM = "P1";
const char RADIO_P2[]          PROGMEM = "live-icy.gss.dr.dk/A/A04H.mp3.m3u";            const char RADIO_P2_NAME[]          PROGMEM = "P2";
const char RADIO_P3[]          PROGMEM = "live-icy.gss.dr.dk/A/A05H.mp3.m3u";            const char RADIO_P3_NAME[]          PROGMEM = "P3";
const char RADIO_P4[]          PROGMEM = "live-icy.gss.dr.dk/A/A10H.mp3.m3u";            const char RADIO_P4_NAME[]          PROGMEM = "P4";
const char RADIO_P5[]          PROGMEM = "live-icy.gss.dr.dk/A/A25H.mp3.m3u";            const char RADIO_P5_NAME[]          PROGMEM = "P5";
const char RADIO_P6[]          PROGMEM = "live-icy.gss.dr.dk/A/A29H.mp3.m3u";            const char RADIO_P6_NAME[]          PROGMEM = "P6";
const char RADIO_P7[]          PROGMEM = "live-icy.gss.dr.dk/A/A21H.mp3.m3u";            const char RADIO_P7_NAME[]          PROGMEM = "P7";
const char RADIO_P8[]          PROGMEM = "live-icy.gss.dr.dk/A/A22H.mp3.m3u";            const char RADIO_P8_NAME[]          PROGMEM = "P8";
const char RADIO_NYHEDER[]     PROGMEM = "live-icy.gss.dr.dk/A/A02L.mp3.m3u";            const char RADIO_NYHEDER_NAME[]     PROGMEM = "Nyheder"; // L eller H?

const char RADIO_KLASSISK[]    PROGMEM = "onair.100fmlive.dk/klassisk_live.mp3.m3u";     const char RADIO_KLASSISK_NAME[]    PROGMEM = "Klassisk";
const char RADIO_24SYV[]       PROGMEM = "streaming.radio24syv.dk/pls/24syv_64_IR.pls";  const char RADIO_24SYV_NAME[]       PROGMEM = "24syv"; 
const char RADIO_JAZZGROOVE[]  PROGMEM = "199.180.72.2:8015/listen.pls";                 const char RADIO_JAZZGROOVE_NAME[]  PROGMEM = "JazzGroove"; // "77.67.106.49/stream" 
const char RADIO_JAZZFM[]      PROGMEM = "listenlive.eu/jazzfmuk.m3u";                   const char RADIO_JAZZFM_NAME[]      PROGMEM = "JazzFM"; 

/*
http://www.listenlive.eu/jazzfmuk.m3u
Jazz FM  London  United Kingdom


*/

boolean readResponse = false;

/* 
 *  Setup once
 */
void setup()
{
    const int ETH_DELAY = 200; // Not clear how much is needed here (and why...)

#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Starting ethernet");
    delay(ETH_DELAY);
#endif
    Ethernet.begin(arduino_mac, arduino_ip);
#ifdef DEBUG
    delay(ETH_DELAY);
    Serial.println("Ethernet started");
#endif
    setupKeyboard();

    ledInit();
}

/*
 * Main looop
 */
void loop()
{
    char key = 0;
#ifdef DEBUG
    if (Serial.available() > 0) {
        key = Serial.read();
        Serial.println(key);
    } else
#endif
        key = loopKeyboard();
    

    if (key != 0) {
        ledCommunicating();

        switch (key) {
            case '*': sonosVolMinus();                                              break;
            case '#': sonosVolPlus();                                               break;
            case '0': sonosPause();                                                 break;
            case '1': sonosRadioStation(RADIO_P1,          RADIO_P1_NAME);          break;
            case '2': sonosRadioStation(RADIO_P2,          RADIO_P2_NAME);          break;
            case '3': sonosRadioStation(RADIO_P3,          RADIO_P3_NAME);          break;
            case '4': sonosRadioStation(RADIO_P4,          RADIO_P4_NAME);          break;
            case '5': sonosRadioStation(RADIO_P5,          RADIO_P5_NAME);          break;
            case '6': sonosRadioStation(RADIO_P6,          RADIO_P6_NAME);          break;
            case '7': sonosRadioStation(RADIO_P7,          RADIO_P7_NAME);          break;
            case '8': sonosRadioStation(RADIO_P8,          RADIO_P8_NAME);          break;
            case '9': sonosRadioStation(RADIO_NYHEDER,     RADIO_NYHEDER_NAME);     break;
            case 'A': sonosRadioStation(RADIO_KLASSISK,    RADIO_KLASSISK_NAME);    break;
            case 'B': sonosRadioStation(RADIO_24SYV,       RADIO_24SYV_NAME);       break;
            case 'C': sonosRadioStation(RADIO_JAZZGROOVE,  RADIO_JAZZGROOVE_NAME);  break;
            case 'D': sonosRadioStation(RADIO_JAZZFM,      RADIO_JAZZFM_NAME);      break;
            default: readResponse = false;                                          break;
        }
    }
 
    ledCheckTimeout();
}


