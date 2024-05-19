#ifndef PINDEF_H
#define PINDEF_H

#include <Arduino.h>
//D0
//D1
const uint8_t RESET_STEP_PIN = 2;            //D2
const uint8_t SWITCH_SUBROUTINES_PIN = 3;    //D3
//D4
const uint8_t SELF_TEST_PIN = 5;             //D5
//D6
//D7
const uint8_t STATIONARY_PIN = 8;            //D8
const uint8_t WALKING_PIN = 9;               //D9
const uint8_t RUNNING_PIN = 10;              //D10
const uint8_t ENABLE_3V = 11;                //D11
//D12
//D13

const uint8_t I2C_DATA_PIN = SDA;            //SDA
const uint8_t I2C_CLOCK_PIN = SCL;           //SCL

const uint8_t FILTERED_X_AXIS_PIN = A0;      //A0
const uint8_t FILTERED_Y_AXIS_PIN = A1;      //A1
const uint8_t FILTERED_Z_AXIS_PIN = A2;      //A2
//A3
//A4
//A5

#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

inline void setupPins(){
    pinMode(RESET_STEP_PIN, INPUT_PULLUP);
    pinMode(SWITCH_SUBROUTINES_PIN, INPUT_PULLUP);
    pinMode(SELF_TEST_PIN, OUTPUT);
    pinMode(STATIONARY_PIN, OUTPUT);
    pinMode(WALKING_PIN, OUTPUT);
    pinMode(RUNNING_PIN,OUTPUT);
    pinMode(ENABLE_3V, OUTPUT);
    digitalWrite(ENABLE_3V, HIGH); // Enable 3V system by default
}
#endif