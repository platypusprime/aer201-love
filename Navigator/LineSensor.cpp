/*
 * LineSensor.cpp
 *
 *  Created on: 2015-03-02
 *      Author: Joel
 */

#include "LineSensor.h"
#include "Arduino.h"

LineSensor::LineSensor(short pin) :
		pin(pin), calibMax(0), calibMin(1023), threshold(511) {
}

LineSensor::~LineSensor() {
	// TODO Auto-generated destructor stub
}

void LineSensor::addCalibrationValue() {

	short newCalibVal = readAnalogValue(); // take reading

	if (newCalibVal > calibMax) // look for white value
		calibMax = newCalibVal;

	if (newCalibVal < calibMin) // look for black value
		calibMin = newCalibVal;

	// threshold value is mean value of max and min
	threshold = (calibMax + calibMin) / 2;
}

short LineSensor::readAnalogValue() {
	return analogRead(pin);
}

bool LineSensor::sensesLine() {
	short reading = readAnalogValue();
	bool output = reading > threshold;
	//Serial.print(output ? "X" : "O");
	//Serial.print(" (");
	//Serial.print(reading);
	//Serial.print(")");
	return output;
}
