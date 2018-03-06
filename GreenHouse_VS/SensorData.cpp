// 
// 
// 
#include <ArduinoJson.h>
#include "String.h"
#include "SensorData.h"
#include <OneWire.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

Adafruit_BME280 bme; // I2C �������� ������� bme ������ Adafruit_BME280. ���������� ������ ������� �����������.
OneWire ds(13);  //GroundTemperatureSensors �� 12-�� ����

SensorData::SensorData()
{
	Watering = 0;
	Light = 0;
	Heating = 0;
	Blowing = 0;
}


void SensorData::calc()
{

	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();

	//root["GroundTemperatureSensors"] = "";
	//double DataGroundTemperatureSensors[2];

	if (GroundTemperatureSensors(DataGroundTemperatureSensors)) //����� ������� �������� �������� GroundTemperatureSensors
	{
		JsonArray& DataGroundTemperatureSensor = root.createNestedArray("DataGroundTemperatureSensor");
		DataGroundTemperatureSensor.add(DataGroundTemperatureSensors[0]);
		DataGroundTemperatureSensor.add(DataGroundTemperatureSensors[1]);
		DataGroundTemperatureSensor.add(DataGroundTemperatureSensors[2]);
	}

	if (BmeCalc(BmeData))
	{
		root["DataBME280Temp"] = BmeData[0];
		root["DataBME280Humidity"] = BmeData[1];
		root["DataBME280Pressure"] = BmeData[2];
	}

	

	//root["GroundGygrometer1"] = "";
	JsonArray& DataGroundGygrometers = root.createNestedArray("DataGroundGygrometers");
	DataGroundGygrometer[0] = analogRead(A0);
	DataGroundGygrometers.add(DataGroundGygrometer[0]);

	//root["GroundGygrometer2"] = "";
	DataGroundGygrometer[1] = analogRead(A1);
	DataGroundGygrometers.add(DataGroundGygrometer[1]);

	//root["GroundGygrometer3"] = "";
	DataGroundGygrometer[2] = analogRead(A2);
	DataGroundGygrometers.add(DataGroundGygrometer[2]);

	//root["GroundGygrometer4"] = "";
	DataGroundGygrometer[3] = analogRead(A3);
	DataGroundGygrometers.add(DataGroundGygrometer[3]);

	root["Watering"] = Watering;
	root["Light"] = Light;
	root["Heating"] = Heating;
	root["Blowing"] = Blowing;
	//root.printTo(Serial);
	//Serial.println();
	root.prettyPrintTo(Serial);
	Serial.println();
}
bool SensorData::GroundTemperatureSensors(double *DataGroundTemperatureSensors)
{
	byte i = 0;
	byte addr[8];

	ds.reset_search(); //�������� ����� �����. ��������� ������������� ������ �������� �� ������ ����������.
	if (ds.search(addr) == false)
	{
		Serial.println("Can't find GroundTemperatureSensors pls chekc it and reload");
		return 0;
		//break;
	}
	else
	{
		ds.reset();
		ds.write(0xCC);           // ������� 0xCC - �������� ������� ���� ������� �����������
		ds.write(0x44, 1);         // ��������� ��������� � �������� ���������� �������
		delay(1000);     // 750 ����������� ����� �������, � ����� � ���
		do
		{
			//�������� �� ����������� ������
			if (OneWire::crc8(addr, 7) != addr[7]) {
				Serial.print("CRC is not valid!\n");  //  "CRC �� ���������!\n")
				return 0;
			}
			//Serial.print("number of devices = ");
			//Serial.println(i);
			DataGroundTemperatureSensors[i] = temp(addr);
			i++;
		} while (ds.search(addr));

		return 1;
	}
}
double SensorData::temp(byte addr[8])
{
	byte data[12];
	int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
	byte i = 0;
	ds.reset();
	ds.select(addr);
	ds.write(0xBE);         // ��������� scratchpad-������

	for (i = 0; i < 9; i++) {           // ��� ����� 9 ������
		data[i] = ds.read();
	}
	LowByte = data[0];
	HighByte = data[1];
	TReading = (HighByte << 8) + LowByte;
	SignBit = TReading & 0x8000;  // ��������� �������� � ����� ������� ����
	if (SignBit) // ���� �������� �������������
	{
		TReading = (TReading ^ 0xffff) + 1;
	}
	Tc_100 = (6 * TReading) + TReading / 4;    // �������� �� (100 * 0.0625) ��� 6.25

	Whole = Tc_100 / 100;  // �������� ���� �� ����� ����� � ������� ������ 
	Fract = Tc_100 % 100;
	double temperature = Fract;
	while ((temperature /= 10) > 1);
	temperature += Whole;

	if (SignBit) // ���� ����� �������������
	{
		temperature = 0 - temperature;
	}
	return temperature;
}

bool SensorData::BmeCalc(double *BmeData)
{
	bool status;
	status = bme.begin(0x76);
	if (!status) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		return 0;
	}
	else
	{

		//root["BME280"] = "";
		//JsonArray& DataBME280 = root.createNestedArray("DataBME280");
		//DataBME280.add(bme.readTemperature());
		//D1ataBME280.add(bme.readPressure() / 100.0F);
		//DataBME280.add(bme.readHumidity());
		this->BmeData[0] = bme.readTemperature();
		this->BmeData[1] = bme.readHumidity();
		this->BmeData[2] = bme.readPressure() / 100.0F;
		return 1;
	}
}



