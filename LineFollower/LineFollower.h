// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef LineFollower_H_
#define LineFollower_H_
#include "Arduino.h"
#include <LiquidCrystal.h>
//add your includes for the project LineFollower here

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
bool* readSensors();
#ifdef __cplusplus
} // extern "C"
#endif

void calibrateSensors();
int readSensor(int sensor);
void adjustMotors();

//Do not add code below this line
#endif /* LineFollower_H_ */
