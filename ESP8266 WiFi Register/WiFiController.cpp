#include "WiFiController.h"

WiFiController::WiFiController(const char* SSID, int8_t mode = 0) : _apName(SSID), _mode(mode) {}
WiFiController::WiFiController(const char* SSID): _apName(SSID), _mode(0) {}

void WiFiController::begin()
{
	if (!eeprom.getConfig())
	{
		WiFiRegister WiFiReg(_apName);
		WiFiReg.begin();
	}
	else
	{
		pinMode(14, INPUT);
		if (digitalRead(14) == LOW)
			eeprom.resetConfig();

		eeprom.readWifi(_ssid, _pass);

		WiFi.forceSleepWake();
		yield();
		connect();
	}
}

void WiFiController::forceWifiERegister()
{
	WiFiRegister WiFiReg(_apName);
	WiFiReg.begin();
}

bool WiFiController::connect()
{
	switch (_mode)
	{
		case 0:
		{	
			if (WiFi.status() == WL_CONNECTED)
				return true;

			if(WiFi.getMode() == 2)
				WiFi.softAPdisconnect();
			yield();

			if (!modeSTA())
				modeAP();
			return true;
		}
		case 1:
		{
			if (WiFi.status() != WL_CONNECTED)
				while (!modeSTA())
					delay(1000);
			return true;
		}
		case 2:
		{
			while (!modeAP())
				delay(1000);
			return true;
		}
		default:
		{
			yield();
			ESP.restart();
		}
	}
	return false;
}

bool WiFiController::modeSTA()
{
	WiFi.disconnect();
	yield();
	WiFi.mode(WIFI_STA);
	yield();
	Serial.print(F("STA mode "));

	uint32_t time1 = system_get_time(), time2;
	WiFi.begin((const char*)_ssid.c_str(), (const char*)_pass.c_str());
	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
		time2 = system_get_time();
		if (((time2 - time1) / 1e6) > 60)
		{
			Serial.println(F("false"));
			return false;
		}
	}

	Serial.print(F("true, Connected in: "));
	Serial.println((time2 - time1) / 1e6);
	return true;
}

bool WiFiController::modeAP()
{
	IPAddress apIP(5, 5, 5, 5);

	WiFi.disconnect();
	yield();
	WiFi.mode(WIFI_AP);
	yield();
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

	dnsServer.setTTL(1);
	dnsServer.start(53, "*", apIP);
	yield();

	if (WiFi.softAP(_apName)) {
		Serial.print(F("AP mode true "));
		Serial.println(_apName);
		return true;
	}
	else {
		Serial.println(F("AP mode false"));
		return false;
	}
}

bool WiFiController::checkInternet()
{
	if (_client.connect("httpbin.org", 80))
		return true;
	else
		return false;
}