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
	//Полив еще не реализован шаблонно выглядит след образом
	if (Sensor.DataGroundGygrometer[0] < SoilMoistureMin)
	{
		//Включить полив на 1 м горшке
	}
	if (Sensor.DataGroundGygrometer[1] < SoilMoistureMin)
	{
		//Включить полив на 2 м горшке
	}
	if (Sensor.DataGroundGygrometer[2] < SoilMoistureMin)
	{
		//Включить полив на 3 м горшке
	}
	if (Sensor.DataGroundGygrometer[3] < SoilMoistureMin)
	{
		//Включить полив на 4 м горшке
	}
	if (Sensor.BmeTemperature < AirTemperatureMin)
	{
		//тут должен быть код, реализующий нагрев
	}
	else if (Sensor.BmeTemperature > AirTemperatureMax)
	{
		//тут должен быть код, реализующий охлаждение пока пробная версия, запускающая вентиляторы
		digitalWrite(3, HIGH);
	}


}


