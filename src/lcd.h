#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal_I2C.h>

// Create LCD Object with an address of 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27,16,2);

void setupLCD(){
    lcd.init();
    lcd.backlight();
}




















#endif