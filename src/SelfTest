include "pinDef.h"

int initialX;
int initialy;
int initialz;

int accelerationX;
int accelerationY;
int accelerationZ;

double analogLow = 0.0;
double analogHigh = 1023.0;
double voltageLow = 0.0;
double voltageHigh = 5.0;

double expectedChangeX = -0.325 //-325mV -1.08 G
double expectedChangeY = 0.325 //+325 mV 1.08 G
double expectedChangeZ = 0.550  //+550mV 1.83 G
double tolerance = 0.01; //random value, we can change to get it workig properly


void setup() {
  // pinMode(stPwrPin, OUTPUT);
  // pinMode(xacceleration, INPUT);
  // pinMode(yacceleration, INPUT);
  // pinMode(zacceleration, INPUT);
}

double mapValues(double input){
  double value = map(input, analogLow, analogHigh, voltageLow, voltageHigh);
  return value;
}

bool selfTest(){
  initialX = getXAcceleration();
  initialY = getYAcceleration();
  initialZ = getZAcceleration();

  setSTPinHigh();

  delay(10);

  accelerationX = getXAcceleration();
  accelerationY = getYAcceleration();
  accelerationZ = getZAcceleration();
//add a tolerance to our expected changed
  if ((expectedChangeX - tolerance <= accelerationX - initialX <= expectedChangeX + tolerance) && 
      (expectedChangeY - tolerance <= accelerationY - initialY <= expectedChangeY + tolerance) && 
      (expectedChangeZ - tolerance <= accelerationZ - initialZ <= expectedChangeZ + tolerance)){
    return true;
  }
  else{
    return false;
  }

  setSTPinLow();

}


void setSTPinHigh(){
 digitalWrite(SELF_TEST_PIN, HIGH);
}

void setSTPinLow(){
 digitalWrite(SELF_TEST_PIN, LOW);
}

int getXAcceleration(){
  double beforeMappedXValue = analogRead(FILTERED_X_AXIS_PIN);
  return mapValues(beforeMappedXValue);
}

int getYAcceleration(){
  double beforeMappedYValue = analogRead(FILTERED_Y_AXIS_PIN);
  return mapValues(beforeMappedYValue);
}

int getZAcceleration(){
  double beforeMappedZValue = analogRead(FILTERED_Z_AXIS_PIN);
  return mapValues(beforeMappedZValue);
}
