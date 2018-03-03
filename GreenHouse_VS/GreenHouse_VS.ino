#include <ArduinoJson.h>
#include <MsTimer2.h>
#include "String.h"
//#include "SensorData.h"
#include "JsonRasberry.h"

SensorData Sensor;
JsonRasberry JR;//инициализация класса для считывания JSON от Rasberry
String StrJson = "";
boolean stringComplete = false;
//SensorData SensorDat;
void setup(void)
{
	Serial.begin(9600);
	MsTimer2::set(5000, function); // каждые 5 с вызывает функцию, считывющую показатели с датчиков и отправляет
								   // JSON в Serial.
	pinMode(3, OUTPUT);
	pinMode(8, OUTPUT);
	digitalWrite(3, LOW);
	digitalWrite(8, LOW);
	MsTimer2::start();

}

void function()
{
	Sensor.calc();
}

void serialEvent()
{
	MsTimer2::stop();
	while (Serial.available())
	{
		char inChar = (char)Serial.read();
		StrJson += inChar;
		if (inChar == '\n')
		{
			stringComplete = true;
			MsTimer2::start();
			return;
		}
	}
}
void inputJson()
{
	Serial.println(StrJson);
	Serial.println(StrJson.length());

	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(StrJson);
	if (!root.success()) {
		Serial.println("parseObject() failed");
	}
	else
	{
		Serial.println("parseObject success");
		JR.AddData((int)root["SoilMoistureLimits"][0], (int)root["SoilMoistureLimits"][1], (bool)root["Light"],
			(int)root["AirTemperatureLimits"][0], (int)root["AirTemperatureLimits"][1],
			(int)root["SoilTemperatureLimits"][0], (int)root["SoilTemperatureLimits"][1]);
		JR.calc(Sensor);
	}
}
void loop(void) {
	//8 лампы 3 вентиляторы

	//  digitalWrite(pin, value)
	if (stringComplete) {
		inputJson();// обработка принимаемого json, там же вызов необходмых функций.
					// очищаем строку:
		StrJson = "";
		stringComplete = false;
	}
}

