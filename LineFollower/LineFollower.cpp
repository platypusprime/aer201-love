#include "LineFollower.h"
#include "Sensor.h"

// LCD fields
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
const byte LIGHT_SYMB = 2;
byte lightSymbol[8] = { B00000, B01110, B10001, B10001, B10001, B01110, B00000,
		B00000 };
const byte DARK_SYMB = 3;
byte darkSymbol[8] = { B00000, B01110, B11111, B11111, B11111, B01110, B00000,
		B00000 };

// sensor fields
Sensor lineSensors[4] = { A1, A2, A3, A4 };
bool calibrated = false;
const unsigned long CALIB_TIME = 3000;
int threshold = 0;
bool* sensorOutput;

// motor fields
int lSpd = 30, rSpd = 30;
const int ADJUSTMENT_MAJOR = 5;
const int ADJUSTMENT_MINOR = 3;
const short LEFT_SPEED = 10;
const short LEFT_DIR = 13;
const short RIGHT_SPEED = 11;
const short RIGHT_DIR = 12;

void setup() {
	// setup interface
	Serial.begin(9600);
	lcd.createChar(LIGHT_SYMB, lightSymbol);
	lcd.createChar(DARK_SYMB, darkSymbol);
	lcd.begin(16, 2);

	// setup motors
	pinMode(LEFT_SPEED, OUTPUT);
	pinMode(LEFT_DIR, OUTPUT);
	pinMode(RIGHT_SPEED, OUTPUT);
	pinMode(RIGHT_DIR, OUTPUT);

	// initialize sensor storage
	sensorOutput = new bool[4];
}

void loop() {
	if (calibrated)
		adjustMotors();
	else {
//		digitalWrite(LEFT_DIR, HIGH);
//		analogWrite(LEFT_SPEED, 0);
//		digitalWrite(RIGHT_DIR, LOW);
//		analogWrite(RIGHT_SPEED, 0);
		calibrateSensors();
	}

	readSensors(sensorOutput);

	if (sensorOutput[1] && sensorOutput[2]) {
//DO NOTHING
		//		// set motors equal
//		if (leftSpd > rightSpd)
//			leftSpd = rightSpd;
//		else
//			rightSpd = leftSpd;
	} else if (sensorOutput[1]) {
		rSpd += ADJUSTMENT_MAJOR;
		lSpd -= ADJUSTMENT_MINOR;

	} else if (sensorOutput[2]) {
		lSpd += ADJUSTMENT_MAJOR;
		rSpd -= ADJUSTMENT_MINOR;
	} else {
		// TODO cry in circles
	}

	delay(100); // limit output signal rate

}

void calibrateSensors() {

	// manually slide the sensors on and off the black lines while this is running
	lcd.clear();
	lcd.print("CALIBRATING");

	// run for a set time period
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

	//	stop calibration on subsequent loops
	calibrated = true;
	startMotors();
}

void readSensors(bool* &output) {

	// query sensors
	for (int i = 0; i < 4; i++)
		output[i] = lineSensors[i].onLine();
	// print results on LCD
	printSensorReadings(output);
}

void printSensorReadings(bool* sensorOutput) {

	lcd.setCursor(1, 0);
	if (sensorOutput[0])
		lcd.write(DARK_SYMB);
	else
		lcd.write(LIGHT_SYMB);
	lcd.setCursor(0, 1);
	lcd.print(lineSensors[0].read());
	lcd.print("    ");

	lcd.setCursor(5, 0);
	if (sensorOutput[1])
		lcd.write(DARK_SYMB);
	else
		lcd.write(LIGHT_SYMB);
	lcd.setCursor(4, 1);
	lcd.print(lineSensors[1].read());
	lcd.print("    ");

	lcd.setCursor(9, 0);
	if (sensorOutput[2])
		lcd.write(DARK_SYMB);
	else
		lcd.write(LIGHT_SYMB);
	lcd.setCursor(8, 1);
	lcd.print(lineSensors[2].read());
	lcd.print("    ");

	lcd.setCursor(13, 0);
	if (sensorOutput[3])
		lcd.write(DARK_SYMB);
	else
		lcd.write(LIGHT_SYMB);
	lcd.setCursor(12, 1);
	lcd.print(lineSensors[3].read());
	lcd.print("    ");
}

void startMotors() {
	digitalWrite(LEFT_DIR, HIGH);
	analogWrite(LEFT_SPEED, 255);
	digitalWrite(RIGHT_DIR, HIGH);
	analogWrite(RIGHT_SPEED, 255);
	delay(100);
	adjustMotors();
}
void adjustMotors() {
	digitalWrite(LEFT_DIR, HIGH);
	analogWrite(LEFT_SPEED, lSpd);
	digitalWrite(RIGHT_DIR, HIGH);
	analogWrite(RIGHT_SPEED, rSpd);
}

