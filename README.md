# arduinos
Arduino based client for controlling Sonos internet radio through a simple keyboard + LED interface

Current implementation of Arduinos (= ARDUIno + soNOS) is designed for control of 2 Sonos devices, 
which have been grouped together.

The current implementation is based on hard-coded radio stations (Danish). These 
URLs are not easy to find on the internet, so happy hunting. URLs can be played with e.g. Windows 
Media Player (just pre-pend 'http://')

Future versions of Arduinos should preferably be based on the radio stations configured within your 
Sonos (tuneIn based, or whatever)

###Hardware:
- Arduino (Uno or Nano)
- Ethernet shield ( ENC28J60-based for the Nano)
- Red and green LED (I am using a combined device) + 220R resistor to GND
	- Green LED on digital I/O 6
	- Red LED on digital I/O 7
- 4*4 keyboard
	- Rows on digital I/O 2, 3, 4, 5
	- Columns on analog A0, A1, A2, A3
- Powersupply (I am using a cell-phone charger + USB cable)

###Features/limitations:
- Configurable within the file 'arduinos.h'
- 2 Sonos devices supported
- Sonos devices should be grouped together using another application
- Suports a 4*4 = 16 digit keypad
- Supports 2 LEDs for user feedback (e.g. red + green)
- Supports streaming from 14 internet radio stations
- The internet radio station URLs must be specified within the code
- Supports both Uno+shield and Nano+shield
	- Uno ethernet shield: Wiznet Ethernet w5100 based
	- Nano ethernet shield: Microchip ENJ28J60 based
- When using Microchip ENJ28J60, the UIPEthernet library must be installed (ttps://github.com/ntruchsess/arduino_uip)

###Disclaimer:
- This comes with absolutely no warranty or support. Use this at your own risk...

###Other resources:
- http://jpmens.net/2010/03/16/sonos-pause-switch/
- http://www.tweaking4all.com/hardware/arduino/arduino-enc28j60-ethernet/
- https://github.com/samdoshi/sonos-arduino
- http://bsteiner.info/articles/hidden-sonos-interface
- https://github.com/jishi/node-sonos-http-api

###Radio:
- http://code.openhub.net/file?fid=jMpcjEpvRf4nOYsBpPlKRukEGwc&cid=-TH0Exu9wdQ&s=&fp=3643&mp&projSelected=true#L0
- http://www.shoutcast.com/  
- https://www.internet-radio.com

###Todo:
- check that noDEBUG is working
- experiment with the ETH_DELAY
- fill in last 3 readio stations
