// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef Test_H_
#define Test_H_
#include "Arduino.h"
#include <LiquidCrystal.h>
//add your includes for the project Test here

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
void testConnection();
void setupLCD();
void setupSensors();
void setupMotors();
void testLCD();
void testSensors();
void testMotors();
void testSerial();
int readSensor(int, int);
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project Test here

//Do not add code below this line
#endif /* Test_H_ */
