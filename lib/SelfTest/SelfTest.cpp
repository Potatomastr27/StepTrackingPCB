#include "SelfTest.h"

int initialX;
int initialY;
int initialZ;

int accelerationX;
int accelerationY;
int accelerationZ;

int expectedChangeX = -110; //-325mV -1.08 G
int expectedChangeY = 110; //+325 mV 1.08 G
int expectedChangeZ = 188;  //+550mV 1.83 G
int tolerance = 30; // Tollerance for passing the self test

bool selfTest(){
    printLCD("Self Test\r\nUnderway", 2);
    int initialX = getXAcceleration();
    int initialY = getYAcceleration();
    int initialZ = getZAcceleration();

    turnSTOn();

    delay(2000);

    int accelerationX = getXAcceleration();
    int accelerationY = getYAcceleration();
    int accelerationZ = getZAcceleration();
    turnSTOff();

    int difX = accelerationX - initialX;
    int difY = accelerationY - initialY;
    int difZ = accelerationZ - initialZ;

    //add a tolerance to our expected changed
    if (abs(difX - expectedChangeX) < tolerance &&
        abs(difY - expectedChangeY) < tolerance &&
        abs(difZ - expectedChangeZ) < tolerance
    ){
        sprintf(lcdBuffer, "Success\r\nX: %i,%i,%i\r\nY: %i,%i,%i\r\nZ: %i,%i,%i", initialX, accelerationX, difX, initialY, accelerationY, difY, initialZ, accelerationZ, difZ);
        printLCD(lcdBuffer);
        return true;
    }
    else{
        sprintf(lcdBuffer, "Failed\r\nX: %i,%i,%i\r\nY: %i,%i,%i\r\nZ: %i,%i,%i", initialX, accelerationX, difX, initialY, accelerationY, difY, initialZ, accelerationZ, difZ);
        printLCD(lcdBuffer);
        return false;
    }

  

}


void turnSTOn(){
 digitalWrite(SELF_TEST_PIN, LOW);
}

void turnSTOff(){
 digitalWrite(SELF_TEST_PIN, HIGH);
}

int getXAcceleration(){
  return analogRead(FILTERED_X_AXIS_PIN);
}

int getYAcceleration(){
  return analogRead(FILTERED_Y_AXIS_PIN);
}

int getZAcceleration(){
  return analogRead(FILTERED_Z_AXIS_PIN);
}
