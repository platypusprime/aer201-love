// Do not remove the include below
#include "CommDemo.h"

int x, y, o;
int pts[3][2];

void CommDemo::getInput() {
	Serial.println(
			"For the purposes of this data entry, the game field is to be viewed with the board as \"up\"");
	Serial.println("Distance is measured in pegs");

	Serial.println("Enter x-coord of hopper:");
	while (!Serial.available())
		continue;
	x = Serial.parseInt();

	Serial.println("Enter y-coord of hopper:");
	while (!Serial.available())
		continue;
	y = Serial.parseInt();

	Serial.println(
			"Enter orientation of hopper (1 for pointing to board, 0 pointing away):");
	while (!Serial.available())
		continue;
	o = Serial.parseInt();
}

void CommDemo::processInput() {
	pts[0][0] = x;
	pts[1][0] = x + 1;
	pts[1][1] = y;
	pts[2][0] = x - 1;
	pts[2][1] = y;
	if (o) { // board-pointing
		pts[0][1] = y + 1;
	} else { // wall-pointing
		pts[0][1] = y - 1;
	}
}

void CommDemo::displayResults() {
	Serial.println("");
	Serial.println("The legs of the hopper are in the following pegs:");
	Serial.print("(");
	Serial.print(pts[0][0]);
	Serial.print(",");
	Serial.print(pts[0][1]);
	Serial.print("), (");
	Serial.print(pts[1][0]);
	Serial.print(",");
	Serial.print(pts[1][1]);
	Serial.print("), (");
	Serial.print(pts[2][0]);
	Serial.print(",");
	Serial.print(pts[2][1]);
	Serial.println(")");
	Serial.println("");
}
