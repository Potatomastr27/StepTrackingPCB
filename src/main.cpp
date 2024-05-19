#include <Arduino.h>
#include "SelfTest.h"
#include "Calibration.h"
#include "pinDef.h"
#include "lcd.h"
#include "stepAnalysis.h"


void setup() {
    setupPins();
    setupLCD();
    setupAnalysis();

    Serial.begin(9600);    
}

void loop() {
    
}