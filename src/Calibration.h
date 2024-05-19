#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "lcd.h"
#include "pinDef.h"

// Calibration parameters
int x_min, x_max, y_min, y_max, z_min, z_max;

// Calibration flags
volatile bool calibrationMode = false;

unsigned long stepStartTime = 0;
unsigned long currentTime = 0;

/**
 * @brief Will start the calibration sequence
 * 
 * @returns 0 if sucessful
*/
int calibrate();

// Calibration function declarations
void calibrateAxis(int &minVal, int &maxVal, char axis);

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to read sensor value based on the specified axis
int readSensor(char axis);

/**
 * @brief Will give you the calibrated axis reading
 * 
 * @param axis The axis reading to return, either 'X', 'Y' or 'Z'
 * @returns An int representing the acceleration of that axis
*/
int getCalibratedReading(char axis);


#endif