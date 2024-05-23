#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>
#include <Calibration.h>
long prevBlink = 0;
#define ARR_SIZE 5
int absAccs[ARR_SIZE];

void setup() {
    Serial.begin(9600);

    setupPins();
    Serial.println("Setting up LCD");
    setupLCD();
    
    Serial.println("Begin");
    Serial.println("Sending Hello World to LCD");
    printLCD("Hello World");
    Serial.println("Done, waiting 10 seconds");
    delay(1000);

    //calibrate();

    readEEPROM();
}

void loop() {
    int x = getCalibratedReading('X');
    int y = getCalibratedReading('Y');
    int z = getCalibratedReading('Z');
    int absAcc = sqrt(square(x) + square(y) + square(z)) - 1000;

    for (int i = 0; i < ARR_SIZE -1; i++){
        // Shift over this entry by one
        absAccs[i] = absAccs[i+1];
    }
    // Append new data point in newly made free space
    absAccs[ARR_SIZE-1] = absAcc;

    // Find the peak acceleration in the array
    int peakAbsAcc = 0;
    for (auto acceleration : absAccs){
        if (acceleration > peakAbsAcc)
            peakAbsAcc = acceleration;
    }

    Serial.println("Using sprintf");
    sprintf(lcdBuffer, "X: %i %i\r\nY: %i %i\r\nZ: %i %i\r\nAbs: %i, Peak: %i", x, analogRead(FILTERED_X_AXIS_PIN), y, analogRead(FILTERED_Y_AXIS_PIN), z, analogRead(FILTERED_Z_AXIS_PIN), absAcc, peakAbsAcc);
    // Debug code
    Serial.print("Buffer Contents: ");
    Serial.println(lcdBuffer);
    Serial.println("Sending to LCD");
    printLCD(0,0, lcdBuffer,1,WHITE);

}