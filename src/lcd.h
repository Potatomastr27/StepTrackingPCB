#ifndef lcd_h
#define lcd_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint16_t lcdX = 2;
const uint16_t lcdY = 16;
const uint16_t lcdAdr = 0x27;
char lcdBuffer[32];

// Create LCD Object with an address of 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(lcdAdr, lcdY, lcdX);

void setupLCD(){
    lcd.init();
    lcd.backlight();
    Serial.println("Hello");
}




















#endif