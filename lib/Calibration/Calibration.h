#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Arduino.h>
#include "../../include/pinDef.h"
#include <lcd.h>
#include <EEPROM.h>

extern char lcdBuffer[100];
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

void readEEPROM();

void writeEEPROM();


#endif