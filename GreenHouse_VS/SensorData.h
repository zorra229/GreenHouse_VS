// SensorData.h
#pragma once;
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
	double BmeData[3];
	int DataGroundGygrometer[4];

	bool Watering;
	bool Light;
	bool Heating;
	bool Blowing;

	//construct
	SensorData();
	//���� ������ �� ���� ��������
	void calc();
	bool GroundTemperatureSensors(double *);//���������� ������ � ���� 1wire
	bool BmeCalc(double *);
private:
	double temp(byte addr[8]);//���������� ������ � ������ �������, ��������� �� 1wire
};

#endif

