#include "stepAnalysis.h"

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

void setupAnalysis(){
    // Fill with initial data
    for(auto data : movingAvgBuffer){
        data = 0;
    }
    for(auto data : movingAvgTimeBuffer){
        data = 0;
    }
    avg = 0;
}

int addReading(int reading){
    long functionCallTime = millis(); // We will need to use this later for saving in the time Buffer

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
    
    // Check if the new average is above the threshold and the previous is below, this means that a step has occured
    bool hasStepOccured = (newAvg > stepAmplitudeThreshold) && ((avg > stepAmplitudeThreshold) == false);

    // Set the prevAvg to the new average for the next time we run this function
    avg = newAvg;
    // If a step has not occured we want to exit function early
    if (hasStepOccured == false){
        // A step has not occured so we just need to update the time between steps buffer and return false
        movingAvgTimeBuffer[TIME_BUFFER_SIZE-1] = functionCallTime;
        return 0;
    }
    
    // A step has occured
    // Move over all the data in this buffer by 1
    for (int i = 0; i < TIME_BUFFER_SIZE - 1; i++){
        movingAvgTimeBuffer[i] = movingAvgTimeBuffer[i+1];
    }
    
    // Append another time onto the end to represent the next incomplete step
    movingAvgTimeBuffer[TIME_BUFFER_SIZE-1] = functionCallTime;

    // Return true because a step occured
    return 1;
}

int getAvg(){
    return avg;
}

int getMovementRate(){

    // Ensure that the buffer is full of data before trying to calculate movement rate
    for (auto time : movingAvgTimeBuffer){
        if (time < 100)
            return -1;
    }
    // We are interested in the time between each step AND the time between each step including the next step that hasnt occured yet
    long avgTimeBetweenSteps, avgTimeInclNextStep = 0;
    double freqSteps, freqInclNextStep = 0;

    // for (int i = 0; i < TIME_BUFFER_SIZE-1; i++){
    //     // Sum the difference between step times to get time between steps
    //     avgTimeInclNextStep += movingAvgTimeBuffer[i+1] - movingAvgTimeBuffer[i];
    // }
    // Sum the difference between step times to get time between steps = last entry - first entry
    avgTimeInclNextStep = movingAvgTimeBuffer[TIME_BUFFER_SIZE-1] - movingAvgTimeBuffer[0];

    // Exclude the last entry for time between steps so take it out
    // avgTimeBetweenSteps = avgTimeInclNextStep - (movingAvgTimeBuffer[TIME_BUFFER_SIZE-1] - movingAvgTimeBuffer[TIME_BUFFER_SIZE-2]);
    avgTimeBetweenSteps = movingAvgTimeBuffer[TIME_BUFFER_SIZE-2] - movingAvgTimeBuffer[0];

    // We now have our averages so we must next calculate the frequency of steps

    // Convert to a double, then convert from ms to seconds, then use 1/T = f to get frequency
    freqSteps = 1/(((double)avgTimeBetweenSteps)/1000);
    freqInclNextStep = 1/(((double)avgTimeInclNextStep)/1000);

    // We have the frequencies so last step is to compare to our set thresholds

    // First we need to check if enough time has passed since the last step that we know the user is stationary
    if (freqInclNextStep < stepFrequencyWalk)
        return 0;
    
    // If that is not the case we can just calculate based on the steps that have occured
    if (freqSteps > stepFrequencyRun)
        return 2;
    if (freqSteps > stepFrequencyWalk)
        return 1;
    if (freqSteps > 0)
        return 0;
    Serial.print("ERROR: Invalid Frequency Value = ");
    Serial.println(freqSteps);
    // If no if statement triggered we must have an invalid frequency value (such as negative) so return -2 to signify this
    return -2;
}
