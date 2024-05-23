#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>
#include <Calibration.h>
#include <stepAnalysis.h>

long prevBlink = 0;
int y_axis, x_axis, z_axis, absAcceleration;
int stepCount;

void setup() {
    Serial.begin(9600);

    setupPins();
    Serial.println("Setting up LCD");
    setupLCD();
    setupAnalysis();
    
    Serial.println("Begin");
    Serial.println("Sending Hello World to LCD");
    printLCD("Hello World");
    Serial.println("Done, waiting 10 seconds");
    delay(1000);
    stepCount = 0;

}

void loop() {
    // Get latest readings
    x_axis = getCalibratedReading('X');
    y_axis = getCalibratedReading('Y');
    z_axis = getCalibratedReading('Z');    

    // Calculate absolute acceleration
    absAcceleration = sqrt(square(x_axis) + square(y_axis) + square(z_axis)) - 1000;
    stepCount += addReading(absAcceleration);

    sprintf(lcdBuffer, "Steps: %i Avg: %i\r\nX: %i\r\nY: %i\r\nZ: %i", stepCount, getAvg(), analogRead(FILTERED_X_AXIS_PIN), analogRead(FILTERED_Y_AXIS_PIN), analogRead(FILTERED_Z_AXIS_PIN));

    printLCD(0,0, lcdBuffer,1,WHITE);
}