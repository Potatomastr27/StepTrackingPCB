#ifndef SELFTEST_H
#define SELFTEST_H
#include "pinDef.h"

#include <Arduino.h>

int initialX;
int initialY;
int initialZ;

int accelerationX;
int accelerationY;
int accelerationZ;

double analogLow = 0.0;
double analogHigh = 1023.0;
double voltageLow = 0.0;
double voltageHigh = 5.0;

double expectedChangeX = -0.325; //-325mV -1.08 G
double expectedChangeY = 0.325; //+325 mV 1.08 G
double expectedChangeZ = 0.550;  //+550mV 1.83 G
double tolerance = 0.01; //random value, we can change to get it workig properly

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