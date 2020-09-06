#ifndef WiFiController_h
#define WiFiController_h
#include "WiFiRegister.h"
#include "EEPROMController.h"
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>

class WiFiController {
public:
	WiFiController(const char*, int8_t);
	WiFiController(const char*);
	void begin();
	void forceWifiERegister();
	bool connect();
	bool checkInternet();

private:
	EEPROMController eeprom;
	WiFiClient _client;
	DNSServer dnsServer;

	String _ssid;
	String _pass;
	const char* _apName;
	int8_t _mode;

	bool modeSTA();
	bool modeAP();

};
#endif