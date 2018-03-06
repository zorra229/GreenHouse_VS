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
	if (light)
	{
		Sensor.Light = 1;
		digitalWrite(8, HIGH);
	}
	else
	{
		Sensor.Light = 0;
		digitalWrite(8, LOW);
	}
	//Полив еще не реализован шаблонно выглядит след образом
	if (Sensor.DataGroundGygrometer[0] < SoilMoistureMin)
	{
		MsTimer2::stop();
		//Включить полив на 1 м горшке
		MsTimer2::start();
	}
	if (Sensor.DataGroundGygrometer[1] < SoilMoistureMin)
	{
		MsTimer2::stop();
		//Включить полив на 2 м горшке
		MsTimer2::start();
	}
	if (Sensor.DataGroundGygrometer[2] < SoilMoistureMin)
	{
		MsTimer2::stop();
		//Включить полив на 3 м горшке
		MsTimer2::start();
	}
	if (Sensor.DataGroundGygrometer[3] < SoilMoistureMin)
	{
		MsTimer2::stop();
		//Включить полив на 4 м горшке
		MsTimer2::start();
	}
	if (Sensor.BmeData[0] < AirTemperatureMin)
	{
		MsTimer2::stop();
		//тут должен быть код, реализующий нагрев
		MsTimer2::start();
	}
	else if (Sensor.BmeData[0] > AirTemperatureMax)
	{
		MsTimer2::stop();
		//тут должен быть код, реализующий охлаждение пока пробная версия, запускающая вентиляторы
		digitalWrite(3, HIGH);
		MsTimer2::start();
	}


}


