#ifndef STEPANALYSIS_H
#define STEPANALYSIS_H

#include <Arduino.h>
#include "../../include/pinDef.h"



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