/*
 * Sensor.cpp
 *
 *  Created on: 2015-02-24
 *      Author: Joel
 */

#include "Sensor.h"

Sensor::Sensor(short pin) :
		pin(pin), calibMax(0), calibMin(1023) {
}

void Sensor::addCalibrationValue() {
	short newCalibVal = read();
	if (newCalibVal > calibMax)
		calibMax = newCalibVal;
	if (newCalibVal < calibMin)
		calibMin = newCalibVal;

	// threshold val is mean value of max and min
	threshold = (calibMax + calibMin) / 2;
}

short Sensor::read() {
	return analogRead(pin);
}

bool Sensor::onLine() {
	return read() < threshold;
}

Sensor::~Sensor() {
}

