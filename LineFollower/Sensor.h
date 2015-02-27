/*
 * Sensor.h
 *
 *  Created on: 2015-02-24
 *      Author: Joel
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "LineFollower.h"

class Sensor {
public:
	Sensor(short);
	void addCalibrationValue();
	short read();
	bool onLine();
	virtual ~Sensor();
private:
	short pin;
	short threshold;
	short calibMax,calibMin;
};

#endif /* SENSOR_H_ */
