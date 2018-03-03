// SensorData.h

#ifndef _SENSORDATA_h
#define _SENSORDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SensorData {
public:
	//data
	double DataGroundTemperatureSensors[3];
	double BmeTemperature;
	double BmeHumidity;
	double BmePressure;
	int DataGroundGygrometer[4];
	//construct
	SensorData();
	//сбор данных со всех датчиков
	void calc();

private:
	bool GroundTemperatureSensors(double *);//считывание данных с шины 1wire
	double temp(byte addr[8]);//считывание данных с одного датчика, сидяещего на 1wire
};

#endif

