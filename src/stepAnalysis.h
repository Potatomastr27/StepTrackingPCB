#ifndef STEPANALYSIS_H
#define STEPANALYSIS_H

#include <Arduino.h>
#include "pinDef.h"

#define BUFFER_SIZE 5
int movingAvgBuffer[BUFFER_SIZE];

const uint32_t stepAmplitudeThreshold = 1000;
const uint32_t stepFrequencyWalk = 2;
const uint32_t stepFrequencyRun = 3;

int avg;

// Stores the time at which the last 5 steps occured
#define TIME_BUFFER_SIZE 5
long movingAvgTimeBuffer[TIME_BUFFER_SIZE]; // The last entry of the buffer will be updated every call even if no step has occured
long avgStepTime;

/**
 * @brief Sets all the interal data to their inital values
*/
void setupAnalysis();

/**
 * @brief This function should be run as often as possible for more accurate results
 * @returns 1 if a step occured 0 otherwise
*/
int addReading(int reading);

int getAvg();
/**
 * @brief Returns whether the user is stationary, walking or running
 * @returns 0,1,2 -> Stationary, Walking, Running or -1 if there is not enough data to determine yet or -2 if an error occured with the analysis
*/
int getMovementRate();












#endif