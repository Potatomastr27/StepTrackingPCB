#ifndef STEPANALYSIS_H
#define STEPANALYSIS_H

#include <Arduino.h>
#include "pinDef.h"

#define BUFFER_SIZE 5
int movingAvgBuffer[BUFFER_SIZE];

const uint32_t stepAmplitudeThreshold = 1000;

int avg;

void setupAnalysis();

/**
 * @returns Whether or not a step occured
*/
bool addReading(int reading);

int getAvg();
















#endif