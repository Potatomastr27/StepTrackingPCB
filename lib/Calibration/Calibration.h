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
void calibrateAxis(int &minVal, int &maxVal, int &normVal, char minMaxAxis, char normAxis);

//////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Will get the raw reading of the specified axis
 * @param axis The axis to get the reading of, either 'X', 'Y' or 'Z'
 * @returns the reading of that axis
*/ 
int readSensor(char axis);

/**
 * @brief Will give you the calibrated axis reading
 * 
 * @param axis The axis reading to return, either 'X', 'Y' or 'Z'
 * @returns An int representing the acceleration of that axis
*/
int getCalibratedReading(char axis);

/**
 * @brief Reads the calibration parameters stored in the EEPROM 
*/
void readEEPROM();
/**
 * @brief Saves the current calibration parameters to the EEPROM
*/
void writeEEPROM();


#endif