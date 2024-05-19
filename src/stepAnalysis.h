#ifndef STEPANALYSIS_H
#define STEPANALYSIS_H

#include <Arduino.h>
#include "pinDef.h"


int movingAvgBuffer[5];
int avg;

void setupAnalysis();

/**
 * @returns Whether or not a step occured
*/
int addReading(int reading);

int getAvg();
















#endif