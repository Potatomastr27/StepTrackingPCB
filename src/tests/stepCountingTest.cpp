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

    readEEPROM();

}

void loop() {
    // Get latest readings
    x_axis = getCalibratedReading('X');
    y_axis = getCalibratedReading('Y');
    z_axis = getCalibratedReading('Z');    

    // Calculate absolute acceleration
    absAcceleration = sqrt(square(x_axis) + square(y_axis) + square(z_axis)) - 1000;
    if(absAcceleration < 0)
        absAcceleration = 0;
    stepCount += addReading(absAcceleration);

    // Reset LEDs
    digitalWrite(STATIONARY_PIN, LOW);
    digitalWrite(WALKING_PIN, LOW);
    digitalWrite(RUNNING_PIN, LOW);

    // Get the rate of movement
    int movementRate = getMovementRate();    
    // Turn on the correct LED
    switch(movementRate){
        case 0:
            digitalWrite(STATIONARY_PIN, HIGH);
            break;
        case 1:
            digitalWrite(WALKING_PIN, HIGH);
            break;
        case 2:
            digitalWrite(RUNNING_PIN, HIGH);
            break;
        default:
            break; //Do Nothing
    }
    char freq[10];
    dtostrf(getFreq(), 4, 2, freq);

    sprintf(lcdBuffer, "S %i A %i F %s\r\nX: %i %i\r\nY: %i %i\r\nZ: %i %i", 
            stepCount, getAvg(), freq, analogRead(FILTERED_X_AXIS_PIN), getCalibratedReading('X'), 
            analogRead(FILTERED_Y_AXIS_PIN), getCalibratedReading('Y'), analogRead(FILTERED_Z_AXIS_PIN), 
            getCalibratedReading('Z'));

    printLCD(0,0, lcdBuffer,1,WHITE);
}