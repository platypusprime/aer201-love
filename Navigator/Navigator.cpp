// Do not remove the include below
#include "Navigator.h"
#include "LineSensor.h"
#include "CommDemo.h"

// pins
const short DEMUX_PINS[] = { 11, 12, 13, 8 };
const short MOTOR_SELECT_PINS[] = { 22, 24, 26, 3 };
const short RDIR_PIN = 6;
const short LDIR_PIN = 7;
const short RSPD_PIN = 9;
const short LSPD_PIN = 10;
const short RENA_PIN = 12;
const short LENA_PIN = 11;

// sensor fields
LineSensor lineSensors[6] = { A1, A2, A3, A4, A5, A6 };
const unsigned long CALIB_TIME = 3000;
bool* sensorIn;

// motor fields
const short BASE_SPD = 150;
const short ADJ_SPD_MAJOR = BASE_SPD, ADJ_SPD_MINOR = BASE_SPD - 30;
const short LOST_SPD_MAJOR = 200, LOST_SPD_MINOR = 100;

void setup() {
	Serial.begin(9600);
	Serial.println("Enter command code");

	//	setup pins
	for (int i = 0; i < 4; i++) {
		pinMode(DEMUX_PINS[i], OUTPUT);
		pinMode(MOTOR_SELECT_PINS[i], OUTPUT);
	}
	pinMode(RDIR_PIN, OUTPUT);
	pinMode(LDIR_PIN, OUTPUT);
	pinMode(RSPD_PIN, OUTPUT);
	pinMode(LSPD_PIN, OUTPUT);
	pinMode(RENA_PIN, OUTPUT);
	pinMode(LENA_PIN, OUTPUT);

}

void loop() {
	// check for console commands
	if (Serial.available()) {
		switch (Serial.parseInt()) {
		case 0: // setup
//			// select left motor 1
//			selectDemux(1, 0, 0, 0);
//			selectMotor(0, 0, 0, 0);
//
//			// select right motor 1
//			selectDemux(1, 0, 0, 1);
//			selectMotor(0, 0, 0, 0);
//
//			//relatch
//			selectDemux(0, 0, 0, 0);
			digitalWrite(RENA_PIN, HIGH);
			digitalWrite(LENA_PIN, HIGH);
//			calibrateSensors();
			break;
		case 1: // communication demo
			CommDemo::getInput();
			CommDemo::processInput();
			CommDemo::displayResults();
			break;
		case 2: // navigation demo
			adjustMotors(BASE_SPD, BASE_SPD, true, true);
//			move(0, 0, 1, 5);
			break;
		case 3: // gameboard demo
			adjustMotors(BASE_SPD, BASE_SPD, false, false);
			// TODO
			break;
		case 4: // obstacle demo
			// TODO
			forward(1);
			break;
		default:
			Serial.println("Invalid selection!");
			Serial.println("");
			Serial.println("Enter command code");
			return;
		}
		Serial.println("Done!");
		Serial.println("");
		Serial.println("Enter command code");
	}
}

void calibrateSensors() {
	// run for a set time period
	long start = millis();
	while (millis() - start < CALIB_TIME) {
		// TODO send serial output
		for (int j = 0; j < 6; j++) {
			lineSensors[j].addCalibrationValue();
		}
	}
	//	TODO startMotors();
}

void readSensors(bool* &output) {

	// query sensors
	for (int i = 0; i < 6; i++) {
		output[i] = lineSensors[i].sensesLine();
		//Serial.print(" ");
	}
	//Serial.println("");
}

void adjustMotors(short rSpd, short lSpd, bool rDir, bool lDir) {
	//// select [1000] on demux to unlatch motor directions
	//selectDemux(0, 1, 1, 1);

	// write directions
	digitalWrite(RDIR_PIN, rDir ? HIGH : LOW);
	digitalWrite(LDIR_PIN, !lDir ? HIGH : LOW);

	//// relatch
	//selectDemux(0, 0, 0, 0);

	// write speeds
	analogWrite(LSPD_PIN, lSpd);
	analogWrite(RSPD_PIN, rSpd);

}

void selectDemux(bool A3, bool A2, bool A1, bool A0) {
	digitalWrite(DEMUX_PINS[0], A0 ? HIGH : LOW);
	digitalWrite(DEMUX_PINS[1], A1 ? HIGH : LOW);
	digitalWrite(DEMUX_PINS[2], A2 ? HIGH : LOW);
	digitalWrite(DEMUX_PINS[3], A3 ? HIGH : LOW);
//	delay(100);
}

void selectMotor(bool M3, bool M2, bool M1, bool M0) {
	digitalWrite(MOTOR_SELECT_PINS[0], !M0 ? HIGH : LOW);
	digitalWrite(MOTOR_SELECT_PINS[1], !M1 ? HIGH : LOW);
	digitalWrite(MOTOR_SELECT_PINS[2], !M2 ? HIGH : LOW);
	digitalWrite(MOTOR_SELECT_PINS[3], !M3 ? HIGH : LOW);
//	delay(100);
}

void move(int x0, int y0, int x, int y) {
	forward(x - x0);
	turn((x - x0) * (y - y0));
	forward(y - y0);
}

void forward(int n) {
	int count = 0;
	while (count < n) {
		readSensors(sensorIn); // read line sensors into sensorInput

		// detected a cross
		if (sensorIn[0] && sensorIn[5]) {
			count++;
		} else if (matchesPattern(0, 1, 1, 0) || matchesPattern(1, 1, 1, 1)) {
			adjustMotors(BASE_SPD, BASE_SPD, true, true);
		} else if (matchesPattern(1, 1, 1, 0) || matchesPattern(1, 1, 0, 0)
				|| matchesPattern(1, 0, 0, 0) || matchesPattern(0, 1, 0, 0)) {
			adjustMotors(ADJ_SPD_MAJOR, ADJ_SPD_MINOR, true, true);
		} else if (matchesPattern(0, 1, 1, 1) || matchesPattern(0, 0, 1, 1)
				|| matchesPattern(0, 0, 0, 1) || matchesPattern(0, 0, 1, 0)) {
			adjustMotors(ADJ_SPD_MINOR, ADJ_SPD_MAJOR, true, true);
		} else {
			adjustMotors(LOST_SPD_MAJOR, LOST_SPD_MINOR, true, false);
		}
	}
}

bool matchesPattern(bool b1, bool b2, bool b3, bool b4) {
	return sensorIn[1] == b1 && sensorIn[2] == b2 && sensorIn[3] == b3
			&& sensorIn[4] == b4;
}

void turn(int dir) {
	if (dir > 0) {
		// TODO left turn
		do {
			adjustMotors(BASE_SPD, BASE_SPD, true, false);
		} while (sensorIn[0] && sensorIn[5]);
		do {
			adjustMotors(BASE_SPD, BASE_SPD, true, false);
		} while (!sensorIn[0] && !sensorIn[5]);
	} else {
		// TODO right turn
		do {
			adjustMotors(BASE_SPD, BASE_SPD, false, true);
		} while (sensorIn[0] && sensorIn[5]);
		do {
			adjustMotors(BASE_SPD, BASE_SPD, false, true);
		} while (!sensorIn[0] && !sensorIn[5]);
	}
}
