#include <Arduino.h>
#include <math.h>

#include "SelfTest.h"
#include "Calibration.h"
#include "pinDef.h"
#include "lcd.h"
#include "stepAnalysis.h"

void shutdownError(char* msg);
void buttonCallback();


double absAccelleration;
int x_axis,y_axis,z_axis;

int stepCount = 0;
long buttonPressTime = 0;

bool doCalibration = false;

void setup() {
    Serial.begin(9600);

    setupPins();
    setupLCD();
    setupAnalysis();    

    if (selfTest() == false)
        shutdownError("Self Test Failed");

    // Add an external interrupt on pin 3 for switch subroutine button
    attachInterrupt(INT1, buttonCallback, CHANGE);
}

void loop() {
    // If we need to do calibration, do it
    if (doCalibration == true){
        calibrate();
        doCalibration = false;
        // After calibration we need to reset the stepAnalysis data as the data is no longer relevant
        setupAnalysis();
    }
    // Get latest readings
    x_axis = getCalibratedReading('X');
    y_axis = getCalibratedReading('Y');
    z_axis = getCalibratedReading('Z');

    // Calculate absolute acceleration
    absAccelleration = sqrt(square(x_axis) + square(y_axis) + square(z_axis));
    // Update the reading for the step count with the new data
    stepCount += addReading(absAccelleration);

    // If reset step button is pressed, reset the step count
    if (digitalRead(RESET_STEP_PIN) == BUTTON_PRESSED)
        stepCount = 0;
    
    // Reset LEDs
    digitalWrite(STATIONARY_PIN, LOW);
    digitalWrite(WALKING_PIN, LOW);
    digitalWrite(RUNNING_PIN, LOW);


    // Get the rate of movement
    int movementRate = getMovementRate();
    // If the function returned an invalid reading we shutdown
    if (movementRate == -2)
        shutdownError("ERROR: getMovementRate() returned -2");
    
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

    // Update LCD with step count
    sprintf(lcdBuffer, "Step Count:\r\n%i", stepCount);
    printLCD(lcdBuffer);
}



void shutdownError(char* msg){
    Serial.println(msg);
    printLCD(msg);
    while(true);
}

void buttonCallback(){
    // If the button was pressed we record the time it was pressed
    if (digitalRead(SWITCH_SUBROUTINES_PIN) == BUTTON_PRESSED){
        buttonPressTime = millis();
        return;
    }
    // Otherwise we check how long the button was held for
    long buttonPressLength = millis() - buttonPressTime;

    // If it was held for more than 2 seconds, we tell the main loop to run the calibration sequence
    if (buttonPressTime > 2000){
        doCalibration = true;
    }
}