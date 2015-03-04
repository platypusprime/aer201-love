/*
 * LineSensor.h
 *
 *  Created on: 2015-03-02
 *      Author: Joel
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

class LineSensor {
public:
	LineSensor(short);
	virtual ~LineSensor();

	void addCalibrationValue();
	short readAnalogValue();
	bool sensesLine();
private:
	short pin;
	short calibMax, calibMin;
	short threshold;
};

#endif /* LINESENSOR_H_ */
