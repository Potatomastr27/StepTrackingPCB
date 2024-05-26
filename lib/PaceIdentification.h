#ifndef PACEIDENTIFICATION_H
#define PACEIDENTIFICATION_H

#include <Arduino.h>
#include <pinDef.h>
#include "pinDef.h"

void updatePace(int movementRate);

// Add the function declaration here
void shutdownError(const char* msg);

#endif