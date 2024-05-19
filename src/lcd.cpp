#include "lcd.h"

void setupLCD(){
    lcd.init();
    lcd.backlight();
    Serial.println("Hello");
}

void printLCD(int x, int y, char* msg){
}