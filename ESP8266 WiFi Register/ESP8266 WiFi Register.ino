#include "WiFiRegister.h"

#define DNS_SSID "SmartRegister"

void preinit() {
	ESP8266WiFiClass::preinitWiFiOff();
}

void setup()
{
	Serial.begin(115200);
	yield();
	
	Serial.println(ESP.getFreeHeap(), DEC);

	WiFiRegister WiFiController(DNS_SSID);
	//WiFiController.begin();
	WiFiController.forceWifiERegister();
}
void loop()
{
	yield(); 
	//ESP.restart();
}


