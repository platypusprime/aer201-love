// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef Navigator_H_
#define Navigator_H_
#include "Arduino.h"
//add your includes for the project Navigator here

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

void calibrateSensors();
void readSensors(bool* &);
void adjustMotors(short, short, bool, bool);
void selectDemux(bool, bool, bool, bool);
void selectMotor(bool, bool, bool, bool);
bool matchesPattern(bool, bool, bool, bool);
void move(int, int, int, int);
void forward(int);
void turn(int);

//Do not add code below this line
#endif /* Navigator_H_ */
