#include <Arduino.h>
#include "SelfTest.h"
#include "Calibration.h"
#include "pinDef.h"
#include "lcd.h"


void setup() {
    setupPins();
    setupLCD();

    Serial.begin(9600);
    
}

void loop() {

}