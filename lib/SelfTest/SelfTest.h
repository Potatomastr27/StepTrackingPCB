#ifndef SELFTEST_H
#define SELFTEST_H

#include <Arduino.h>
#include "../../include/pinDef.h"
#include <lcd.h>

/**
 * @returns true if sensor working, false otherwise
*/
bool selfTest();

/**
 * @brief Turns Self Test mode on
*/
void turnSTOn();

/**
 * @brief Turns Self Test mode off
*/
void turnSTOff();

/**
 * @brief Gets the raw X axis acceleration
*/
int getXAcceleration();

/**
 * @brief Gets the raw Y axis acceleration
*/
int getYAcceleration();

/**
 * @brief Gets the raw Z axis acceleration
*/
int getZAcceleration();


#endif