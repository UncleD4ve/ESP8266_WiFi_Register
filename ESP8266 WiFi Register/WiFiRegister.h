#ifndef WiFiController_h
#define WiFiController_h
#include "Arduino.h"
#include "indexBegin.h"
#include "indexEnd.h"
#include "WiFiRegister.h"
#include "EEPROMController.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

class WiFiRegister {
public:
	WiFiRegister(const char*);
	void begin();
	void forceWifiERegister();
private:
	ESP8266WebServer _server;
	EEPROMController eeprom;
	DNSServer dnsServer;
	WiFiClient _client;
	String _ssid;
	String _pass;
	const char * _apName;
	char _status[4];

	uint8_t encryptionTypeStr(uint8_t);
	uint8_t encryptionPowerStr(int8_t);
	const  char * encryptionColorStr(int8_t);
	String constructHTMLpage();

	void ssidFromWeb();
	void handleRoot();
	void status();
	void restart();
};
#endif