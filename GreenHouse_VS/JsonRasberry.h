// JsonRasberry.h

#ifndef _JSONRASBERRY_h
#define _JSONRASBERRY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SensorData.h"
class JsonRasberry
{
public:
	JsonRasberry();
	void calc(const SensorData &Sensor);
	void AddData(int, int, bool, int, int, int, int);
private:
	int SoilMoistureMin;
	int SoilMoistureMax;

	bool light;

	int AirTemperatureMin;
	int AirTemperatureMax;

	int SoilTemperatureMin;
	int SoilTemperatureMax;
};

#endif

