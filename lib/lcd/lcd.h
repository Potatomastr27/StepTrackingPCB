#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * Setup is based on this website, which is in turn based on the example code for the Adafruit_SSD1306 Library
 * https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/ 
 * 
*/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define defaultTextSize 1
#define defaultTextColor WHITE
#define lcdAdr 0x27 // Find address, this is not right

extern char lcdBuffer[100];

void setupLCD();

/**
 * @brief Prints to the LCD/OLED Display
 * 
 * @param msg The msg to send, can use the provided "lcdBuffer"
*/
void printLCD(char* msg);

/**
 * @brief Prints to the LCD/OLED Display
 * 
 * @param x the column to start in
 * @param y the row to start in
 * @param msg The msg to send, can use the provided "lcdBuffer"
*/
void printLCD(int x, int y, char* msg);

/**
 * @brief Prints to the LCD/OLED Display
 * 
 * @param x the column to start in
 * @param y the row to start in
 * @param msg The msg to send, can use the provided "lcdBuffer"
 * @param textSize The size of the text
 * @param textColour The colour of the text
*/
void printLCD(int x, int y, char* msg, int textSize, int textColour);




#endif