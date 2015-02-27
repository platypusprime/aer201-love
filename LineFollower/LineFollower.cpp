#include "LineFollower.h"
#include "Sensor.h"

//const short SENSOR_SELECT[] = { 8, 9 };
//const short SENSOR_OUTPUT = A4;

const unsigned long CALIB_TIME = 3000;

const short LEFT_SPEED = 10;
const short LEFT_DIR = 13;
const short RIGHT_SPEED = 11;
const short RIGHT_DIR = 12;

bool calibrated = false;
int threshold = 0;

// sensor pins hard-coded here
Sensor lineSensors[4] = { A1, A2, A3, A4 };

int leftSpd = 100, rightSpd = 100;
const int ADJUSTMENT = 50;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
	//setup sensors
	Serial.begin(9600);
	lcd.begin(16, 2);

// setup motors
	pinMode(LEFT_SPEED, OUTPUT);
	pinMode(LEFT_DIR, OUTPUT);
	pinMode(RIGHT_SPEED, OUTPUT);
	pinMode(RIGHT_DIR, OUTPUT);
}

void loop() {
	if (!calibrated)
		calibrateSensors();

	bool *sensorOutput = readSensors();

	if (sensorOutput[1] && sensorOutput[2]) {
		leftSpd = 255;
		rightSpd = 255;
	} else if (sensorOutput[1]) {
//		leftSpd += ADJUSTMENT;
		leftSpd = 0;
		rightSpd = 255;
	} else if (sensorOutput[2]) {
//		rightSpd += ADJUSTMENT;
		leftSpd = 255;
		rightSpd = 0;
	} else {
		//cry in circles
	}

	delete[] sensorOutput;

	delay(200);

	adjustMotors();
}

void calibrateSensors() {
	// move the sensors on and off the black lines while this is running
	lcd.clear();
	lcd.print("CALIBRATING");
	long start = millis();
	while (millis() - start < CALIB_TIME) {
		lcd.setCursor(0, 1);
		lcd.print(CALIB_TIME - millis() + start);
		lcd.print("    ");
		for (int j = 0; j < 4; j++) {
			lineSensors[j].addCalibrationValue();
		}
	}
	lcd.clear();
	calibrated = true;
}

bool* readSensors() {
	bool* output = new bool[4];
	for (int i = 0; i < 4; i++)
		output[i] = lineSensors[i].onLine();

	// print results on LCD
	lcd.setCursor(1, 0);
	if (output[0])
		lcd.print("B");
	else
		lcd.print("W");
	lcd.setCursor(0, 1);
	lcd.print(lineSensors[0].read());
	lcd.print("    ");

	lcd.setCursor(5, 0);
	if (output[1])
		lcd.print("B");
	else
		lcd.print("W");
	lcd.setCursor(4, 1);
	lcd.print(lineSensors[1].read());
	lcd.print("    ");

	lcd.setCursor(9, 0);
	if (output[2])
		lcd.print("B");
	else
		lcd.print("W");
	lcd.setCursor(8, 1);
	lcd.print(lineSensors[2].read());
	lcd.print("    ");

	lcd.setCursor(13, 0);
	if (output[3])
		lcd.print("B");
	else
		lcd.print("W");
	lcd.setCursor(12, 1);
	lcd.print(lineSensors[3].read());
	lcd.print("    ");

	return output;
}

void adjustMotors() {
	digitalWrite(LEFT_DIR, HIGH);
	analogWrite(LEFT_SPEED, leftSpd);
	digitalWrite(RIGHT_DIR, HIGH);
	analogWrite(RIGHT_SPEED, rightSpd);
}
