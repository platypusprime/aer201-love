#include "LineFollower.h"

const short SENSOR_SELECT[] = { 8, 9 };
const short SENSOR_OUTPUT = A5;

const short LEFT_SPEED = 10;
const short LEFT_DIR = 13;
const short RIGHT_SPEED = 11;
const short RIGHT_DIR = 12;

bool calibrated = false;
int threshold = 0;

int leftSpd = 100, rightSpd = 100;
const int ADJUSTMENT = 50;

void setup() {
	//setup sensors
	pinMode(SENSOR_SELECT[0], OUTPUT);
	pinMode(SENSOR_SELECT[1], OUTPUT);

	// setup motors
	pinMode(LEFT_SPEED, OUTPUT);
	pinMode(LEFT_DIR, OUTPUT);
	pinMode(RIGHT_SPEED, OUTPUT);
	pinMode(RIGHT_DIR, OUTPUT);
}

void loop() {
	if (!calibrated)
		calibrate();

	int ml = readSensor(0);
	int mr = readSensor(1);

	if (ml > threshold && mr > threshold) {
		// go straight
	} else if (ml > threshold) {
		leftSpd += ADJUSTMENT;
	} else if (mr > threshold) {
		rightSpd += ADJUSTMENT;
	} else {
		//cry in circles
	}

	adjustMotors();
}

int readSensor(int i, int j) {
	if (i)
		digitalWrite(SENSOR_SELECT[0], LOW);
	else
		digitalWrite(SENSOR_SELECT[0], HIGH);

	if (j)
		digitalWrite(SENSOR_SELECT[1], LOW);
	else
		digitalWrite(SENSOR_SELECT[1], HIGH);

	return analogRead(SENSOR_OUTPUT);
}

int readSensor(int sensor) {
	switch (sensor) {
	case 0:
		return readSensor(0, 0);
	case 1:
		return readSensor(0, 1);
	case 2:
		return readSensor(1, 0);
	case 3:
		return readSensor(1, 1);
	default:
		return -1;
	}
}

void calibrate() {
//	int darkVals[10];
//	int lightVals[10];
	int total = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			total += readSensor(j);
		}
		//		darkVals[i] = readSensor(0);
//		lightVals[i] = readSensor(2);
//		i++;
//		darkVals[i] = readSensor(1);
//		lightVals[i] = readSensor(3);
	}

	threshold = total / 40; // TODO replace with shift
	calibrated = true;
}

void adjustMotors() {
	digitalWrite(LEFT_DIR, HIGH);
	analogWrite(LEFT_SPEED, leftSpd);
	digitalWrite(RIGHT_DIR, HIGH);
	analogWrite(RIGHT_SPEED, rightSpd);
}
