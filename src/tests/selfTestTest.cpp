#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>
#include <SelfTest.h>

long prevBlink = 0;


void setup() {
    Serial.begin(9600);

    setupPins();
    Serial.println("Setting up LCD");
    setupLCD();

    delay(1000);
    selfTest();

}

void loop() {
}