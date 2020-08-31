#ifndef EEPROMController_h
#define EEPROMController_h
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>

class EEPROMController {
public:
	EEPROMController();
	bool saveWifi(String &, String &);
	void readWifi(String &, String &);
	void displayEEPROM();
	bool setConfig(bool);
	void resetConfig();
	bool getConfig();
};
#endif