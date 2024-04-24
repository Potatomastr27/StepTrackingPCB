#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>

long prevBlink = 0;
char lcdBuffer[50];

void setup() {
    setupPins();
    setupLCD();
    lcd.print("Hello World");
}

void loop() {

    if (millis() - prevBlink > 500 && !digitalRead(SWITCH_SUBROUTINES_PIN == LOW)){
        digitalWrite(STATIONARY_PIN, !digitalRead(STATIONARY_PIN));
        delay(100);
        digitalWrite(WALKING_PIN, !digitalRead(WALKING_PIN));
        delay(100);
        digitalWrite(RUNNING_PIN, !digitalRead(RUNNING_PIN));
        delay(100);
        prevBlink = millis();
    }

    if ((!digitalRead(RESET_STEP_PIN)) == HIGH){
        lcd.clear();
        snprintf(lcdBuffer, 32, "X: %i Y:%iZ:%i", analogRead(FILTERED_X_AXIS_PIN), analogRead(FILTERED_Y_AXIS_PIN), analogRead(FILTERED_Z_AXIS_PIN));
        lcd.print(lcdBuffer);
    }
}