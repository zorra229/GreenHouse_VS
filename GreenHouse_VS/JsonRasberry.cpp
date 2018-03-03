// 
// 
// 
#include "JsonRasberry.h"
JsonRasberry::JsonRasberry()
{

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

}

void JsonRasberry::calc(const SensorData &Sensor)
{
	if (SoilMoistureMin<Sensor.DataGroundGygrometer[0])
	{
		Serial.println("success");
	}
}


