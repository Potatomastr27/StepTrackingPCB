#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>

long prevBlink = 0;


void setup() {
    Serial.begin(9600);

    setupPins();
    Serial.println("Setting up LCD");
    setupLCD();
    
    Serial.println("Begin");
    Serial.println("Sending Hello World to LCD");
    printLCD("Hello World\r\nHelloWorld2\r\n012345678901234567890123456789");
    Serial.println("Done, waiting 10 seconds");
    delay(10000);
}

void loop() {
    for(int i = 0; i < 1000; i++){
        Serial.println("Using sprintf");
        sprintf(lcdBuffer, "Heres a number: %i", i);
        // Debug code
        Serial.print("Buffer Contents: ");
        Serial.println(lcdBuffer);
        Serial.println("Sending to LCD");
        printLCD(0,0, lcdBuffer,2,WHITE);
    }
}