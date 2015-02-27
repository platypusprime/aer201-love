#include "Test.h"

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const short SENSOR_SELECT[] = { 8, 9 };
const short SENSOR_OUTPUT = A4;

const short LEFT_SPEED = 10;
const short LEFT_DIR = 13;
const short RIGHT_SPEED = 11;
const short RIGHT_DIR = 12;

bool serialTested = false;

void setup() {
	Serial.begin(9600);
	pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
	pinMode(SENSOR_OUTPUT, INPUT);
	setupLCD();
	setupSensors();
	setupMotors();
}

// the loop function runs over and over again forever
void loop() {

//	testConnection();
	//	testLCD();
	testSensors();
	testMotors();
//	delay(500);

	//if (!serialTested) {
		//testSerial();
	//}
}

void setupLCD() {
	lcd.begin(16, 2);
}

void setupSensors() {
	pinMode(SENSOR_SELECT[0], OUTPUT);
	pinMode(SENSOR_SELECT[1], OUTPUT);
}

void setupMotors() {
	pinMode(LEFT_SPEED, OUTPUT);
	pinMode(LEFT_DIR, OUTPUT);
	pinMode(RIGHT_SPEED, OUTPUT);
	pinMode(RIGHT_DIR, OUTPUT);
}

void testConnection() {
	digitalWrite(13, HIGH);
	Serial.println(1);
	delay(250);
	digitalWrite(13, LOW);
	delay(250);
	digitalWrite(13, HIGH);
	Serial.println(2);
	delay(250);
	digitalWrite(13, LOW);
	delay(250);
	digitalWrite(13, HIGH);
	Serial.println(3);
	delay(250);
	digitalWrite(13, LOW);
	delay(2000);
}

void testLCD() {
	lcd.setCursor(0, 1);
	// print the number of seconds since reset:
	lcd.print(millis() / 1000);
}

void testSensors() {
	lcd.home();
	lcd.print("OR:");
	lcd.print(readSensor(0, 0));
	lcd.print(" ");

	lcd.setCursor(8, 0);
	lcd.print("?L:");
	lcd.print(readSensor(0, 1));
	lcd.print("  ");

	lcd.setCursor(0, 1);
	lcd.print("CR:");
	lcd.print(readSensor(1, 0));
	lcd.print("  ");

	lcd.setCursor(8, 1);
	lcd.print("?L:");
	lcd.print(readSensor(1, 1));
	lcd.print("  ");
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

	delay(300);
	return analogRead(SENSOR_OUTPUT);
}

void testMotors() {
	digitalWrite(LEFT_DIR, HIGH);
	analogWrite(LEFT_SPEED, 100);
	digitalWrite(RIGHT_DIR, HIGH);
	analogWrite(RIGHT_SPEED, 100);

}

void testSerial() {
	Serial.println("board_drop-2-WHITE");
	delay(500);
	Serial.println("board_drop-2-BLACK");
	delay(500);
	Serial.println("board_drop-3-WHITE");
	delay(500);
	Serial.println("board_drop-6-WHITE");
	delay(500);
	Serial.println("board_drop-0-BLACK");
	delay(500);
	Serial.println("board_drop-1-WHITE");
	delay(500);
	Serial.println("board_drop-5-BLACK");
	serialTested = true;
}
