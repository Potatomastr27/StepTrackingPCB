#include "stepAnalysis.h"


void setupAnalysis(){
    // Fill with initial data
    for(int i = 0; i < BUFFER_SIZE; i++){
        movingAvgBuffer[i] = 0;
    }
    avg = 0;
}

bool addReading(int reading){
    int newAvg = 0;
    // Shift all the readings over by 1 to the left
    for (int i = 0; i < BUFFER_SIZE - 1; i++){
        movingAvgBuffer[i] = movingAvgBuffer[i+1];
        // Start summing up new average
        newAvg += movingAvgBuffer[i];
    }

    // Append new reading onto end
    movingAvgBuffer[BUFFER_SIZE-1] = reading;
    //Calculate new average
    newAvg += reading;
    newAvg = newAvg / BUFFER_SIZE;

    // We want to only trigger a step count on a rising edge so that we dont double count

    bool isPrevAvgAboveThreshold = avg > stepAmplitudeThreshold;
    bool isNewAvgAboveThreshold = newAvg > stepAmplitudeThreshold;

    // Set the prevAvg to the new average for the next time we run this function
    avg = newAvg;
    // Check if the new average is above the threshold and the previous is below, this means that a step has occured
    if (isNewAvgAboveThreshold && isPrevAvgAboveThreshold == false)
        return true;

    // If not we just return false
    return false;
}

int getAvg(){
    return avg;
}