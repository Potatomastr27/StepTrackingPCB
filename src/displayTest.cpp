#include <Arduino.h>
#include "pinDef.h"
#include "lcd.h"

long prevBlink = 0;


void setup() {
    Serial.begin(9600);

    setupPins();
    setupLCD();
    
    Serial.println("Begin");

    printLCD("Hello World\r\nHelloWorld2\r\n012345678901234567890123456789");
    delay(10000);
}

void loop() {
    for(int i = 0; i < 1000; i++){
        sprintf(lcdBuffer, "Heres a number: %i", i);
        printLCD(0,0, lcdBuffer,2,WHITE);
    }
}