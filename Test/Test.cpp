// Do not remove the include below
#include "Test.h"

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
	Serial.begin(9600);
	pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
	digitalWrite(13, HIGH);
	delay(250);
	digitalWrite(13, LOW);
	delay(250);
	digitalWrite(13, HIGH);
	delay(250);
	digitalWrite(13, LOW);
	delay(250);
	digitalWrite(13, HIGH);
	delay(250);
	digitalWrite(13, LOW); // turn the LED off by making the voltage LOW
	delay(2000); // wait for a second
}
