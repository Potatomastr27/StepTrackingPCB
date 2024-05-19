#ifndef SELFTEST_H
#define SELFTEST_H
#include "../../include/pinDef.h"

#include <Arduino.h>

double mapValues(double input);

/**
 * @returns true if sensor working, false otherwise
*/
bool selfTest();


void setSTPinHigh();

void setSTPinLow();

int getXAcceleration();

int getYAcceleration();

int getZAcceleration();


#endif