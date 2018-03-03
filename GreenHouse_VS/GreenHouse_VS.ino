#include <ArduinoJson.h>
#include <MsTimer2.h>
#include "String.h"
//#include "SensorData.h"
#include "JsonRasberry.h"

SensorData Sensor;
JsonRasberry JR;//������������� ������ ��� ���������� JSON �� Rasberry

boolean stringComplete = false;
//SensorData SensorDat;
void setup(void)
{
	Serial.begin(9600);
	MsTimer2::set(5000, function); // ������ 5 � �������� �������, ���������� ���������� � �������� � ����������
								   // JSON � Serial.
	pinMode(3, OUTPUT);
	pinMode(8, OUTPUT);
	digitalWrite(3, LOW);
	digitalWrite(8, LOW);
	MsTimer2::start();

}

void function()
{
	Sensor.calc();
	if (JR.success)
	{
		JR.calc(Sensor);
	}
}

void serialEvent()
{
	MsTimer2::stop();
	while (Serial.available())
	{
		char inChar = (char)Serial.read();
		JR.StrJson += inChar;
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
	Serial.println(JR.StrJson);
	Serial.println(JR.StrJson.length());

	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(JR.StrJson);
	if (!root.success()) {
		Serial.println("parseObject() failed");
	}
	else
	{
		Serial.println("parseObject success");
		JR.AddData((int)root["SoilMoistureLimits"][0], (int)root["SoilMoistureLimits"][1], (bool)root["Light"],
			(int)root["AirTemperatureLimits"][0], (int)root["AirTemperatureLimits"][1],
			(int)root["SoilTemperatureLimits"][0], (int)root["SoilTemperatureLimits"][1]);
	}
}
void loop(void) {
	//8 ����� 3 �����������

	//  digitalWrite(pin, value)
	if (stringComplete) {
		inputJson();// ��������� ������������ json, ��� �� ����� ���������� �������.
		JR.StrJson = "";// ������� ������:
		stringComplete = false;
	}
}

