 #include "Calibration.h"

// Calibration parameters
struct calibrationParms{
    int x_neg1g, x_0g, x_1g, y_neg1g, y_0g, y_1g, z_neg1g, z_0g, z_1g;
};

// Aprox default params, will be overwritten by EEPROM
calibrationParms params = {607,511,408,612,511,409,614,511,411}; 


int calibrate(){
    // Calibrate on each axis
    calibrateAxis(params.x_neg1g, params.x_1g, params.y_0g, 'X', 'Y');
    calibrateAxis(params.y_neg1g, params.y_1g, params.z_0g, 'Y', 'Z');
    calibrateAxis(params.z_neg1g, params.z_1g, params.x_0g, 'Z', 'X');

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
        delay(100); // Adjust delay as needed
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
        delay(100); // Adjust delay as needed
    }

    // Calculate the average for high values
    maxVal = highSum / 20;
    normVal = normSum / 40;
    sprintf(lcdBuffer, "%c Axis Calibration Complete %i, %i, %i", minMaxAxis, minVal, normVal, maxVal);
    printLCD(lcdBuffer);
    
    // Wait until button is pressed
    while(digitalRead(SWITCH_SUBROUTINES_PIN) == BUTTON_RELEASED);
    delay(300);
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
    // get raw reading
    int rawReading = readSensor(axis);
    switch (axis){
        case 'X':
            // If the raw reading is a positive acceleration, map the reading where 0g -> 0 and 1g -> 1000
            if (rawReading < params.x_0g)
                return map(rawReading, params.x_0g, params.x_1g, 0, 1000);
            // If the raw reading is a negative acceleration, map the reading where -1g -> -1000, 0g -> 0
            else if (rawReading > params.x_0g)
                return map(rawReading, params.x_neg1g, params.x_0g, -1000, 0);
            
        case 'Y':
        // If the raw reading is a positive acceleration, map the reading where 0g -> 0 and 1g -> 1000
            if (rawReading < params.y_0g)
                return map(rawReading, params.y_0g, params.y_1g, 0, 1000);
            // If the raw reading is a negative acceleration, map the reading where -1g -> -1000, 0g -> 0
            else if (rawReading > params.y_0g)
                return map(rawReading, params.y_neg1g, params.y_0g, -1000, 0);
        case 'Z':
        // If the raw reading is a positive acceleration, map the reading where 0g -> 0 and 1g -> 1000
            if (rawReading < params.z_0g)
                return map(rawReading, params.z_0g, params.z_1g, 0, 1000);
            // If the raw reading is a negative acceleration, map the reading where -1g -> -1000, 0g -> 0
            else if (rawReading > params.z_0g)
                return map(rawReading, params.z_neg1g, params.z_0g, -1000, 0);
    }
}

void readEEPROM(){
    EEPROM.get(0, params);
}

void writeEEPROM(){
    EEPROM.put(0, params);
}