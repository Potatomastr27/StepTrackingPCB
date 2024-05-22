#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>
#include <Calibration.h>

long prevBlink = 0;


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
    Serial.println("Using sprintf");
    sprintf(lcdBuffer, "X: %i %i\r\nY: %i %i\r\nZ: %i %i\r\nAbs: %i", x, analogRead(FILTERED_X_AXIS_PIN), y, analogRead(FILTERED_Y_AXIS_PIN), z, analogRead(FILTERED_Z_AXIS_PIN), absAcc);
    // Debug code
    Serial.print("Buffer Contents: ");
    Serial.println(lcdBuffer);
    Serial.println("Sending to LCD");
    printLCD(0,0, lcdBuffer,1,WHITE);

}