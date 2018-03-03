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
	//���� ������ �� ���� ��������
	void calc();

private:
	bool GroundTemperatureSensors(double *);//���������� ������ � ���� 1wire
	double temp(byte addr[8]);//���������� ������ � ������ �������, ��������� �� 1wire
};

#endif

