#include <Arduino.h>
#include <pinDef.h>
#include <lcd.h>

long prevBlink = 0;


void setup() {
    Serial.begin(9600);

    setupPins();
    setupLCD();
    
    lcd.setCursor(0,0);
    lcd.print("Hello World");
    Serial.println("Begin");
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

    // 
    if (digitalRead(RESET_STEP_PIN) == BUTTON_PRESSED){
        lcd.clear();
        snprintf(lcdBuffer, 32, "X: %i Y:%iZ:%i", analogRead(FILTERED_X_AXIS_PIN), analogRead(FILTERED_Y_AXIS_PIN), analogRead(FILTERED_Z_AXIS_PIN));
        lcd.print(lcdBuffer);
    }
    else{
        lcd.clear();
        snprintf(lcdBuffer, 32, "Hello World!");
        lcd.print(lcdBuffer);
    }
}