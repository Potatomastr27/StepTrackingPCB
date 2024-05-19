#include "Calibration.h"

// Calibration parameters
int x_min, x_max, y_min, y_max, z_min, z_max;

// Calibration flags
volatile bool calibrationMode = false;

unsigned long stepStartTime = 0;
unsigned long currentTime = 0;

int calibrate(){
    // Calibrate on each axis
    calibrateAxis(x_min, x_max, 'X');
    calibrateAxis(y_min, y_max, 'Y');
    calibrateAxis(z_min, z_max, 'Z');

    // Save calibration data
    writeEEPROM();

    printLCD("Calibration Complete");
    delay(300); // Display "Calibration Complete" for 300ms second
    return 1;
}

// Function to calibrate a specific axis
void calibrateAxis(int &minVal, int &maxVal, char axis) {
    int highSum, lowSum = 0;

    sprintf(lcdBuffer, "-%c\r\nPlease Position System Then press button", axis);
    printLCD(lcdBuffer);

    // Wait until button is pressed
    while(/*Button is not presed*/false);

    sprintf(lcdBuffer, "-%c\r\nCalibrating...", axis);
    printLCD(lcdBuffer);

    // Get 20 low values
    for (int i = 0; i < 20; i++) {
        int val = readSensor(axis);
        lowSum += val;
        delay(50); // Adjust delay as needed
    }

    // Calculate the average for low values
    minVal = lowSum / 20;

    sprintf(lcdBuffer, "+%c\nPlease Position System Then press button", axis);
    printLCD(lcdBuffer);

    // Wait until button is pressed
    while(/*Button is not presed*/false);

    sprintf(lcdBuffer, "+%c\r\nCalibrating...", axis);
    printLCD(lcdBuffer);



    // Get 20 high values
    for (int i = 0; i < 20; i++) {
        int val = readSensor(axis);
        highSum += val;
        delay(50); // Adjust delay as needed
    }

    // Calculate the average for high values
    maxVal = highSum / 20;
    sprintf(lcdBuffer, "%c Axis Calibration Complete", axis);
    printLCD(lcdBuffer);
    

    delay(300); // Display "Calibration Complete" for 300ms second
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
            return map(analogRead(FILTERED_X_AXIS_PIN), 0, 1024, x_min, x_max);
        case 'Y':
            return map(analogRead(FILTERED_Y_AXIS_PIN), 0, 1024, y_min, y_max);
        case 'Z':
            return map(analogRead(FILTERED_Z_AXIS_PIN), 0, 1024, z_min, z_max);
    }

    return -1;
}

void readEEPROM(){
    x_min = EEPROM.read(0);
    x_max = EEPROM.read(1);
    y_min = EEPROM.read(2);
    y_max = EEPROM.read(3);
    z_min = EEPROM.read(4);
    z_max = EEPROM.read(5);
}

void writeEEPROM(){
    EEPROM.write(0, x_min);
    EEPROM.write(1, x_max);
    EEPROM.write(2, y_min);
    EEPROM.write(3, y_max);
    EEPROM.write(4, z_min);
    EEPROM.write(5, z_max);
}