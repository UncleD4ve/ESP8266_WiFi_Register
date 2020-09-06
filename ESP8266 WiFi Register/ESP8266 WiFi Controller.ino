#include "WiFiController.h"

#define DNS_SSID "SmartRegister"

WiFiController WiFiContr(DNS_SSID,0);
uint32_t previousMillis(0);

void preinit() {
	ESP8266WiFiClass::preinitWiFiOff();
}

void setup()
{
	Serial.begin(115200);
	yield();
	Serial.println(ESP.getFreeHeap(), DEC);

	WiFiContr.begin();
}
void loop()
{
	yield(); 


	if (millis() - previousMillis >= 660000) {
		WiFiContr.connect();
	}
	//ESP.restart();
}


