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
    printLCD("Hello World");
    Serial.println("Done, waiting 10 seconds");
    delay(1000);

}

void loop() {
    Serial.println("Using sprintf");
    sprintf(lcdBuffer, "X: %i\r\nY: %i\r\nZ: %i", analogRead(FILTERED_X_AXIS_PIN), analogRead(FILTERED_Y_AXIS_PIN), analogRead(FILTERED_Z_AXIS_PIN));
    // Debug code
    Serial.print("Buffer Contents: ");
    Serial.println(lcdBuffer);
    Serial.println("Sending to LCD");
    printLCD(0,0, lcdBuffer,1,WHITE);
}