#include <Arduino.h>
#include <pinDef.h>

long prevBlink = 0;


void setup() {
    Serial.begin(9600);

    setupPins();
    
    Serial.println("Begin");
    delay(10000);
}

void loop() {

    // Blink all LEDS every 500ms seperated by 100ms only when the button is released
    if (millis() - prevBlink > 500 && digitalRead(SWITCH_SUBROUTINES_PIN == BUTTON_RELEASED)){
        digitalWrite(STATIONARY_PIN, !digitalRead(STATIONARY_PIN)); // Toggle Pin
        delay(100);
        digitalWrite(WALKING_PIN, !digitalRead(WALKING_PIN)); // Toggle Pin
        delay(100);
        digitalWrite(RUNNING_PIN, !digitalRead(RUNNING_PIN)); // Toggle Pin
        delay(100);
        prevBlink = millis();
    }
}