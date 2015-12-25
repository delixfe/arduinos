#include "arduinos.h"

const char SONOS_TAG_PROGRAM[] PROGMEM = "AVTransport:1#SetAVTransportURI";
const char RADIO_START[]       PROGMEM = "<u:SetAVTransportURI xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><CurrentURI>x-rincon-mp3radio://";
const char RADIO_END1[]        PROGMEM = "</CurrentURI><CurrentURIMetaData>&lt;DIDL-Lite xmlns:dc=&quot;http://purl.org/dc/elements/1.1/&quot; xmlns:upnp=&quot;urn:schemas-upnp-org:metadata-1-0/upnp/&quot; xmlns:r=&quot;urn:schemas-rinconnetworks-com:metadata-1-0/&quot; xmlns=&quot;urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/&quot;&gt;";
const char RADIO_END2[]        PROGMEM = "&lt;item id=&quot;R:0/0/21&quot; parentID=&quot;R:0/0&quot; restricted=&quot;true&quot;&gt;&lt;dc:title&gt;";
const char RADIO_END3[]        PROGMEM = "&lt;/dc:title&gt;&lt;upnp:class&gt;object.item.audioItem.audioBroadcast&lt;/upnp:class&gt;";
const char RADIO_END4[]        PROGMEM = "&lt;desc id=&quot;cdudn&quot; nameSpace=&quot;urn:schemas-rinconnetworks-com:metadata-1-0/&quot;&gt;SA_RINCON65031_&lt;/desc&gt;&lt;/item&gt;&lt;/DIDL-Lite&gt;</CurrentURIMetaData></u:SetAVTransportURI></s:Body></s:Envelope>";

/*
 * Wrap up and send package with address of the stream that should be played
 */
void sonosRadioStation(const char *pProgmem, const char *pProgmemStationName) {
    sonos(SONOS_TAG_PROGRAM, pProgmem, RADIO_START, RADIO_END1, RADIO_END2, pProgmemStationName, RADIO_END3, RADIO_END4);
    sonosPlay();
}


