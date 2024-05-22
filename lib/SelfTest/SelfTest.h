#ifndef SELFTEST_H
#define SELFTEST_H

#include <Arduino.h>
#include "../../include/pinDef.h"
#include <lcd.h>

/**
 * @returns true if sensor working, false otherwise
*/
bool selfTest();


void turnSTOn();

void turnSTOff();

int getXAcceleration();

int getYAcceleration();

int getZAcceleration();


#endif