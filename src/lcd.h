#ifndef lcd_h
#define lcd_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

const uint16_t lcdX = 2;
const uint16_t lcdY = 16;
const uint16_t lcdAdr = 0x27;
char lcdBuffer[100];

// Create LCD Object with an address of 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(lcdAdr, lcdY, lcdX);

void setupLCD();

/**
 * @brief Prints to the LCD/OLED Display
 * 
 * @param x the column to start in
 * @param y the row to start in
 * @param msg The msg to send, can use the provided "lcdBuffer"
*/
void printLCD(int x, int y, char* msg);


#endif