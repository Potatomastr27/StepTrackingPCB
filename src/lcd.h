#ifndef lcd_h
#define lcd_h

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

const uint16_t SCREEN_WIDTH = 128;
const uint16_t SCREEN_HEIGHT = 32;
const uint16_t defaultTextSize = 1;
const uint16_t defaultTextColor = WHITE;
const uint16_t lcdAdr = 0x27; // Find address, this is not right
char lcdBuffer[100];

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

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