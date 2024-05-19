#include "Calibration.h"
//#include <ADXL335.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////

void calibrationSetup() {

    // Set up analog pins
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);


    // Set up button pin
    pinMode(SWITCH_SUBROUTINES_PIN, INPUT_PULLUP);

    // Attach interrupt to the button
    attachInterrupt(digitalPinToInterrupt(SWITCH_SUBROUTINES_PIN), buttonInterrupt, FALLING);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Button interrupt handler
void buttonInterrupt() {
    //  delay(50); // Debounce...
    //  if (digitalRead(BUTTON_PIN) == LOW) {
    //    // Button is pressed, start calibration sequence
    //    lcd.clear();
    //    lcd.print("Hold for 2s");
    //    delay(2000);
    //    //state1 = true;
    //
    //    // Check if the button is still held after 2 seconds
    //    if (digitalRead(BUTTON_PIN) == LOW){//  state1 == true) {
    //      calibrationMode = true;
    //      lcd.clear();
    //      lcd.print("Calibration");
    //      lcd.setCursor(0, 1);
    //      lcd.print("Mode");
    //      //delay(2000);
    //
    // Authorize calibration
    while (digitalRead(SWITCH_SUBROUTINES_PIN) == LOW);

    calibrationAuthorized = true;

    // Calibration loop
    while (calibrationMode) {
    calibrateAxis(x_min, x_max, 'X');
    calibrateAxis(y_min, y_max, 'Y');
    calibrateAxis(z_min, z_max, 'Z');

    calibrationMode = false; // End calibration sequence
    stepStartTime = millis();          
    //flag1 = true;
    }

    // Display Calibration Complete
    //      if (flag1 == true){
    //        stepStartTime = millis;
    //        flag1 = false;
    //      }
    //        Serial.print(x_min);
    //        Serial.print("\t");
    //        Serial.print(x_max);
    //        Serial.print("\t");
    //        Serial.print(y_min);
    //        Serial.print("\t");
    //        Serial.print(y_max);
    //        Serial.print("\t"); 
    //        Serial.print(z_min);
    //        Serial.print("\t");
    //        Serial.print(z_max);
    //        Serial.println("\t");  //---->> Debugging Purposes

    currentTime = millis();
    lcd.clear();
    lcd.print("Calibration");
    lcd.setCursor(0, 1);
    lcd.print("Complete");

    /* return to main program */

    //delay(3000); // Display "Calibration Complete" for 3 seconds
    //lcd.clear();
    if (currentTime >= stepStartTime + 3000){
    lcd.clear();
    stepStartTime = millis();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to calibrate a specific axis
void calibrateAxis(int &minVal, int &maxVal, char axis) {
    if (calibrationAuthorized) {
        if (halfwayflag == false){
            lcd.clear();
            lcd.print ("- ");
            lcd.print(axis);
            lcd.setCursor(0, 1);
            lcd.print(" Calibration...");

            int lowSum = 0;

            // Get 20 low values
            for (int i = 0; i < 20; i++) {
                int val = readSensor(axis);
                lowSum += val;
                delay(50); // Adjust delay as needed
            }

            // Calculate the average for low values
            minVal = lowSum / 20;
            delay(500);
            calibDone = true;
            
            if (calibDone == true){
                halfwayflag = true;
                calibrationAuthorized = false;
                calibDone = false;
            }
        }

        lcd.clear();
        lcd.print("Waiting...");
        //delay(500);

        //halfwayflag = true

        //    if (calibrationAuthorized == true && halfwayflag == false){   --->>>>> ask whether this a viable way of toggeling
        //      halfwayflag = true;
        //    }
        //halfwayflag = false; 


        if (halfwayflag == true){ //&& calibrationAuthorized == true){ //--->>>>> Check here 
            lcd.clear();
            lcd.print ("+ ");
            lcd.print(axis);
            lcd.setCursor(0, 1);
            lcd.print(" Calibration");

            int highSum = 0;

            // Get 20 high values
            for (int i = 0; i < 20; i++) {
                int val = readSensor(axis);
                highSum += val;
                delay(50); // Adjust delay as needed
            }

            // Calculate the average for high values
            maxVal = highSum / 20;
            calibDone = true;
        }
        if (calibDone == true){
            lcd.clear();
            lcd.print(axis);
            lcd.print(" Calibration");
            lcd.setCursor(0, 1);
            lcd.print("Complete");
        }

        delay(1000); // Display "Calibration Complete" for 1 second
        calibrationAuthorized = false;
        halfwayflag = false; //------------>>> check whether its right
        calibDone = false;

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

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