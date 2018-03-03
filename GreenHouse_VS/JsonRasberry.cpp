// 
// 
// 
#include "JsonRasberry.h"
JsonRasberry::JsonRasberry()
{
	StrJson = "";

	SoilMoistureMin = 0;
	SoilMoistureMax = 0;

	AirTemperatureMin = 0;
	AirTemperatureMax = 0;

	SoilTemperatureMin = 0;
	SoilTemperatureMax = 0;
	
	success = 0;

}

void JsonRasberry::AddData(int SoilMoistureMin, int SoilMoistureMax, bool light, int AirTemperatureMin, int AirTemperatureMax, int SoilTemperatureMin, int SoilTemperatureMax)
{
	this->SoilMoistureMin = SoilMoistureMin;
	this->SoilMoistureMax = SoilMoistureMax;

	this->light = light;

	this->AirTemperatureMin = AirTemperatureMin;
	this->AirTemperatureMax = AirTemperatureMax;

	this->SoilTemperatureMin = SoilTemperatureMin;
	this->SoilTemperatureMax = SoilTemperatureMax;

	success = 1;

}

void JsonRasberry::calc(SensorData &Sensor)
{
	if(light)
		digitalWrite(8, HIGH);
	else
		digitalWrite(8, LOW);
	//����� ��� �� ���������� �������� �������� ���� �������
	if (Sensor.DataGroundGygrometer[0] < SoilMoistureMin)
	{
		//�������� ����� �� 1 � ������
	}
	if (Sensor.DataGroundGygrometer[1] < SoilMoistureMin)
	{
		//�������� ����� �� 2 � ������
	}
	if (Sensor.DataGroundGygrometer[2] < SoilMoistureMin)
	{
		//�������� ����� �� 3 � ������
	}
	if (Sensor.DataGroundGygrometer[3] < SoilMoistureMin)
	{
		//�������� ����� �� 4 � ������
	}
	if (Sensor.BmeTemperature < AirTemperatureMin)
	{
		//��� ������ ���� ���, ����������� ������
	}
	else if (Sensor.BmeTemperature > AirTemperatureMax)
	{
		//��� ������ ���� ���, ����������� ���������� ���� ������� ������, ����������� �����������
		digitalWrite(3, HIGH);
	}


}


