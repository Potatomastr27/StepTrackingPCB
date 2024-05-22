#include "Calibration.h"

// Calibration parameters
int x_neg1g, x_0g, x_1g, y_neg1g, y_0g, y_1g, z_neg1g, z_0g, z_1g;

int calibrate(){
    // Calibrate on each axis
    calibrateAxis(x_neg1g, x_1g, y_0g, 'X', 'Y');
    calibrateAxis(y_neg1g, y_1g, z_0g, 'Y', 'Z');
    calibrateAxis(z_neg1g, z_1g, x_0g, 'Z', 'X');

    // Save calibration data
    writeEEPROM();

    printLCD("Calibration Complete");
    delay(300); // Display "Calibration Complete" for 300ms second
    return 1;
}

// Function to calibrate a specific axis
void calibrateAxis(int &minVal, int &maxVal, int &normVal, char minMaxAxis, char normAxis) {
    int highSum = 0, lowSum = 0, normSum = 0;

    sprintf(lcdBuffer, "+%c\r\nPlease Position System Then press button", minMaxAxis);
    printLCD(lcdBuffer);

    // Wait until button is pressed
    while(digitalRead(SWITCH_SUBROUTINES_PIN) == BUTTON_RELEASED);

    sprintf(lcdBuffer, "+%c\r\nCalibrating...", minMaxAxis);
    printLCD(lcdBuffer);

    // Get 20 low values
    for (int i = 0; i < 20; i++) {
        lowSum += readSensor(minMaxAxis);
        normSum += readSensor(normAxis);
        delay(50); // Adjust delay as needed
    }

    // Calculate the average for low values
    minVal = lowSum / 20;

    sprintf(lcdBuffer, "-%c\nPlease Position System Then press button", minMaxAxis);
    printLCD(lcdBuffer);

    // Wait until button is pressed
    while(digitalRead(SWITCH_SUBROUTINES_PIN) == BUTTON_RELEASED);

    sprintf(lcdBuffer, "-%c\r\nCalibrating...", minMaxAxis);
    printLCD(lcdBuffer);



    // Get 20 high values
    for (int i = 0; i < 20; i++) {
        highSum += readSensor(minMaxAxis);
        normSum += readSensor(normAxis);
        delay(50); // Adjust delay as needed
    }

    // Calculate the average for high values
    maxVal = highSum / 20;
    normVal = normSum / 40;
    sprintf(lcdBuffer, "%c Axis Calibration Complete %i, %i, %i", minMaxAxis, minVal, normVal, maxVal);
    printLCD(lcdBuffer);
    
    // Wait until button is pressed
    while(digitalRead(SWITCH_SUBROUTINES_PIN) == BUTTON_RELEASED);
}

// Function to read sensor value based on the specified axis
int readSensor(char axis) {
    int pin;

    // Pick the correct pin based on the axis
    switch (axis){
        case 'X':
            pin = FILTERED_X_AXIS_PIN;
            break;
        case 'Y':
            pin = FILTERED_Y_AXIS_PIN;
            break;
        case 'Z':
            pin = FILTERED_Z_AXIS_PIN;
            break;
        default:
            return -1;
    }

    return analogRead(pin);
}

int getCalibratedReading(char axis){
    switch (axis){
        case 'X':
            if 
            return map(analogRead(FILTERED_X_AXIS_PIN), x_neg1g, x_1g, -1024, 1024);
        case 'Y':
            return map(analogRead(FILTERED_Y_AXIS_PIN), y_neg1g, y_1g, -1024, 1024);
        case 'Z':
            return map(analogRead(FILTERED_Z_AXIS_PIN), z_neg1g, z_1g, -1024, 1024);
    }

    return -1;
}

void readEEPROM(){
    x_neg1g = EEPROM.read(0);
    x_neg1g = EEPROM.read(1);
    y_neg1g = EEPROM.read(2);
    y_1g = EEPROM.read(3);
    z_neg1g = EEPROM.read(4);
    z_1g = EEPROM.read(5);
}

void writeEEPROM(){
    EEPROM.write(0, x_neg1g);
    EEPROM.write(1, x_neg1g);
    EEPROM.write(2, y_neg1g);
    EEPROM.write(3, y_1g);
    EEPROM.write(4, z_neg1g);
    EEPROM.write(5, z_1g);
}