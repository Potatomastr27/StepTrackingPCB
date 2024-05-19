#include "lcd.h"
#include "pinDef.h"
//#include <ADXL335.h>

// Calibration parameters
int x_min, x_max, y_min, y_max, z_min, z_max;

// Calibration flags
volatile bool calibrationMode = false;
volatile bool calibrationAuthorized = false;

//logic flags 
bool flag1 = false;
bool halfwayflag = false;
bool calibDone = false; 
//bool state1 = true;

unsigned long stepStartTime = 0;
unsigned long currentTime = 0;

// Calibration function declarations
void calibrateAxis(int &minVal, int &maxVal, char axis);

//////////////////////////////////////////////////////////////////////////////////////////////////////

void calibrationSetup();

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Button interrupt handler
void buttonInterrupt();

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to read sensor value based on the specified axis
int readSensor(char axis);