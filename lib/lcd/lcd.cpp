#include "lcd.h"

Adafruit_SSD1306 display;
char lcdBuffer[100];


void setupLCD(){
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
        // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC) /*Address goes here*/) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.display();
    delay(2000);
}

void printLCD(char* msg){
    printLCD(0,0,msg, defaultTextSize, defaultTextColor);
}

void printLCD(char* msg, int textSize){
    printLCD(0,0,msg, textSize, defaultTextColor);
}

void printLCD(int x, int y, char* msg){
    printLCD(x,y,msg, defaultTextSize, defaultTextColor);
}

void printLCD(int x, int y, char* msg, int textSize, int textColour){
    display.clearDisplay();

    display.setTextSize(textSize);
    display.setTextColor(textColour);
    display.setCursor(x,y);
    display.print(msg);

    display.display();
}
